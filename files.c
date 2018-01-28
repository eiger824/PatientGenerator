#include <stdio.h>
#include <string.h>

#include "files.h"

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
        case RANK:
            strcpy(fname, RANK_FILE);
            break;
        case GLASG:
            strcpy(fname, GLASG_FILE);
            break;
        case WFNS:
            strcpy(fname, WFNS_FILE);
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
    if (p == AGE || p == WFNS)
    {
        fprintf(fp, "%d\n", val);
    }
    else if (p == GLASG)
    {
        switch (val)
        {
            case NONE:
                fprintf(fp, "  --  \n");
                break;
            case LIGHT:
                fprintf(fp, "Light\n");
                break;
            case MODERATE:
                fprintf(fp, "Moderate\n");
                break;
            case SEVERE:
                fprintf(fp, "Severe\n");
                break;
        }
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
        fprintf(f, "Patient\tAge\tSex\tHTA\tHSA\tIncident Rankin\tGlasgow\t\tWFNS\tTreat\n");
        fprintf(f, "-------------------------------------------");
        fprintf(f, "-------------------------------------------\n");
    }
    else
    {
        char glasgow_type[100];
        switch (ptr->glasg)
        {
            case NONE:
                strcpy(glasgow_type, "   --   ");
                break;
            case LIGHT:
                strcpy(glasgow_type, "  Light ");
                break;
            case MODERATE:
                strcpy(glasgow_type, "Moderate");
                break;
            case SEVERE:
                strcpy(glasgow_type, " Severe ");
                break;
        }
        fprintf(f, "%d\t%d\t%c\t%c\t%c\t%c\t %c\t%s\t%c\t%c\n",
                index + 1,
                ptr->age,
                ptr->sex,
                ptr->hta,
                ptr->hsa,
                ptr->inc,
                ptr->rank,
                glasgow_type,
                (ptr->wfns == '-' ? ptr->wfns : ptr->wfns + 48),
                ptr->treat);
        fprintf(f, "-------------------------------------------");
        fprintf(f, "-------------------------------------------\n");

        // Print individual files
        print_separate_file(AGE, ptr->age);
        print_separate_file(SEX, ptr->sex);
        print_separate_file(HTA, ptr->hta);
        print_separate_file(HSA, ptr->hsa);
        print_separate_file(INC, ptr->inc);
        print_separate_file(RANK, ptr->rank);
        print_separate_file(GLASG, ptr->glasg);
        print_separate_file(WFNS, ptr->wfns);
        print_separate_file(TREAT, ptr->treat);
    }
    // And close it
    fclose(f);
    return 0;
}
