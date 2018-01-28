#ifndef PERSON_H_
#define PERSON_H_

#include <stdint.h>

typedef enum glasgow_type
{
    NONE = 0,
    LIGHT,
    MODERATE,
    SEVERE
} gtype_t;

typedef struct person_type
{
    uint8_t age;
    int8_t sex;
    int8_t hta;
    int8_t hsa;
    int8_t inc;
    int8_t rank;
    gtype_t glasg;
    int8_t wfns;
    int8_t treat;
} person_t;

#endif /* PERSON_H_ */
