#ifndef RESULTTHREAD_H
#define RESULTTHREAD_H

#include <QObject>
#include <thread>
#include "threadsafequeue.h"

class ResultThread : public QObject
{
    Q_OBJECT

    typedef std::unique_lock<std::mutex> Lock;
public:
    explicit ResultThread(ThreadSafeQueue<double>& results,
                          QObject *parent = nullptr);
    ~ResultThread();

    Q_INVOKABLE void start();
private:
    std::thread m_thread;
    bool m_isDone;
    ThreadSafeQueue<double>& m_results;
};

#endif // RESULTTHREAD_H
