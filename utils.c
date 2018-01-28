#include "utils.h"

op_type_t   utils_get_op_type(const char * str_op)
{
    op_type_t op =  UNKWNOWN;
    const char *q = str_op;
    return op;
}

double utils_procent(int a, int b)
{
    return 100 * (double) a / (double) b;
}

double utils_add(double a, double b)
{
    return a + b;
}

double utils_subs (double a,  double b)
{
    return a - b;
}

double utils_mult (double a, double b)
{
    return a * b;
}

double utils_div (double a,  double b)
{
    return a / b;
}
