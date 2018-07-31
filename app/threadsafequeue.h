#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

class ISizeChangedListener
{
public:
    virtual ~ISizeChangedListener() {}
    virtual void newSizeRecieved(int value) = 0;
};

template <typename T>
class ThreadSafeQueue
{
    using Lock = std::unique_lock<std::mutex>;
public:
    ThreadSafeQueue()
        : m_pSizeChangedListener(nullptr)
    {
    }

    void push(const T& t)
    {
        Lock lock(m_mutex);
        m_queue.push(t);
        if (m_pSizeChangedListener)
        {
            m_pSizeChangedListener->newSizeRecieved(m_queue.size());
        }
        m_condVar.notify_one();
    }

    T pop()
    {
        Lock lock(m_mutex);
        m_condVar.wait(lock, [this]() { return m_queue.empty(); });
        T t = m_queue.front();
        m_queue.pop();
        if (m_pSizeChangedListener)
        {
            m_pSizeChangedListener->newSizeRecieved(m_queue.size());
        }
        return t;
    }

    int size()
    {
        Lock lock(m_mutex);
        return m_queue.size();
    }

    void setSizeChangedListener(ISizeChangedListener* listener)
    {
        m_pSizeChangedListener = listener;
    }

private:
    std::queue<T>            m_queue;
    std::mutex               m_mutex;
    std::condition_variable  m_condVar;
    ISizeChangedListener*    m_pSizeChangedListener;
};

#endif // THREADSAFEQUEUE_H
