#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Files to use
#define		OUT_FILE		"all.txt"
#define 	AGES_FILE		"ages.txt"
#define		SEXES_FILE		"sexes.txt"
#define 	HTA_FILE		"hta.txt"
#define		HSA_FILE		"hsa.txt"
#define		INC_FILE		"incid.txt"
#define 	TREATMENT_FILE	"treatment.txt"

typedef struct person_type
{
	int age;
	char sex;
	char hta;
	char hsa;
	char inc;
	char treat;
} person_t;

typedef enum param_type
{
	AGE = 0,
	SEX,
	HTA,
	HSA,
	INC,
	TREAT
} param_t;

// Ptr to array of people
static person_t *subjects;

void acknowledgments()
{
	printf("Developed by Carlos Pagola, January 2018\n\n");
}

void dump_statistics(int nr_persons)
{
	printf("\n****************************************\n");
	printf("Statistics of examined patients\n");
	printf("Number of patients in the study:\t%d\n", nr_persons);
	printf("****************************************\n");
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
		break:
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
	// Write to file
	fprintf(f, "----------- Patient %d -----------\n", index + 1);
	
	fprintf(f, "Age:\t\t%d\n", ptr->age);
	print_separate_file(AGE, ptr->age);
	
	fprintf(f, "Sex:\t\t%c\n", ptr->sex);
	print_separate_file(SEX, ptr->sex);
	
	fprintf(f, "HTA:\t\t%c\n", ptr->hta);
	print_separate_file(HTA, ptr->hta);
	
	fprintf(f, "HSA:\t\t%c\n", ptr->hsa);
	print_separate_file(HSA, ptr->hsa);
	
	fprintf(f, "Incid.:\t\t%c\n", ptr->inc);
	print_separate_file(INC, ptr->inc);
	
	fprintf(f, "Treatment:\t%c\n", ptr->treat);
	print_separate_file(TREAT, ptr->treat);
	
	fprintf(f, "----------------------------------\n");
	// And close it
	fclose(f);
	return 0;
}


int main(int argc, char * argv[])
{
	int nr_persons;
	int min_age;
	int max_age;
	
	
	// Initialize random seed
	srand (time (NULL));
	
	// Show some (real) acknowledgments ...
	acknowledgments();
	
	// Input some data!
	printf("Enter number of patients: ");
	scanf("%d", &nr_persons);
	printf("Enter age range (MIN): ");
	scanf("%d", &min_age);
	printf("Enter age range (MAX): ");
	scanf("%d", &max_age);
	
	subjects = (person_t *) malloc (sizeof *subjects * nr_persons);
	
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
	// Output some statistics
	dump_statistics();
	// Free memory
	free(subjects);
	exit(0);
}
