#ifndef __DOUBLYLINKEDLIST_H
#define __DOUBLYLINKEDLIST_H

#include "person.h"
#include "def.h"

typedef struct dll_node_type
{
    person_t * p;
    struct dll_node_type *next;
    struct dll_node_type *prev;

} dll_node_t;

typedef struct dll_type
{
    dll_node_t *first;
    dll_node_t *last;

    int count;

} dll_t;

dll_t *dll_init(void);
void dll_destroy(dll_t *dlls);

void dll_insert_after(dll_t *dlls, dll_node_t *node, person_t * p);
void dll_insert_before(dll_t *dlls, dll_node_t *node, person_t * p);

void dll_insert_beginning(dll_t *dlls, person_t * p); 
void dll_insert_end(dll_t *dlls, person_t * p); 

void dll_remove(dll_t *dlls, dll_node_t *node, person_t * p);
void dll_delete(dll_t *dlls, dll_node_t *node); 

void dll_print(dll_t *dlls);

void dll_empty(dll_t *dlls);
dll_t * dll_copy_list(dll_t * rhs);
void dll_select_all_from(dll_t * list, param_t param, int val);

#endif /* __DOUBLYLINKEDLIST_H */
