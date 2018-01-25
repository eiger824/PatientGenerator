#include <stdarg.h>
#include <stdlib.h>

#include "db.h"
#include "def.h"

dll_t *tmp_list = NULL; // List to return to other file scope

void db_init(person_t * p, int nr_persons)
{
    // Do nothing for the moment
    db_list = dll_init();
    person_t * q = p;
    for (int i=0; i< nr_persons; ++i)
    {
        dll_insert_end(db_list, q++);
    }
#ifdef DEBUG_ENABLED
    dll_print(db_list);
#endif
}

int db_query(int flags, const char *fmt, ...)
{
    int age = -1;
    char sex = -1;
    char hta = -1;
    char hsa = -1;
    char inc = -1;
    char treat = -1;

    // Init variadic args
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0')
    {
        if (*fmt == '0')
            age = va_arg(args, int);
        else if (*fmt == '1')
            sex = va_arg(args, int);
        else if (*fmt == '2')
            hta = va_arg(args, int);
        else if (*fmt == '3')
            hsa = va_arg(args, int);
        else if (*fmt == '4')
            inc = va_arg(args, int);
        else if (*fmt == '5')
            treat = va_arg(args, int);
        ++fmt;
    }

    if (tmp_list)
        free(tmp_list);
    // Init list by copy
    tmp_list =  dll_copy_list(db_list);
#ifdef DEBUG_ENABLED
    printf("Initial count:\t%d\n", tmp_list->count);
#endif

    // Parse flags
    if ((flags & AGE) == AGE)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, AGE, age);
#ifdef DEBUG_ENABLED
        printf("Selected AGE, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & SEX) == SEX)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, SEX, sex);
#ifdef DEBUG_ENABLED
        printf("Selected SEX, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & HTA) == HTA)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, HTA, hta);
#ifdef DEBUG_ENABLED
        printf("Selected HTA, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & HSA) == HSA)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, HSA, hsa);
#ifdef DEBUG_ENABLED
        printf("Selected HSA, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & INC) == INC)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, INC, inc);
#ifdef DEBUG_ENABLED
        printf("Selected INC, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & TREAT) == TREAT)
    {
        // Loop through list and remove all non-matches from tmp_list
        dll_select_all_from(tmp_list, TREAT, sex);
#ifdef DEBUG_ENABLED
        printf("Selected TREAT, count now:\t%d\n", tmp_list->count);
#endif
    }

    return tmp_list->count;
}

void db_free()
{
    // Do nothing for the moment
    free(db_list);
    free(tmp_list);
}

