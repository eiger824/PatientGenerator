#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

dll_t *dll_init(void)
{
	dll_t *dlls = (dll_t *) malloc(sizeof(dll_t));
	dlls->first = NULL;
	dlls->last = NULL;
	dlls->count = 0;
	return dlls;
}

void dll_destroy(dll_t *dlls)
{
	dll_empty(dlls);
	free(dlls);
}

void dll_insert_after(dll_t *dlls, dll_node_t *node, person_t * p)
{
	dll_node_t *new_node = (dll_node_t *) malloc(sizeof(dll_node_t));
	dlls->count++;
	new_node->prev = node;
	new_node->next = node->next;
	if (node->next == NULL)
	{
		dlls->last = new_node;
	}
	else
	{
		node->next->prev = new_node;
	}
	node->next = new_node;
    new_node->p = p;
}

void dll_insert_before(dll_t *dlls, dll_node_t *node, person_t * p)
{
	dll_node_t *new_node = (dll_node_t *) malloc(sizeof(dll_node_t));
	dlls->count++;
	new_node->prev = node->prev;
	new_node->next = node;
	if (node->prev == NULL)
	{
		dlls->first = new_node;
	}
	else
	{
		node->prev->next = new_node;
	}
	node->prev = new_node;
    new_node->p = p;
}

void dll_insert_beginning(dll_t *dlls, person_t * p)
{
	if (dlls->first == NULL)
	{
		dll_node_t *new_node = (dll_node_t *) malloc(sizeof(dll_node_t));
		dlls->count++;
		dlls->first = new_node;
		dlls->last = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
        new_node->p = p;
	}
	else
	{
        dll_insert_before(dlls, dlls->first, p);
	}
}

void dll_insert_end(dll_t *dlls, person_t * p)
{
	if (dlls->last == NULL)
	{
        dll_insert_beginning(dlls, p);
	}
	else
	{
        dll_insert_after(dlls, dlls->last, p);
	}
}

void dll_remove(dll_t *dlls, dll_node_t *node, person_t * p)
{
    p = node->p;
	dll_delete(dlls, node);
}

void dll_delete(dll_t *dlls, dll_node_t *node)
{
	if (node->prev == NULL)
	{
		dlls->first = node->next;
	}
	else
	{
		node->prev->next = node->next;
	}
	if (node->next == NULL)
	{
		dlls->last = node->prev;
	}
	else
	{
		node->next->prev = node->prev;
	}
//     free(node->p);
	free(node);
	dlls->count--;
}

void dll_empty(dll_t *dlls)
{
	dll_node_t *temp_first_node;
	while(dlls->first != NULL)
	{
		temp_first_node = dlls->first;
		dlls->first = dlls->first->next;
        free(temp_first_node->p);
		free(temp_first_node);
	}
	dlls->count = 0;
	dlls->last = NULL;
}

void dll_print(dll_t *dlls)
{
    dll_node_t * node = dlls->first;
    while (node != dlls->last->next)
    {
        person_t * ptr = node->p;
        printf("Age: %d, Sex: %c, HTA: %c, HSA: %c, Inc: %c, Treat: %c\n",
                ptr->age,
                ptr->sex,
                ptr->hta,
                ptr->hsa,
                ptr->inc,
                ptr->treat);
        node = node->next;
    }
}

dll_t * dll_copy_list(dll_t * rhs)
{
    dll_t * list = dll_init();
    dll_node_t * nd = rhs->first;
    while (nd != rhs->last->next)
    {
        dll_insert_end(list, nd->p);
        nd = nd->next;
    }
    return list;
}

void dll_select_all_from(dll_t * list, param_t param, int val)
{
    // Do stuff if something in the list
    if (!list->count) return;

    dll_node_t * nd = list->first;
    dll_node_t *tmp = nd;
    int which = -1;
    while (nd != list->last->next)
    {
        switch (param)
        {
            case AGE:
                which = nd->p->age;
                break;
            case SEX:
                which = nd->p->sex;
                break;
            case HTA:
                which = nd->p->hta;
                break;
            case HSA:
                which = nd->p->hsa;
                break;
            case INC:
                which = nd->p->inc;
                break;
            case TREAT:
                which = nd->p->treat;
                break;
            default:
                break;
        }
        if (which != val)
        {
                tmp = nd->next;
                dll_delete(list, nd);
                nd = tmp;
        }
        else
        {
            nd = nd->next;
            tmp = nd;
        }
        if (!list->count) break;
    }
}
