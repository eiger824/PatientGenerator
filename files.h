#ifndef FOPS_H_
#define FOPS_H_

#include "def.h"
#include "person.h"

int print_separate_file(param_t p, int val);
int print_to_file(const char *fname, const person_t * ptr, unsigned index);

#endif /* FOPS_H_ */
