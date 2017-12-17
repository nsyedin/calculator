#ifndef CALC_H
#define CALC_H

#include "calc_global.h"

enum class Operation : int
{
    ADD,
    SUB,
    MUL,
    DIV
};

enum class Error : int
{
    NO_ERROR,
    INVALID_ARGUMENT,
    INVALID_OPERATION
};


extern "C" CALCSHARED_EXPORT double calculate(Operation op, double a, double b, Error& error);

#endif // CALC_H
