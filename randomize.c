#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>

#include "person.h"
#include "def.h"
#include "dll.h"
#include "db.h"
#include "timelib.h"
#include "files.h"


// Ptr to array of people
static person_t *subjects;

void acknowledgments()
{
    printf("Developed by Carlos Pagola, January 2018, version 0.2\n");
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
        printf("Done! Elapsed time: %.3f seconds\n", time_get_sim_seconds());
        printf("Statistics of examined patients\n");
        printf("\nNumber of patients in the study:\t%d\n", nr_persons);
        // Let's print some stats!
        int patients_18 = db_query(AGE, "0", 18);
        printf("Patients of age 18:\t\t\t%d (%.2f%%)\n",
                patients_18, 100 * ((float)patients_18 / (float)nr_persons));
        int patients_18_hta_yes = db_query(AGE | HTA, "02", 18, 'Y');
        printf("Patients of age 18 with HTA positive:\t%d (%.2f%%)\n",
                patients_18_hta_yes, 100 * ((float)patients_18_hta_yes / (float)patients_18));
        printf("\n*****************************************************************\n");
    }

}

void help()
{
    printf("USAGE: test nNM|v|h\n");
    printf("-h\tShow this help and exit\n");
    printf("-i\tRun database search in interactive mode\n");
    printf("-n\tSet number of patients\n");
    printf("-m\tSet minimum age\n");
    printf("-M\tSet maximum age\n");
    printf("-v\tShow version information and exit\n");
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
                help();
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

    // Initialize random seed
    srand (time (NULL));

    // Show some (real) acknowledgments ...
    acknowledgments();

    // Input some data!
    if (nr_persons == -1)
    {
        printf("Enter number of patients: ");
        scanf("%d", &nr_persons);
    }
    if (min_age == -1)
    {
        printf("Enter age range (MIN): ");
        scanf("%d", &min_age);
    }
    if (max_age == -1)
    {
        printf("Enter age range (MAX): ");
        scanf("%d", &max_age);
    }
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
        subjects[i].hsa = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].inc = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].rank = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        // depending on hsa, which glasgow level
        if (subjects[i].hsa == 'Y')
        {

            subjects[i].glasg = (gtype_t) (1 + rand() % 3);
        }
        else
        {
            subjects[i].glasg = NONE;
        }
        subjects[i].treat = (rand() < RAND_MAX / 2) ? 'A' : 'B';
        // Print the whole person entry
        print_to_file(OUT_FILE, &subjects[i], i);
    }
    // Init db
    db_init(subjects, nr_persons, min_age, max_age);
    // Output some statistics
    dump_statistics(nr_persons, interactive);
    // Free memory
    db_free();
    exit(0);
}
