#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include <QObject>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <list>
#include "calc.h"

class ResultThread;

class RequestThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int queueSize READ queueSize NOTIFY queueSizeChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

    typedef std::unique_lock<std::mutex> Lock;

public:
    typedef std::function<double(Error&)> CalcFunc;

    explicit RequestThread(ResultThread *pResultThread, QObject *parent = nullptr);
    ~RequestThread();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE void add(QString operation, QString a, QString b);

    int queueSize() const
    {
        return m_queueSize;
    }

    int timeout() const
    {
        return m_timeout;
    }

public slots:
    void setTimeout(int timeout)
    {   
        if (m_timeout == timeout)
            return;

        {
            Lock lock(m_mutex);
            m_timeout = timeout;
        }

        emit timeoutChanged(m_timeout);
    }

signals:
    void queueSizeChanged(int queueSize);
    void timeoutChanged(int timeout);

private:
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_isNotified;
    bool m_isDone;

    std::list<CalcFunc> m_queue;
    int m_queueSize;

    int m_timeout;
    ResultThread *m_pResultThread;
};

#endif // REQUESTTHREAD_H
