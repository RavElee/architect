
#include <exception_handler.h>
#include <loop.h>

namespace engine
{

    loop::loop(threadsafe_q<command_shared> &q)
        : stopFlag(true), q(q)
    {
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
        q.push(std::make_shared<loop::command_stop>(*this));
    }

    void loop::loop_processor()
    {
        while (!stopFlag)
        {
            auto cmd = q.wait_and_pop();

            // if (!cmd)
            //     continue;

            try
            {
                cmd->execute();
            }
            catch (const std::exception &e)
            {
                engine::exception_handler::instance().handle(cmd, e)->execute();
            }
        }
    }
} // namespace engine
