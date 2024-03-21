
#include <exception_handler.h>
#include <loop.h>

namespace engine
{

    loop::loop(threadsafe_q<command_shared> &q) : stopFlag(true), q(q)
    {
        behavior = [this] {
            auto cmd = this->q.wait_and_pop();

            try
            {
                cmd->execute();
            }
            catch (const std::exception &e)
            {
                engine::exception_handler::instance().handle(cmd, e)->execute();
            }
        };
    }

    loop::~loop()
    {
        // stop();
        if (thr.joinable())
            thr.join();
    }

    int loop::start()
    {
        if (stopFlag == false)
            return -1;
        stopFlag = false;
        thr = std::thread(&loop::loop_processor, this);
        return 0;
    }

    void loop::stop()
    {
        q.push(std::make_shared<loop::soft_stop>(*this));
    }

    void loop::set_behavior(const std::function<void()> &&behavior)
    {
        this->behavior = behavior;
    }

    void loop::loop_processor()
    {
        while (!stopFlag)
        {
            behavior();
        }
    }

    void loop::soft_stop::execute()
    {
        _loop.set_behavior([this]() {
            if (_loop.q.empty())
            {
                _loop.stopFlag = true;
                callback();
                return;
            }

            auto cmd = _loop.q.wait_and_pop();
            try
            {
                cmd->execute();
            }
            catch (const std::exception &e)
            {
                engine::exception_handler::instance().handle(cmd, e)->execute();
            }
        });
    }

} // namespace engine
