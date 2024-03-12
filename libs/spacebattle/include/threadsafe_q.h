#ifndef THREADSAFE_Q_H
#define THREADSAFE_Q_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <cassert>

namespace engine
{

    template <class T>
    class threadsafe_q
    {
    public :
        threadsafe_q() = default;
        ~threadsafe_q() = default;

        // cppcheck-suppress missingMemberCopy
        threadsafe_q(const threadsafe_q &other) noexcept
        {
            std::lock_guard<std::mutex> lk(other.mut);
            data_queue = other.data_queue;
        }

        threadsafe_q &operator=(const threadsafe_q &other) = delete;

        void push(T &value)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(value);
            data_cond.notify_one(); // data_cond.notify_all();
        }

        bool try_pop(T &value)
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return false;

            value = data_queue.front();
            data_queue.pop();

            return true;
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return std::shared_ptr<T>();

            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }

        void wait_and_pop(T &value)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
            value = data_queue.front();
            data_queue.pop();
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.empty();
        }

        size_t size() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.size();
        }

    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    };


    template <class T>
    class threadsafe_q<std::shared_ptr<T>>
    {
    public :
        threadsafe_q() = default;
        ~threadsafe_q() = default;

        threadsafe_q(const threadsafe_q &other) noexcept
        {
            std::lock_guard<std::mutex> lk(other.mut);
            data_queue = other.data_queue;
        }

        threadsafe_q &operator=(const threadsafe_q &other) = delete;

        void push(std::shared_ptr<T> value)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(value);
            data_cond.notify_one(); // data_cond.notify_all();
        }

        bool try_pop(T &value)
        {
            assert(0);
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return false;

            value = data_queue.front();
            data_queue.pop();

            return true;
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return std::shared_ptr<T>();

            std::shared_ptr<T> res(data_queue.front());
            data_queue.pop();
            return res;
        }

        void wait_and_pop(T &value)
        {
            assert(0);
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
            value = data_queue.front();
            data_queue.pop();
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
            // using namespace std::literals;
            // auto st = data_cond.wait_for(lk, 10us, [this] { return !data_queue.empty(); });
            // if (st == false)
            //     return std::shared_ptr<T>();

            std::shared_ptr<T> res(data_queue.front());
            data_queue.pop();
            return res;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.empty();
        }

        size_t size() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.size();
        }

    private:
        mutable std::mutex mut;
        std::queue<std::shared_ptr<T>> data_queue;
        std::condition_variable data_cond;
    };
} // namespace system

#endif // THREADSAFE_Q_H
