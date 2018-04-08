#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#include <libgen.h>
#include <getopt.h>

#include "person.h"
#include "def.h"
#include "dll.h"
#include "db.h"
#include "html.h"
#include "timelib.h"
#include "files.h"
#include "utils.h"


// Ptr to array of people
static person_t *subjects;

void acknowledgments()
{
    printf("Developed by Carlos Pagola, January 2018, version 0.4\n");
}

void dump_statistics(int nr_persons, int interactive)
{
    if (interactive)
    {
        // Enter interactive mode
        db_interactive_mode();
    }
    else
    {
        printf("\n*****************************************************************\n");
        printf("Done! %d patients were generated in %.3f seconds\n",
                nr_persons, time_get_sim_seconds());
        printf("(See all files under txts/ directory and the html/patients.html file)\n");
        printf("*****************************************************************\n");
    }

}

void help(char * program)
{
    printf("USAGE: %s nNM|v|h\n", basename(program));
    printf("-h\tShow this help and exit\n");
    printf("-i\tRun database search in interactive mode\n");
    printf("-n\tSet number of patients\n");
    printf("-m\tSet minimum age\n");
    printf("-M\tSet maximum age\n");
    printf("-v\tShow version information and exit\n");
    printf("\nEXAMPLES:\n");
    printf("%s\t\t\tRun the tool and exit after generation. Patient data will be asked to the user\n",
            basename(program));
    printf("%s -i\t\t\tRun the tool and enter interactive database mode after generation. Patient data will be asked to the user\n",
            basename(program));
    printf("%s -n 100 -m 18 -M 90\tRun the tool by specifying number of patients and age range\n",
            basename(program));

}

int main(int argc, char * argv[])
{
    int nr_persons = -1;
    int min_age = -1;
    int max_age = -1;
    int interactive = 0; // Interactive mode
    int c;

    while ((c = getopt(argc, argv, "im:M:n:hv")) != -1)
    {
        switch (c)
        {
            case 'h':
                help(argv[0]);
                exit(0);
            case 'i':
                interactive = 1;
                break;
            case 'v':
                acknowledgments();
                exit(0);
            case 'm':
                min_age = atoi(optarg);
                break;
            case 'M':
                max_age = atoi(optarg);
                break;
            case 'n':
                nr_persons = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Wrong option -- %c\n", c);
                exit(1);
        }
    }

    if (optind < argc)
    {
        for (int i = optind; i < argc; i++)
        {
            printf ("Non-option argument -- '%s'\n", argv[i]);
        }
        help(argv[0]);
        exit(1);
    }

    // Initialize random seed
    srand (time (NULL));

    // Show some (real) acknowledgments ...
    acknowledgments();

    // Input some data!
    if (nr_persons == -1)
        nr_persons = parse_val("Enter number of patients: ", "(Please enter a positive number)");
    if (min_age == -1)
        min_age = parse_val("Enter age range (MIN): ", "(Please enter a minimum age greater than 1)");
    if (max_age == -1)
        max_age = parse_val("Enter age range (MAX): ", "(Please enter a maximum age greater than 1)");

    // Check that min < max
    if (min_age > max_age)
    {
        fprintf(stderr, "Wrong range: min age must be smaller than max age!\n");
        exit(2);
    }

    subjects = (person_t *) malloc (sizeof *subjects * nr_persons);

    time_start_timer();
    // First line
    print_to_file(OUT_FILE, NULL, 0);
    for (int i=0; i<nr_persons; ++i)
    {
        subjects[i].age = min_age + rand() % (max_age + 1 - min_age);
        subjects[i].sex = (rand() < RAND_MAX / 2) ? 'M' : 'F';
        subjects[i].hta = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].sah = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        // depending on sah, which glasgow level
        if (subjects[i].sah == 'Y')
        {
            subjects[i].inc = 'N';
            subjects[i].fisher = FISHER_MIN + rand() % (FISHER_MAX + 1 - FISHER_MIN);
            subjects[i].glasg = (gtype_t) (GLASG_MIN + rand() % (GLASG_MAX + 1 - GLASG_MIN));
            subjects[i].wfns = WFNS_MIN + rand() % (WFNS_MAX + 1 - WFNS_MIN);
        }
        else
        {
            subjects[i].inc = 'Y';
            subjects[i].fisher = '-';
            subjects[i].glasg = NONE;
            subjects[i].wfns = '-';
        }
        subjects[i].treat = (rand() < RAND_MAX / 2) ? 'A' : 'B';
        // Print the whole person entry
        print_to_file(OUT_FILE, &subjects[i], i);
    }
    // Create html
    html_export(subjects, nr_persons, min_age, max_age);
    // Init db
    db_init(subjects, nr_persons, min_age, max_age);
    // Output some statistics
    dump_statistics(nr_persons, interactive);
    // Free memory
    db_free();
    exit(0);
}
