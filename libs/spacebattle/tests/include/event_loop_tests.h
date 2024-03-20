#ifndef EVENT_LOOP_TESTS_H
#define EVENT_LOOP_TESTS_H

#include <gtest/gtest.h>
#include <mock.h>
// EVENT LOOP
#include "commands/start_loop.h"
#include "manual_reset_event.h"

TEST(EVENT_LOOP, EVENT_LOOP_STARTED)
{
    using namespace engine;
    threadsafe_q<command_shared> q;
    loop event_loop(q);

    auto cmd = std::make_shared<mock_command>();

    EXPECT_CALL(*cmd, execute());
    q.push(cmd);
    event_loop.start();
    event_loop.stop();
}

TEST(EVENT_LOOP, EVENT_LOOP_HARD_STOP_CMD)
{
    using namespace engine;
    threadsafe_q<command_shared> q;
    loop event_loop(q);

    manual_reset_event mre;

    auto cmd = std::make_shared<mock_command>();
    EXPECT_CALL(*cmd, execute()).Times(1);

    q.push(cmd);
    q.push(std::make_shared<loop::hard_stop>(event_loop, [&mre]() {
        mre.set();
    }));
    q.push(cmd);
    q.push(cmd);

    event_loop.start();
    mre.wait();
    // loop остановился
    EXPECT_EQ(event_loop.get_stop_flag(), true);
    // в очереди остались сообщения
    EXPECT_EQ(q.empty(), false);
}

TEST(EVENT_LOOP, EVENT_LOOP_START_CMD)
{
    using namespace engine;
    threadsafe_q<command_shared> q;
    loop event_loop(q);

    start_loop start_loop(event_loop);
    start_loop.execute();

    auto cmd = std::make_shared<mock_command>();
    EXPECT_CALL(*cmd, execute());
    q.push(cmd);
    q.push(std::make_shared<loop::hard_stop>(event_loop));
}


TEST(EVENT_LOOP, EVENT_LOOP_SOFT_STOP_CMD)
{
    using namespace engine;
    threadsafe_q<command_shared> q;
    loop event_loop(q);

    start_loop start_loop(event_loop);

    auto cmd = std::make_shared<mock_command>();
    EXPECT_CALL(*cmd, execute()).Times(2);

    manual_reset_event mre;

    q.push(cmd);
    q.push(std::make_shared<loop::soft_stop>(event_loop, [&mre]{
        mre.set();
    }));
    q.push(cmd);

    start_loop.execute();
    mre.wait();

    EXPECT_EQ(event_loop.get_stop_flag(), true);
    EXPECT_EQ(q.empty(), true);
}

#endif //EVENT_LOOP_TESTS_H
