#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int parse_val(const char * msg, const char * error_msg)
{
    int out = -1;
    int error = 0;
    char input[100];
    for (;;)
    {
        memset(input, 0, 100);
        printf("%s", msg);
        scanf("%s", input);
        size_t i = 0;
        while (i < strlen(input))
        {
            char c = input[i++];
            if (!isdigit(c) && c != '-' && c != '+')
            {
                fprintf(stderr, "%s\n", error_msg);
                error = 1;
                break;
            }
            error = 0;
        }
        if (!error)
        {
            out = atoi(input);
            // Last check:
            if (out <= 0)
            {
                fprintf(stderr, "%s\n", error_msg);
                error = 1;
            }
            else
            {
                break;
            }
        }
    }
    return out;
}
