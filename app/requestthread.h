#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include <QObject>
#include <thread>
#include "threadsafequeue.h"

class RequestThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

public:
    explicit RequestThread(ThreadSafeQueue<QString>& requests,
                           ThreadSafeQueue<double>& results,
                           QObject *parent = nullptr);
    ~RequestThread();

    void start();

    int timeout() const
    {
        return m_timeout;
    }

public slots:
    void setTimeout(int timeout)
    {   
        if (m_timeout == timeout)
            return;

        m_timeout = timeout;

        emit timeoutChanged(m_timeout);
    }

signals:
    void timeoutChanged(int timeout);

private:
    std::thread m_thread;
    bool m_isDone;
    int m_timeout;
    ThreadSafeQueue<QString>& m_requests;
    ThreadSafeQueue<double>& m_results;
};

#endif // REQUESTTHREAD_H
