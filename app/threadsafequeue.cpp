#include "threadsafequeue.h"

ThreadSafeQueue::ThreadSafeQueue(QObject *parent) : QObject(parent)
{
}

template<type T>
ThreadSafeQueue::push(const T& t)
{
    {
        Lock lock(m_mutex);
        m_queue.push(t);
        m_size = m_queue.size();
    }
    emit sizeChanged(m_size);
    m_condVar.notify_one();
}

template<type T>
T ThreadSafeQueue::pop()
{
    T t;
    {
        Lock lock;
        m_condVar.wait_for(lock, [this](){ m_queue.empty() });
        T t = m_queue.front();
        m_queue.pop();
    }
    emit sizeChanged(m_size);
    return t;
}

