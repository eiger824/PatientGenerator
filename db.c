#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "db.h"
#include "def.h"

// Must-have macro for getline function
#define _GNU_SOURCE

static dll_t * db_list = NULL; // List to use as db
static dll_t * tmp_list = NULL; // List to return to other file scopes

static int params_to_search[6] = {-1};
static char * param_names[6] =
{
    "age",
    "sex",
    "hta",
    "hsa",
    "inc",
    "treat"
};

static int nr = 0;

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
        dll_select_all_from(tmp_list, TREAT, treat);
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

void db_interactive_mode()
{
    // In this mode, we want to enter params (keys + values) in the following form:
    //
    //              key=param
    //
    // And we start the search by hitting:
    //
    //              go
    //
    // And we exit with
    //
    //              exit
    //
    char *line = NULL; 
    size_t len = 0;
    ssize_t nread;
    int retcode;

    printf("\nWelcome to the minimal patient database!\n");
    printf("\nPlease introduce your search queries in the following format:\n");
    printf("\n\t\t\tparam=key\n\n");
    printf("List of available params:\tage,sex,hta,hsa,inc,treat\n");
    printf("List of available keys:\t\t0,1,2,... (for age), M (for male), F (for female), Y (for YES), N (for NO)\n");
    printf("\nGood luck!\n\n");

    while (( nread = getline(&line, &len, stdin)) != -1)
    {
        if (( retcode = db_parse_query(line)) == -1)
            break;
        printf("[db] ");
    }
    // Free line
    free(line);
}

int db_parse_query(char * line)
{
    // Chop last char
    line[strlen(line) - 1] = 0;
    if (!strcmp(line, "exit") ||
            !strcmp(line, "quit") ||
            !strcmp(line, "end")) return -1;
    else if (!strcmp(line, "help"))
    {
        printf("Available commands:\n\n");
        printf("exit/quit/end:\tTerminate database\n");
        printf("go:\t\tPerform the search\n");
        printf("list:\t\tList all the ready-to-process parameters\n");
        printf("clean:\t\tClean all input parameters\n\n");
    }
    else if (!strcmp(line, "go"))
    {
        // Check if any params in stack
        if (nr > 0)
        {
            // And empty the params
            for (unsigned i=0; i<nr; ++i)
            {
                params_to_search[i] = -1;
            }
            nr = 0;
        }
        else
        {
            printf("[db] Enter some search parameters first\n");
        }
    }
    else if (!strcmp(line, "clean"))
    {
        for (unsigned i=0; i<nr; ++i)
        {
            params_to_search[i] = -1;
        }
        nr = 0;
    }
    else if (!strcmp(line, "list"))
    {
        if (nr > 0)
        {
            // Print ready-to-analyze params
            printf("Params. ready to be analized:\n");
            for (int i=0; i<nr; ++i)
            {
                if (params_to_search[i] != -1)
                    printf("%s - %d\n", param_names[i], params_to_search[i]);
            }
        }
        else
        {
            printf("[db] Enter some search parameters first\n");
        }
    }
    else
    {
        // See if format is OK
        int retcode;
        if ( (retcode = db_check_line_format(line)) == -1)
        {
            fprintf(stderr, "[db] Wrong format: \"%s\" -- Format must be 'key=param' (no spaces, commas, etc)\n", line);        
        }
        else
        {
            if (!retcode) // If it was 0
            {
                // Get the actual param
                char *delim = strchr(line, '=');
                size_t diff = delim - line;
                line[diff] = 0;
                printf("Line was:%s\n", line);
                int i;
                for (i=0; i<6; ++i)
                {
                    if (!strcmp(line, param_names[i]))
                        break;
                }
                // 'i' should hold the position now
                if (i < 6)
                {
                    if (i == 0)
                        params_to_search[i] = atoi(++delim);
                    else
                        params_to_search[i] = *++delim;
                    nr++;
                }
                else
                {
                    fprintf(stderr, "[db] Wrong parameter: \"%s\" -- See help\n", line);
                }
            }
        }
    }
    return 0;
}

int db_check_line_format(char *line)
{
    // Just allow empty lines (consecutive 'angry' empty hits ;-)
    if (!strlen(line)) return 2;
    // Below follow restrictions
    if (!line) return -1;
    // Format should be XXX=YYY
    char *eq = strchr(line, '=');
    if (    !eq ||                              /* '=' not found */
            eq == line ||                       /* Found at the beginning */
            eq == (line + strlen(line)-1) ||    /* Found at the end */
            strchr(line, ' '))                  /* Space was found */
        return -1; // Not found
    // Otherwise return 0
    return 0;
}

