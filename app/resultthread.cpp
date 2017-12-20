#include "resultthread.h"
#include <iostream>

ResultThread::ResultThread(QObject *parent)
    : QObject(parent),
      m_isNotified(false),
      m_isDone(false),
      m_queueSize(0)
{
}

ResultThread::~ResultThread()
{
    stop();
}

void ResultThread::start()
{
    std::thread tmp([this]()
    {
        Lock lock(m_mutex);
        while (!m_isDone)
        {
            while (!m_isNotified)
            {
                m_condVar.wait(lock);
            }

            while (!m_queue.empty())
            {
                double result = m_queue.front();
                m_queue.pop_front();

                m_queueSize = m_queue.size();
                emit queueSizeChanged(m_queueSize);

                std::cout << "Got result: " << result << std::endl;
            }
            m_isNotified = false;
        }
    });
    m_thread.swap(tmp);
}

void ResultThread::stop()
{
    if (!m_isDone)
    {
        {
            Lock lock(m_mutex);
            m_isNotified = true;
            m_isDone = true;
        }
        m_condVar.notify_one();
        m_thread.join();
    }
}

void ResultThread::add(double result)
{
    {
        Lock lock(m_mutex);
        m_queue.push_back(result);

        m_queueSize = m_queue.size();

        m_isNotified = true;
    }

    m_condVar.notify_one();
    emit queueSizeChanged(m_queueSize);
}
