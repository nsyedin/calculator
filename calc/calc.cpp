#include "calc.h"
#include <iostream>
#include <math.h>

double calculate(Operation op, double a, double b, Error& error)
{
    std::cout << "calculate!" << std::endl;
    switch (op)
    {
        case Operation::ADD:
            return a + b;
        case Operation::SUB:
            return a - b;
        case Operation::MUL:
            return a * b;
        case Operation::DIV:
            if (abs(b) < 1e-7)
            {
                error = Error::DIVISION_BY_ZERO;
                return 0.0;
            }
            return a / b;
        default:
            error = Error::INVALID_OPERATION;
    }

    return 0.0;
}
