#ifndef LOOP_H
#define LOOP_H

#include "threadsafe_q.h"
#include <commands/command.h>
#include <condition_variable>
#include <functional>
#include <thread>

namespace engine
{
    class loop
    {
        using action = std::function<void()>;

    public:
        loop(threadsafe_q<command_shared> &q);

        ~loop();

        int start();

        void stop();

        void set_behavior(const action &&behavior);

        inline bool get_stop_flag() const {return stopFlag;}

    private:
        void loop_processor();
        bool stopFlag;
        std::condition_variable cv;
        mutable std::mutex mtx;
        std::thread thr;
        engine::threadsafe_q<command_shared> &q;
        action behavior;

    public:
        class hard_stop : public command
        {
        public:
            explicit hard_stop(
                loop &loop, action &&callback = [] {})
                : _loop(loop), callback(callback)
            {
            }
            inline void execute() override
            {
                _loop.stopFlag = true;
                callback();
            }

        private:
            loop &_loop;
            action callback;
        };

        class soft_stop : public command
        {
        public:
            explicit soft_stop(
                loop &loop, action &&callback = [] {})
                : _loop(loop), callback(callback)
            {
            }

            void execute() override;

        private:
            loop &_loop;
            action callback;
    };
};
} // namespace engine

#endif // LOOP_H
