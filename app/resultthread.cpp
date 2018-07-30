#include "resultthread.h"
#include <iostream>

ResultThread::ResultThread(ThreadSafeQueue<double>& results, QObject *parent)
    : QObject(parent),
      m_isDone(false),
      m_results(results)
{
}

ResultThread::~ResultThread()
{
    m_isDone = true;
    m_thread.join();
}

void ResultThread::start()
{
    std::thread tmp([this]()
    {
        while (!m_isDone)
        {
            double result = m_results.pop();
            std::cout << "Got result: " << result;
        }
    });
    m_thread.swap(tmp);
}
