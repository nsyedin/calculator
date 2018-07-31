#ifndef RESULTTHREAD_H
#define RESULTTHREAD_H

#include <QObject>
#include <thread>
#include "threadsafequeue.h"

class ResultThread : public QObject, ISizeChangedListener
{
    Q_OBJECT
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit ResultThread(ThreadSafeQueue<double>& results,
                          QObject *parent = nullptr);
    ~ResultThread();

    Q_INVOKABLE void start();

    int size() const
    {
        return m_results.size();
    }

    virtual void newSizeRecieved(int value) override
    {
        emit sizeChanged(value);
    }

signals:
    void sizeChanged(int value);

private:
    std::thread m_thread;
    bool m_isDone;
    ThreadSafeQueue<double>& m_results;
};

#endif // RESULTTHREAD_H
