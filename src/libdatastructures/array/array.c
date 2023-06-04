/**
 * \file   array.c
 * \brief  Array data structure - functions definitions
 */

#include <stdlib.h>
#include "libdatastructures/array/array-node.h"
#include "libdatastructures/array/array.h"

/* ************************************************************************************************/

void array_init(array_s *a, size_t length)
{
    if (NULL != a) {
        *(size_t *)&a->length = length;
        a->count = 0;

        a->elems = (array_node_s **)calloc((size_t)length, sizeof(array_node_s *));
    }

    return;
}

/* ************************************************************************************************/

array_s *array_new(size_t length)
{
    array_s *a = (array_s *)malloc(sizeof(array_s));

    array_init(a, length);

    return a;
}

/* ************************************************************************************************/

array_rc_e array_push_back(array_s *a, void *elem)
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (a->count == a->length)
        return ARRAY_RC_FULL;

    a->elems[a->count] = array_node_new(elem);
    a->count++;

    return ARRAY_RC_OK;
}

/* ************************************************************************************************/

array_rc_e array_push_front(array_s *a, void *elem)
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (a->count == a->length)
        return ARRAY_RC_FULL;

    for (int i = (int)a->count; i > 0; i--)
        a->elems[i] = a->elems[i - 1];

    a->elems[0] = array_node_new(elem);
    a->count++;

    return ARRAY_RC_OK;
}

/* ************************************************************************************************/

array_rc_e array_push_at(array_s *a, void *elem, int pos)
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (a->count == a->length)
        return ARRAY_RC_FULL;

    if (pos < 0 || pos > (int)a->count)
        return ARRAY_RC_INVALID_POS;

    for (int i = (int)a->count; i > pos; i--)
        a->elems[i] = a->elems[i - 1];

    a->elems[pos] = array_node_new(elem);
    a->count++;

    return ARRAY_RC_OK;
}

/* ************************************************************************************************/

size_t array_count(array_s *a)
{
    if (NULL == a)
        return 0;

    return a->count;
}

/* ************************************************************************************************/

void *array_pick_back(array_s *a)
{
    if (NULL == a || a->count < 1)
        return NULL;

    return a->elems[a->count - 1]->elem;
}

/* ************************************************************************************************/

void *array_pick_front(array_s *a)
{
    if (NULL == a || a->count < 1)
        return NULL;

    return a->elems[0]->elem;
}

/* ************************************************************************************************/

void *array_pick_at(array_s *a, int pos)
{
    if (NULL == a || pos < 0 || pos > (int)a->count - 1)
        return NULL;

    return a->elems[pos]->elem;
}

/* ************************************************************************************************/

void *array_pop_back(array_s *a)
{
    if (NULL == a || a->count < 1)
        return NULL;

    void *elem = array_node_destroy(&a->elems[a->count - 1]);
    a->count--;

    return elem;
}

/* ************************************************************************************************/

void *array_pop_front(array_s *a)
{
    if (NULL == a || a->count < 1)
        return NULL;

    void *elem = array_node_destroy(&a->elems[0]);

    for (int i = 0; i < (int)a->count - 1; i++)
        a->elems[i] = a->elems[i + 1];

    a->elems[a->count - 1] = NULL;
    a->count--;

    return elem;
}

/* ************************************************************************************************/

void *array_pop_at(array_s *a, int pos)
{
    if (NULL == a || a->count < 1 || pos < 0 || pos > (int)a->count - 1)
        return NULL;

    void *elem = array_node_destroy(&a->elems[pos]);

    for (int i = pos; i < (int)a->count - 1; i++)
        a->elems[i] = a->elems[i + 1];

    a->elems[a->count - 1] = NULL;
    a->count--;

    return elem;
}

/* ************************************************************************************************/

void *array_replace(array_s *a, void *elem, int pos)
{
    if (NULL == a || pos < 0 || pos > (int)a->count - 1)
        return NULL;

    void *old_elem = a->elems[pos]->elem;
    a->elems[pos]->elem = elem;

    return old_elem;
}

/* ************************************************************************************************/

array_rc_e array_swap(array_s *a, int pos1, int pos2)
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (a->count < 1)
        return ARRAY_RC_EMPTY;

    if (pos1 < 0 || pos1 > (int)a->count - 1 || pos2 < 0 || pos2 > (int)a->count - 1 ||
        pos1 == pos2)
        return ARRAY_RC_INVALID_POS;

    void *tmp = a->elems[pos1]->elem;
    a->elems[pos1]->elem = a->elems[pos2]->elem;
    a->elems[pos2]->elem = tmp;

    return ARRAY_RC_OK;
}

/* ************************************************************************************************/

int array_find_next(array_s *a, void *elem, int start_pos, int (*elem_compare)(void *, void *))
{
    if (NULL == a || NULL == elem_compare || a->count < 1 || start_pos < 0 ||
        start_pos > (int)a->count - 1)
        return -1;

    int found = -1;

    for (int i = start_pos; i < (int)a->count; i++) {
        if (0 == elem_compare(elem, a->elems[i]->elem)) {
            found = i;
            break;
        }
    }

    return found;
}

/* ************************************************************************************************/

array_rc_e array_traverse(array_s *a, void (*elem_visit)(void *))
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (0 == a->count)
        return ARRAY_RC_EMPTY;

    if (NULL == elem_visit)
        return ARRAY_RC_ELEM_CB_NULL;

    for (int i = 0; i < (int)a->count; i++) {
        elem_visit(a->elems[i]->elem);
    }

    return ARRAY_RC_OK;
}

/* ************************************************************************************************/

array_rc_e array_clear(array_s *a, void (*elem_destroy)(void **))
{
    if (NULL == a)
        return ARRAY_RC_NULL;

    if (0 == a->count)
        return ARRAY_RC_EMPTY;

    array_rc_e rc = (NULL == elem_destroy ? ARRAY_RC_ELEM_CB_NULL : ARRAY_RC_OK);

    for (int i = 0; i < (int)a->count; i++) {
        void *elem = array_node_destroy(&a->elems[i]);

        if (NULL != elem_destroy)
            elem_destroy(&elem);
    }

    a->count = 0;

    return rc;
}

/* ************************************************************************************************/

array_rc_e array_destroy(array_s **a, void (*elem_destroy)(void **))
{
    if (NULL == a || NULL == *a)
        return ARRAY_RC_NULL;

    array_rc_e rc = array_clear(*a, elem_destroy);

    free((*a)->elems);
    free(*a);
    *a = NULL;

    return rc;
}
