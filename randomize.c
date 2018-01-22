#include <stdio.h>
#include <stdlib.h>
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

void acknowledgments()
{
	printf("Developed by Carlos Pagola, January 2018\n\n");
}

int print_to_file(const char *fname, const person_t * ptr, unsigned index)
{
	// Open file first
	FILE *f = fopen(fname, "w+");
	if (f == NULL)
	{
		perror("Error opening file");
		return -1;
	}
	// Write to file
	print_to_file(OUT_FILE, "----------- Patient %d -----------\n", index + 1);
	print_to_file(OUT_FILE, "Age:\t\t%d\n", ptr->age);
	print_to_file(OUT_FILE, "Sex:\t\t%s\n", ptr->sex);
	print_to_file(OUT_FILE, "HTA:\t\t%s\n", ptr->hta);
	print_to_file(OUT_FILE, "HSA:\t\t%s\n", ptr->hsa);
	print_to_file(OUT_FILE, "Incid.:\t\t%s\n", ptr->inc);
	print_to_file(OUT_FILE, "Treatment:\t%s\n", ptr->treat);
	print_to_file(OUT_FILE, "----------------------------------\n");
	// And close it
	fclose(f);
	return 0;
}

int main(int argc, char * argv[])
{
	int nr_persons;
	int min_age;
	int max_age;
	// Ptr to array of people
	person_t *subjects;
	
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
		print_to_file(OUT_FILE, subjects[i], i);
	}
	// Free memory
	free(subjects)
	exit(0);
}
