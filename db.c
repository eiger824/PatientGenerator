#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "db.h"
#include "def.h"

// Must-have macro for getline function
#define _GNU_SOURCE

#define NR_PARAMS   9

static dll_t * db_list = NULL; // List to use as db
static dll_t * tmp_list = NULL; // List to return to other file scopes

static int params_to_search[NR_PARAMS] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
static char * param_names[NR_PARAMS] =
{
    "age",
    "sex",
    "hta",
    "hsa",
    "inc",
    "fisher",
    "glasg",
    "wfns",
    "treat"
};

static int nr = 0;

// These are useful when selecting ranges
static int db_min_age = 0;
static int db_max_age = 0;

void db_init(person_t * p, int nr_persons, int min_age, int max_age)
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
    free(p);
    // Update min & max ages
    db_min_age = min_age;
    db_max_age = max_age;
}

dll_t * db_query_all(int flags, int * vals)
{
    uint8_t age = -1;
    int8_t sex = -1;
    int8_t hta = -1;
    int8_t hsa = -1;
    int8_t inc = -1;
    int8_t fisher = -1;
    int glasg = -1;
    int8_t wfns = -1;
    int8_t treat = -1;

    // See which args were passed onto the function
    for (unsigned i=0; i<NR_PARAMS; ++i)
    {
        int cval = *vals++;
        if (cval != -1)
        {
            switch (i)
            {
                case 0:
                    age = cval;
                    break;
                case 1:
                    sex = cval;
                    break;
                case 2:
                    hta = cval;
                    break;
                case 3:
                    hsa = cval;
                    break;
                case 4:
                    inc = cval;
                    break;
                case 5:
                    fisher = cval;
                    break;
                case 6:
                    glasg = cval;
                    break;
                case 7:
                    wfns = cval;
                    break;
                case 8:
                    treat = cval;
                    break;
                default:
                    break;
            }
        }
    }

    // Free before making a new copy
    if (tmp_list)
        dll_destroy(tmp_list);

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
    if ((flags & FISHER) == FISHER)
    {
        dll_select_all_from(tmp_list, FISHER, fisher);
#ifdef DEBUG_ENABLED
        printf("Selected FISHER, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & GLASG) == GLASG)
    {
        dll_select_all_from(tmp_list, GLASG, glasg);
#ifdef DEBUG_ENABLED
        printf("Selected GLASG, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & WFNS) == WFNS)
    {
        dll_select_all_from(tmp_list, WFNS, wfns);
#ifdef DEBUG_ENABLED
        printf("Selected WFNS, count now:\t%d\n", tmp_list->count);
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

    return tmp_list;
}

int db_query(int flags, const char *fmt, ...)
{
    uint8_t age = -1;
    int8_t sex = -1;
    int8_t hta = -1;
    int8_t hsa = -1;
    int8_t inc = -1;
    int8_t fisher = -1;
    int glasg = -1;
    int8_t wfns = -1;
    int8_t treat = -1;

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
            fisher = va_arg(args, int);
        else if (*fmt == '6')
            glasg = va_arg(args, int);
        else if (*fmt == '7')
            wfns = va_arg(args, int);
        else if (*fmt == '8')
            treat = va_arg(args, int);
        ++fmt;
    }
    // Free list
    va_end(args);

    // Free before making a new copy
    if (tmp_list)
        dll_destroy(tmp_list);

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
    if ((flags & FISHER) == FISHER)
    {
        dll_select_all_from(tmp_list, FISHER, fisher);
#ifdef DEBUG_ENABLED
        printf("Selected FISHER, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & GLASG) == GLASG)
    {
        dll_select_all_from(tmp_list, GLASG, glasg);
#ifdef DEBUG_ENABLED
        printf("Selected GLASG, count now:\t%d\n", tmp_list->count);
#endif
    }
    if ((flags & WFNS) == WFNS)
    {
        dll_select_all_from(tmp_list, WFNS, wfns);
#ifdef DEBUG_ENABLED
        printf("Selected WFNS, count now:\t%d\n", tmp_list->count);
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
    dll_destroy(db_list);
    // Free this list if any queries were made
    if (tmp_list)
        dll_destroy(tmp_list);
}


void db_help()
{
    printf("\nWelcome to the minimal patient database!\n");
    printf("\nPlease introduce your search queries in the following format:\n");
    printf("\n\t\t\tparam=key\n\n");
    printf("List of available params:\tage,sex,hta,hsa,inc,fisher,glasg,wfns,treat\n");
    printf("List of available keys:\t\t0,1,2,... (for age), M (for male), F (for female), Y (for YES), N (for NO), L (for light), M (for moderate), S (for severe)\n");
    printf("List of available commands:\n");
    printf("\nexit/quit/end:\tTerminate database\n");
    printf("go:\t\tPerform the search - returns just the number of hits\n");
    printf("show:\t\tPerform the search - returns the whole list of hits\n");
    printf("list:\t\tList all the ready-to-process parameters\n");
    printf("clean:\t\tClean all input parameters\n");
    printf("rm:\t\tRemoves a parameter from the search list (example: rm age)\n");
    printf("\nGood luck!\n\n");
}

void db_interactive_mode()
{
    // In this mode, we want to enter params (keys + values) in the following form:
    //
    //              key=param
    //
    // And we start the search by hitting:
    //
    //              go / show
    //
    // And we exit with
    //
    //              exit
    //
    char *line = NULL; 
    size_t len = 0;
    ssize_t nread;
    int retcode;

    db_help();

    printf("[db] ");
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
        db_help();
    }
    else if (!strcmp(line, "go") || !strcmp(line, "show"))
    {
        int which = (!strcmp(line, "go") ? 0 : 1);
        // Check if any params in stack
        if (nr > 0)
        {
            int *tmp = params_to_search;
            int flags = 0;

            // Build flags && printing buffer
            char * print_buffer = (char * ) malloc (1000);
            strcpy(print_buffer, "[db] Patients: ");

            for (unsigned i=0; i<NR_PARAMS; ++i)
            {
                if (params_to_search[i] != -1)
                {
                    switch (i)
                    {
                        case 0:
                            flags |= AGE;
                            strcat(print_buffer, "with age ");
                            char age[10];
                            sprintf(age, "%d, ", params_to_search[i]);
                            strcat(print_buffer, age);
                            break;
                        case 1:
                            flags |= SEX;
                            strcat(print_buffer, (params_to_search[i] == 'M' ? "MALE, ":"FEMALE, "));
                            break;
                        case 2:
                            flags |= HTA;
                            strcat(print_buffer, "with HTA ");
                            strcat(print_buffer, (params_to_search[i] == 'Y' ? "positive, ":"negative, "));
                            break;
                        case 3:
                            flags |= HSA;
                            strcat(print_buffer, "with HSA ");
                            strcat(print_buffer, (params_to_search[i] == 'Y' ? "positive, ":"negative, "));
                            break;
                        case 4:
                            flags |= INC;
                            strcat(print_buffer, "with INC ");
                            strcat(print_buffer, (params_to_search[i] == 'Y' ? "positive, ":"negative, "));
                            break;
                        case 5:
                            flags |= FISHER;
                            strcat(print_buffer, "with FISHER ");
                            char fish[10];
                            sprintf(fish, "%d, ", params_to_search[i]);
                            strcat(print_buffer, fish);
                            break;
                        case 6:
                            flags |= GLASG;
                            strcat(print_buffer, "with GLASG ");
                            switch (params_to_search[i])
                            {
                                case 'N':
                                    strcat(print_buffer, " none, ");
                                    break;
                                case 'L':
                                    strcat(print_buffer, " light, ");
                                    break;
                                case 'M':
                                    strcat(print_buffer, " moderate, ");
                                    break;
                                case 'S':
                                    strcat(print_buffer, " severe, ");
                                    break;
                            }
                            break;
                        case 7:
                            flags |= WFNS;
                            strcat(print_buffer, "with WFNS ");
                            char wfns[10];
                            sprintf(wfns, "%d, ", params_to_search[i]);
                            strcat(print_buffer, wfns);
                            break;
                        case 8:
                            flags |= TREAT;
                            strcat(print_buffer, "with treatment ");
                            strcat(print_buffer, (params_to_search[i] == 'A' ? "A, ":"B, "));
                            break;
                        default:
                            break;
                    }
                }
            }
            // Chop off last two chars
            print_buffer[strlen(print_buffer) - 2] = 0;
            printf("%s:", print_buffer);
            // Make the query
            dll_t * tmplist = db_query_all(flags, tmp);
            if (!which)
            {
                printf("\t%d\n", tmplist->count);
            }
            else
            {
                // Iterate through the list
                printf("\n");
                dll_print(tmplist);
            }
            free(print_buffer);
        }
        else
        {
            if (!which)
            {
                printf("Total number of patients\t%d\n", db_list->count);
            }
            else
            {
                printf("\n");
                dll_print(db_list);
            }
        }
    }
    else if (!strcmp(line, "clean"))
    {
        for (unsigned i=0; i<NR_PARAMS; ++i)
        {
            params_to_search[i] = -1;
        }
        nr = 0;
    }
    else if (strstr(line, "rm") == line)
    {
        // Let's check its validity
        // Format should be rm param
        if (strlen(line) > 3)
        {
            char *sp = strchr(line, ' ');
            if (sp)
            {
                size_t diff = sp - line;
                if (diff == 2 && strlen(line) > 3) // Space must not be at the end
                {
                    char *p = ++sp;
                    // Check if param is correct
                    unsigned i;
                    for (i=0; i<NR_PARAMS; ++i)
                    {
                        if (!strcmp(param_names[i], p))
                            break;
                    }
                    // i should hold the param name
                    if (i < NR_PARAMS)
                    {
                        if (params_to_search[i] != -1)
                        {
                            params_to_search[i] = -1;
                            nr--;
                        }
                        else
                        {
                            fprintf(stderr,
                                    "Param '%s' not in search list!\n", p);
                        }
                    }
                    else
                    {
                        fprintf(stderr,
                                "Wrong param '%s'. Type 'help' to see available params\n", p);
                    }
                }
            }
            else
            {
                fprintf(stderr,
                        "[db] Wrong use of 'rm'. Type 'help' to see how it's used\n");
            }
        }
        else
        {
            fprintf(stderr,
                    "[db] Wrong use of 'rm'. Type 'help' to see how it's used\n");
        }
    }
    else if (!strcmp(line, "list"))
    {
        if (nr > 0)
        {
            // Print ready-to-analyze params
            printf("Params. ready to be analized:\n");
            for (int i=0; i<NR_PARAMS; ++i)
            {
                if (params_to_search[i] != -1)
                {
                    printf("%s - ", param_names[i]);
                    if (i == 0)
                        printf("%d\n", params_to_search[i]);
                    else
                        printf("%c\n", params_to_search[i]);
                }
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
                int i;
                for (i=0; i<NR_PARAMS; ++i)
                {
                    if (!strcmp(line, param_names[i]))
                        break;
                }
                // 'i' should hold the position now
                if (i < NR_PARAMS)
                {
                    // Check if available
                    if (params_to_search[i] == -1)
                    {
                        if (i == 0 || i == 7 || i == 5)
                        {
                            // Check input range
                            int a = atoi(++delim);
                            if (i == 0)
                            {
                                if (a < db_min_age || a > db_max_age)
                                {
                                    fprintf(stderr,
                                            "[db] Param value \"%d\" is out of range [%d-%d]. Try again!\n",
                                            a, db_min_age, db_max_age);
                                }
                                else
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                            }
                            else if (i == 7)
                            {
                                if (a < WFNS_MIN || a > WFNS_MAX)
                                {
                                    fprintf(stderr,
                                            "[db] Param value \"%d\" is out of range [%d-%d]. Try again!\n",
                                            a, WFNS_MIN, WFNS_MAX);
                                }
                                else
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                            }
                            else
                            {
                                if (a < FISHER_MIN || a > FISHER_MAX)
                                {
                                    fprintf(stderr,
                                            "[db] Param value \"%d\" is out of range [%d-%d]. Try again!\n",
                                            a, FISHER_MIN, FISHER_MAX);
                                }
                                else
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                            }
                        }
                        else
                        {
                            char a = *++delim;
                            if (i == 1) //  Only M/F
                            {
                                if (a == 'M' || a == 'F')
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                                else
                                {
                                    fprintf(stderr,
                                            "[db] Param value '%c' is illegal. Possible values: M,F. Try again\n", a);
                                }
                            }
                            else if (i >= 2 && i <= 5)
                            {
                                if (a == 'Y' || a == 'N')
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                                else
                                {
                                    fprintf(stderr,
                                            "[db] Param value '%c' is illegal. Possible values: Y,N. Try again\n", a);
                                }
                            }
                            else if (i == 6) // Three types: N, L, M, S
                            {
                                if (a == 'N' || a == 'L' || a == 'M' || a == 'S')
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                                else
                                {
                                    fprintf(stderr,
                                            "[db] Param value '%c' is illegal. Possible values: N,L,M,S. Try again\n", a);
                                }
                            }
                            else
                            {
                                if (a == 'A' || a == 'B')
                                {
                                    params_to_search[i] = a;
                                    nr++;
                                }
                                else
                                {
                                    fprintf(stderr,
                                            "[db] Param value '%c' is illegal. Possible values: A,B. Try again\n", a);
                                }
                            }
                        }
                    }
                    else
                    {
                        fprintf(stderr,
                                "[db] Param \"%s\" is already set. Run 'clean' to start again or keep adding other params!\n",
                                line);
                    }
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

