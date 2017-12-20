#include "requestthread.h"
#include <iostream>
#include <chrono>
#include "calc.h"

RequestThread::RequestThread(ResultThread *pResultThread, QObject *parent)
: QObject(parent),
  m_isDone(false),
  m_timeout(0)
{

}

RequestThread::~RequestThread()
{
    m_isDone = true;
    m_thread.join();
}

void RequestThread::start()
{
    std::thread tmp([this]()
    {
        while (!m_isDone)
        {
            QString expr = m_requests.pop();
            int index = 0;
            char c;
            for (QChar op : { "+", "-", "*", "/" })
            {
                index = expr.indexOf(op);
                if (index != -1)
                {
                    c = op.toLatin1();
                    break;
                }
            }

            double arg1 = expr.left(index).toDouble();
            double arg2 = expr.right(expr.size() - index).toDouble();
            double result = calculate(op, arg1, arg2);

            std::cout << "Got request: " << expr.toStdString();

            // Calculation
            std::this_thread::sleep_for(std::chrono::seconds(m_timeout));

            m_results.push(result);
        }
    });
    m_thread.swap(tmp);
}
