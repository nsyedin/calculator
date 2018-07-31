#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include <QObject>
#include <thread>
#include "threadsafequeue.h"

class RequestThread : public QObject, ISizeChangedListener
{
    Q_OBJECT
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

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

    int size() const
    {
        return m_requests.size();
    }

    virtual void newSizeRecieved(int value) override
    {
        emit sizeChanged(value);
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
    void sizeChanged(int value);

private:
    std::thread m_thread;
    bool m_isDone;
    int m_timeout;
    ThreadSafeQueue<QString>& m_requests;
    ThreadSafeQueue<double>& m_results;
};

#endif // REQUESTTHREAD_H
