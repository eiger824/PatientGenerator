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

// Files to use
#define		OUT_FILE		"txts/all.txt"
#define 	AGES_FILE		"txts/ages.txt"
#define		SEXES_FILE		"txts/sexes.txt"
#define 	HTA_FILE		"txts/hta.txt"
#define		HSA_FILE		"txts/hsa.txt"
#define		INC_FILE		"txts/incid.txt"
#define 	TREATMENT_FILE		"txts/treatment.txt"

// Ptr to array of people
static person_t *subjects;
// Global computation time
static struct timeval timer;

void acknowledgments()
{
    printf("Developed by Carlos Pagola, January 2018, version 0.2\n");
}

double get_simulation_seconds()
{
    struct timeval time_now;
    gettimeofday(&time_now, NULL);

    return (double) (time_now.tv_sec - timer.tv_sec) +
        (double) (time_now.tv_usec - timer.tv_usec) / 1e6;
}

void dump_statistics(int nr_persons)
{
    printf("\n*****************************************************************\n");
    printf("Done! Elapsed time: %.3f seconds\n", get_simulation_seconds());
    printf("Statistics of examined patients\n");
    printf("\nNumber of patients in the study:\t%d\n", nr_persons);
    printf("\n*****************************************************************\n");

    dll_t * result = db_query(AGE, "0", 14);
}

int print_separate_file(param_t p, int val)
{
    //Open file first
    char fname[100];
    switch (p)
    {
        case AGE:
            strcpy(fname, AGES_FILE);
            break;
        case SEX:
            strcpy(fname, SEXES_FILE);
            break;
        case HTA:
            strcpy(fname, HTA_FILE);
            break;
        case HSA:
            strcpy(fname, HSA_FILE);
            break;
        case INC:
            strcpy(fname, INC_FILE);
            break;
        case TREAT:
            strcpy(fname, TREATMENT_FILE);
            break;
        default:
            fprintf(stderr, "Unrecognized parameter\n");
            return -1;
    }
    FILE *fp = fopen(fname, "a+");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    if (p == AGE)
    {
        fprintf(fp, "%d\n", val);
    }
    else
    {
        fprintf(fp, "%c\n", val);
    }
    fclose(fp);
    return 0;
}


int print_to_file(const char *fname, const person_t * ptr, unsigned index)
{
    // Open file first
    FILE *f = fopen(fname, "a+");
    if (f == NULL)
    {
        perror("Error opening file");
        return -1;
    }


    // New write
    if (ptr == NULL)
    {
        fprintf(f, "Patient\tAge\t\tSex\t\tHTA\t\tHSA\t\tInc\t\tTreat\n");
        fprintf(f, "-------------------------------------------------------\n");
    }
    else
    {
        fprintf(f, "%d\t\t%d\t\t%c\t\t%c\t\t%c\t\t%c\t\t%c\n",
                index + 1,
                ptr->age,
                ptr->sex,
                ptr->hta,
                ptr->hsa,
                ptr->inc,
                ptr->treat);
        fprintf(f, "-------------------------------------------------------\n");

        // Print individual files
        print_separate_file(AGE, ptr->age);
        print_separate_file(SEX, ptr->sex);
        print_separate_file(HTA, ptr->hta);
        print_separate_file(HSA, ptr->hsa);
        print_separate_file(INC, ptr->inc);
        print_separate_file(TREAT, ptr->treat);
    }
    // And close it
    fclose(f);
    return 0;
}

void help()
{
    printf("USAGE: test nNM|v|h\n");
    printf("-h\tShow this help and exit\n");
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
    int c;

    while ((c = getopt(argc, argv, "m:M:n:hv")) != -1)
    {
        switch (c)
        {
            case 'h':
                help();
                exit(0);
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

    subjects = (person_t *) malloc (sizeof *subjects * nr_persons);

    // Init time struct
    gettimeofday(&timer, NULL);
    // First line
    print_to_file(OUT_FILE, NULL, 0);
    for (int i=0; i<nr_persons; ++i)
    {
        subjects[i].age = min_age + rand() % (max_age + 1 - min_age);
        subjects[i].sex = (rand() < RAND_MAX / 2) ? 'M' : 'F';
        subjects[i].hta = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].hsa = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].inc = (rand() < RAND_MAX / 2) ? 'Y' : 'N';
        subjects[i].treat = (rand() < RAND_MAX / 2) ? 'A' : 'B';
        // Print the whole person entry
        print_to_file(OUT_FILE, &subjects[i], i);
    }
    // Init db
    db_init(subjects, nr_persons);
    // Output some statistics
    dump_statistics(nr_persons);
    // Free memory
    db_free();
    exit(0);
}
