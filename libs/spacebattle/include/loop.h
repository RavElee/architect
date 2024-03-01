#ifndef LOOP_H
#define LOOP_H

#include <commands/command.h>
#include "threadsafe_q.h"
#include <condition_variable>
#include <thread>

namespace engine
{
    class loop
    {
    public:
        loop(threadsafe_q<command_shared>& q);

        ~loop();

        int start();

        void stop();

    private:
        void loop_processor();
        bool stopFlag;
        std::condition_variable cv;
        mutable std::mutex mtx;
        std::thread thr;
        engine::threadsafe_q<command_shared>& q;

        class command_stop : public command
        {
        public:
            command_stop(loop& loop):_loop(loop){}
            void execute() override {
                _loop.stopFlag = true;
            }
        private:
            loop& _loop;
        };
    };
} // namespace engine

#endif // LOOP_H
