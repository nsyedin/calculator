#ifndef RESULTTHREAD_H
#define RESULTTHREAD_H

#include <QObject>
#include <thread>
#include <mutex>
#include <condition_variable>

class ResultThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int queueSize READ queueSize NOTIFY queueSizeChanged)

    typedef std::unique_lock<std::mutex> Lock;
public:
    explicit ResultThread(QObject *parent = nullptr);
    ~ResultThread();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    void add(double result);

    int queueSize() const
    {
        return m_queueSize;
    }

signals:
    void queueSizeChanged(int queueSize);

private:
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_isNotified;
    bool m_isDone;

    std::list<double> m_queue;
    int m_queueSize;
};

#endif // RESULTTHREAD_H
