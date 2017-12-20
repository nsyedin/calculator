#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <QObject>
#include <queue>
#include <mutex>
#include <condition_variable>

template<type T>
class ThreadSafeQueue : public QObject
{
    typedef std::unique_lock<std::mutex> Lock;

    Q_OBJECT
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit ThreadSafeQueue(QObject *parent = nullptr);

    int size() const
    {
        return m_size;
    }

    Q_INVOKABLE push(const T& t);
    T pop();

signals:
    void sizeChanged(int size);

private:
    int m_size;
    std::queue m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};

#endif // THREADSAFEQUEUE_H
