#include "requestthread.h"
#include <iostream>
#include "resultthread.h"

RequestThread::RequestThread(ResultThread *pResultThread, QObject *parent)
: QObject(parent),
  m_isNotified(false),
  m_isDone(false),
  m_pResultThread(pResultThread),
  m_queueSize(0),
  m_timeout(0)
{

}

RequestThread::~RequestThread()
{
    stop();
}

void RequestThread::start()
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
                CalcFunc f = m_queue.front();
                m_queue.pop_front();
                std::thread calcThread([this, f]()
                {
                    Error error = Error::NONE;
                    double result = f(error);

                    std::this_thread::sleep_for(std::chrono::seconds(m_timeout));
                    std::cout << "Calculated result: " << result << std::endl;

                    m_pResultThread->add(result);

                });
                calcThread.detach();
                m_queueSize = m_queue.size();
                emit queueSizeChanged(m_queueSize);
            }
            m_isNotified = false;
        }
    });
    m_thread.swap(tmp);
}

void RequestThread::stop()
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

void RequestThread::add(QString operation, QString a, QString b)
{
    Operation op = Operation::NONE;
    if (operation == "+")
    {
        op = Operation::ADD;
    }
    else if (operation == "-")
    {
        op = Operation::SUB;
    }
    else if (operation == "*")
    {
        op = Operation::MUL;
    }
    else if (operation == "/")
    {
        op = Operation::DIV;
    }

    CalcFunc f = std::bind(calculate, op, a.toDouble(), b.toDouble(), std::placeholders::_1);

    {
        Lock lock(m_mutex);
        m_queue.push_back(f);

        m_queueSize = m_queue.size();

        m_isNotified = true;
    }

    m_condVar.notify_one();
    emit queueSizeChanged(m_queueSize);
}
