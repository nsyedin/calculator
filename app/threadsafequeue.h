#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
    using Lock = std::unique_lock<std::mutex>;
public:
    ThreadSafeQueue() = default;

    int size() const
    {
        Lock lock(m_mutex);
        return m_queue.size();
    }

    void push(const T& t)
    {
        Lock lock(m_mutex);
        m_queue.push(t);
        m_condVar.notify_one();
    }

    T pop()
    {
        Lock lock(m_mutex);
        m_condVar.wait(lock, [this]() { return m_queue.empty(); });
        T t = m_queue.front();
        m_queue.pop();
        return t;
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};

#endif // THREADSAFEQUEUE_H
