#ifndef PERSON_H_
#define PERSON_H_

typedef enum glasgow_type
{
    NONE = 0,
    LIGHT,
    MODERATE,
    SEVERE
} gtype_t;

typedef struct person_type
{
    int age;
    char sex;
    char hta;
    char hsa;
    char inc;
    char rank;
    gtype_t glasg;
    char treat;
} person_t;

#endif /* PERSON_H_ */
