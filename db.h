#ifndef DB_H_
#define DB_H_

#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

void db_init(person_t * p, int nr_persons, int min_age, int max_age);
int db_query(int flags, const char *fmt, ...);
// Another variant when running interactively
dll_t * db_query_all(int flags, int * vals);
void db_free();

// Fancy interactive mode
void db_interactive_mode();
int db_parse_query(char * line);
int db_check_line_format(char *line);


#endif /* DB_H_ */
