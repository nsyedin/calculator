#ifndef CALC_H
#define CALC_H

#include "calc_global.h"

enum class Operation : int
{
    NONE,
    ADD,
    SUB,
    MUL,
    DIV
};

enum class Error : int
{
    NONE,
    DIVISION_BY_ZERO,
    INVALID_OPERATION
};


extern "C" CALCSHARED_EXPORT double calculate(Operation op, double a, double b, Error& error);

#endif // CALC_H
