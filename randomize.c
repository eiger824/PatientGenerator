#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
	int sex;
	int hta;
	int hsa;
	int inc;
	int treat;
} person_t;

void acknowledgments()
{
	printf("Developed by Carlos Pagola, January 2018\n\n");
}

int print_to_file(const char *fname, const char *format, ...)
{
	// Init variadic list
	va_list args;
	va_start(args, format);
	
	// Open file first
	FILE *f = fopen(fname, "w+");
	if (f == NULL)
	{
		perror("Error opening file");
		return -1;
	}
	// Write to file
	vfprintf(f, format, args);
	// And close it
	fclose(f);
	// Free memory
	va_end(args);
	return 0;
}

int main(int argc, char * argv[])
{
	FILE *fp; // Dump all patients on a pretty list
	FILE *ages;
	FILE *sexes;
	FILE *htas;
	FILE *hsas;
	FILE *incs;
	FILE *treats;
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
	
	for (int i=0; i<nr_persons; ++i)
	{
		print_to_file(OUT_FILE, "----------- Patient %d -----------\n", i + 1);
		print_to_file(OUT_FILE, "Age:\t\t%d\n", min_age + rand() % (max_age + 1 - min_age));
		print_to_file(OUT_FILE, "Sex:\t\t%s\n", (rand() < RAND_MAX / 2) ? "M" : "F");
		print_to_file(OUT_FILE, "HTA:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		print_to_file(OUT_FILE, "HSA:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		print_to_file(OUT_FILE, "Incid.:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		print_to_file(OUT_FILE, "Treatment:\t%s\n", (rand() < RAND_MAX / 2) ? "A" : "B");
		print_to_file(OUT_FILE, "----------------------------------\n");
		/*
		fprintf(fp, "----------- Patient %d -----------\n", i + 1);
		fprintf(fp, "Age:\t\t%d\n", min_age + rand() % (max_age + 1 - min_age));
		fprintf(fp, "Sex:\t\t%s\n", (rand() < RAND_MAX / 2) ? "M" : "F");
		fprintf(fp, "HTA:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		fprintf(fp, "HSA:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		fprintf(fp, "Incid.:\t\t%s\n", (rand() < RAND_MAX / 2) ? "Y" : "N");
		fprintf(fp, "Treatment:\t%s\n", (rand() < RAND_MAX / 2) ? "A" : "B");
		fprintf(fp, "----------------------------------\n");
		*/
	}
	exit(0);
}
