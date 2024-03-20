#ifndef MANUAL_RESET_EVENT_H
#define MANUAL_RESET_EVENT_H

#include <mutex>
#include <condition_variable>

class manual_reset_event{
public:
    void set()
    {
        cv.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> ul(mtx);
        cv.wait(ul);
    }
private:
    std::condition_variable cv;
    std::mutex mtx;
};

#endif //MANUAL_RESET_EVENT_H
