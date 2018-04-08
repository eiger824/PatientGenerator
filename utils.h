#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <math.h>

typedef enum utils_op_type
{
    UNKWNOWN,
    PROCENT,
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION,
    DIVISION
} op_type_t;

// Functions
op_type_t   utils_get_op_type(const char * str_op);
double      utils_procent(int a,     int b);
double      utils_add    (double a,  double b);
double      utils_subs   (double a,  double b);
double      utils_mult   (double a,  double b);
double      utils_div    (double a,  double b);
int         parse_val(const char * msg, const char * error_msg);

#endif /* UTILS_H_ */
