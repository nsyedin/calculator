#include "requestthread.h"
#include <iostream>
#include <chrono>
#include "calc.h"

RequestThread::RequestThread(ThreadSafeQueue<QString>& requests,
                       ThreadSafeQueue<double>& results,
                       QObject *parent)
    : QObject(parent),
      m_isDone(false),
      m_timeout(0),
      m_requests(requests),
      m_results(results)
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
            for (char cc : { '+', '-', '*', '/' })
            {
                index = expr.indexOf(QChar(cc));
                if (index != -1)
                {
                    c = cc;
                    break;
                }
            }

            Operation op = Operation::NONE;
            switch (c)
            {
                case '+':
                    op = Operation::ADD;
                    break;
                case '-':
                    op = Operation::SUB;
                    break;
                case '*':
                    op = Operation::MUL;
                    break;
                case '/':
                    op = Operation::DIV;
                    break;
            }

            double arg1 = expr.left(index).toDouble();
            double arg2 = expr.right(expr.size() - index).toDouble();

            static Error error = Error::NONE;
            double result = calculate(op, arg1, arg2, error);

            std::cout << "Got request: " << expr.toStdString();

            // Calculation
            std::this_thread::sleep_for(std::chrono::seconds(m_timeout));

            m_results.push(result);
        }
    });
    m_thread.swap(tmp);
}
