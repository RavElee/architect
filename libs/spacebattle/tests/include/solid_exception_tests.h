#ifndef SOLID_EXCEPTION_TESTS_H
#define SOLID_EXCEPTION_TESTS_H

#include <gtest/gtest.h>
#include <mock.h>

#include "repeat_command.h"
#include <repeat_twice_command.h>
#include <empty_command.h>
#include <empty_exception.h>
#include <exception_handler.h>
#include <log_command.h>
#include <loop.h>

TEST(SOLID_EXCEPTIONS, MOCK_TEST)
{
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);

    auto cmd = std::make_shared<mock_command>();
    EXPECT_CALL(*cmd, execute());

    eventLoop.start();
    q.push(cmd);
    eventLoop.stop();
}

TEST(SOLID_EXCEPTIONS, LOG_CMD)
{
    mock_exception e;
    EXPECT_NO_THROW(std::make_shared<engine::log_command>(e)->execute());
}

TEST(SOLID_EXCEPTIONS, LOG_CMD_PUT_IN_Q)
{
    engine::exception_handler &eh = engine::exception_handler::instance();
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);
    eventLoop.start();

    engine::handlerFunc handlerLocal = [](engine::command_shared,
                                          const std::exception &e) -> engine::command_shared {
        return std::make_shared<engine::log_command>(e);
    };

    eh.register_handler(typeid(mock_command), typeid(mock_exception), handlerLocal);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute()).WillOnce(testing::Throw(mock_exception()));

    q.push(cmd);
    eventLoop.stop();
}

TEST(SOLID_EXCEPTIONS, REPEAT_CMD)
{
    engine::exception_handler &eh = engine::exception_handler::instance();
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);
    eventLoop.start();

    engine::handlerFunc handlerLocal = [](engine::command_shared cmd,
                                          const std::exception &) -> engine::command_shared {
        return std::make_shared<engine::repeat_command>(cmd);
    };

    eh.register_handler(typeid(mock_command), typeid(mock_exception), handlerLocal);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute()).Times(2).WillOnce(testing::Throw(mock_exception())).WillOnce(std::function<void()>());

    q.push(cmd);
    eventLoop.stop();
}

TEST(SOLID_EXCEPTIONS, REPEAT_CMD_PUT_IN_Q)
{
    engine::exception_handler &eh = engine::exception_handler::instance();
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);
    eventLoop.start();

    engine::handlerFunc handlerLocal = [&q](engine::command_shared cmd,
                                            const std::exception &) -> engine::command_shared {
        q.push(std::make_shared<engine::repeat_command>(cmd));
        return std::make_shared<engine::empty_command>();
    };

    eh.register_handler(typeid(mock_command), typeid(mock_exception), handlerLocal);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute())
        // .Times(2)
        .WillOnce(testing::Throw(mock_exception()))
        .WillOnce(std::function<void()>());

    q.push(cmd);

    // иначе loop умрёт и команды не обработаются
    // TODO: сделать очередь с приоритетами
    using namespace std::literals;
    std::this_thread::sleep_for(100ms);
    eventLoop.stop();
}

TEST(SOLID_EXCEPTIONS, REPEAT_ONCE_AND_LOG_IF_ANY_EXCEPT)
{
    engine::exception_handler &eh = engine::exception_handler::instance();
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);
    eventLoop.start();

    engine::handlerFunc handlerLocal = [](engine::command_shared cmd,
                                            const std::exception &) -> engine::command_shared {
        try
        {
            cmd->execute();
        }
        catch (const std::exception &e)
        {
            return std::make_shared<engine::log_command>(e);
        }

        return std::make_shared<engine::empty_command>();
    };

    eh.register_handler(typeid(mock_command), typeid(mock_exception), handlerLocal);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute())
        .Times(2)
        .WillRepeatedly(testing::Throw(mock_exception()));

    q.push(cmd);

    // иначе loop умрёт и команды не обработаются
    // TODO: сделать очередь с приоритетами
    using namespace std::literals;
    // std::this_thread::sleep_for(100ms);
    eventLoop.stop();
}

TEST(SOLID_EXCEPTIONS, REPEAT_TWICE_AND_LOG_IF_ANY_EXCEPT)
{
    engine::exception_handler &eh = engine::exception_handler::instance();
    engine::threadsafe_q<engine::command_shared> q;
    engine::loop eventLoop(q);
    eventLoop.start();

    engine::handlerFunc innerHandler = [](engine::command_shared cmd,
                                          const std::exception &) -> engine::command_shared {
        try {
            cmd->execute();
        } catch (const std::exception& e) {
            return std::make_shared<engine::log_command>(e);
        }
        return std::make_shared<engine::empty_command>();
    };

    eh.register_handler(typeid(engine::repeat_twice_command), typeid(mock_exception), innerHandler);

    engine::handlerFunc handlerLocal = [](engine::command_shared cmd,
                                          const std::exception &) -> engine::command_shared {
        engine::command_shared cmd_repeat;
        try
        {
            cmd_repeat = std::make_shared<engine::repeat_twice_command>(cmd);
            cmd_repeat->execute();
        }
        catch (const std::exception &e)
        {
            return engine::exception_handler::instance().handle(cmd_repeat, e);
        }
        return std::make_shared<engine::empty_command>();
    };

    eh.register_handler(typeid(mock_command), typeid(mock_exception), handlerLocal);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute())
        .Times(3)
        .WillRepeatedly(testing::Throw(mock_exception()));

    q.push(cmd);

    // иначе loop умрёт и команды не обработаются
    // TODO: сделать очередь с приоритетами
    using namespace std::literals;
    // std::this_thread::sleep_for(100ms);
    eventLoop.stop();
}

#endif //SOLID_EXCEPTION_TESTS_H
