#ifndef HTML_H_
#define HTML_H_

#include <stdio.h>

#include "person.h"

int html_export(person_t * list, unsigned nr_persons, int min_age, int max_age);

void html_fill_header(FILE * fp);
void html_fill_end(FILE * fp);
void html_set_fieldset(FILE * fp, unsigned nr_persons, int min_age, int max_age);
void html_add_line(FILE * fp, const char * msg, ...);
void html_fill_table(FILE * fp, person_t * list, unsigned nr_persons);
void html_add_scripts(FILE * fp);

#endif /* HTML_H_ */
