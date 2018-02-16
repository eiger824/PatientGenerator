#ifndef HTML_H_
#define HTML_H_

#include <stdio.h>

#include "person.h"

int html_create(person_t * list, unsigned nr_persons);

void html_fill_header(FILE * fp);
void html_fill_end(FILE * fp);

#endif /* HTML_H_ */
