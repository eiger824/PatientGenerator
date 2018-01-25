#ifndef DB_H_
#define DB_H_

#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

static dll_t * db_list = NULL;

void db_init(person_t * p, int nr_persons);
int db_query(int flags, const char *fmt, ...);
void db_free();


#endif /* DB_H_ */
