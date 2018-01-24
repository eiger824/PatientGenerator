#include <stdarg.h>

#include "db.h"
#include "def.h"

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

dll_t * db_query(int flags, const char *fmt, ...)
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

    // Init list by copy
    dll_t *tmp_list =  dll_copy_list(db_list);

    // Parse flags
    if ((flags & AGE) == AGE)
    {
#ifdef DEBUG_ENABLED
        printf("Will select age\n");
#endif
        // Loop through list and push every match into tmp_list
        printf("Count now: %d\n", tmp_list->count);
        dll_node_t * nd = tmp_list->first;
        dll_node_t *tmp = nd;
        while (nd != tmp_list->last->next)
        {
            if (nd->p->age != age)
            {
                tmp = nd->next;
                dll_delete(tmp_list, nd);
                nd = tmp;
            }
            else
            {
                nd = nd->next;
                tmp = nd;
            }
        }
        printf("Count now: %d\n", tmp_list->count);
    }
    if ((flags & SEX) == SEX)
    {
#ifdef DEBUG_ENABLED
        printf("Will select sex\n");
#endif
    }
    if ((flags & HTA) == HTA)
    {
#ifdef DEBUG_ENABLED
        printf("Will select HTA\n");
#endif
    }
    if ((flags & HSA) == HSA)
    {
#ifdef DEBUG_ENABLED
        printf("Will select HSA\n");
#endif
    }
    if ((flags & INC) == INC)
    {
#ifdef DEBUG_ENABLED
        printf("Will select INC\n");
#endif
    }
    if ((flags & TREAT) == TREAT)
    {
#ifdef DEBUG_ENABLED
        printf("Will select TREAT\n");
#endif
    }
    else
    {
        // Wrong flag, just return
        return NULL;
    }


    // Return 0 if everything went well
    return tmp_list;
}

void db_free()
{
    // Do nothing for the moment
    free(db_list);
}

