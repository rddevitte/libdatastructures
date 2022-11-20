/**
 * \file   doubly-linked-list.c
 * \brief  Circ. doubly linked list - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/doubly-linked-list.h"
#include "libdatastructures/list/doubly-linked-list-node.h"

/* ************************************************************************************************/

void d_l_list_init(d_l_list_s *list)
{
    if (NULL != list) {
        list->front = NULL;
        list->count = 0;
    }

    return;
}

/* ************************************************************************************************/

d_l_list_s *d_l_list_new(void)
{
    d_l_list_s *new_list = (d_l_list_s *)malloc(sizeof(*new_list));

    d_l_list_init(new_list);

    return new_list;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_insert_front(d_l_list_s *list, void *elem)
{
    if (NULL == list)
        return D_L_LIST_RC_NULL;

    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return D_L_LIST_RC_ELEM_NULL;

    d_l_list_node_s *new_node = d_l_list_node_new(elem);

    if (NULL == new_node)
        return D_L_LIST_RC_NODE_ALLOC_ERR;

    if (NULL != list->front) {
        new_node->prev = list->front->prev;
        new_node->next = list->front;
        list->front->prev->next = new_node;
        list->front->prev = new_node;
    }

    list->front = new_node;
    list->count++;

    return D_L_LIST_RC_OK;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_insert_back(d_l_list_s *list, void *elem)
{
    if (NULL == list)
        return D_L_LIST_RC_NULL;

    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return D_L_LIST_RC_ELEM_NULL;

    d_l_list_node_s *new_node = d_l_list_node_new(elem);

    if (NULL == new_node)
        return D_L_LIST_RC_NODE_ALLOC_ERR;

    if (NULL != list->front) {
        new_node->prev = list->front->prev;
        new_node->next = list->front;
        list->front->prev->next = new_node;
        list->front->prev = new_node;
    } else {
        list->front = new_node;
    }

    list->count++;

    return D_L_LIST_RC_OK;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_traverse_forward(d_l_list_s *list, void (*elem_visit)(void *))
{
    if (NULL == list)
        return D_L_LIST_RC_NULL;

    if (NULL == list->front && 0 == list->count)
        return D_L_LIST_RC_EMPTY;

    if (NULL == elem_visit)
        return D_L_LIST_RC_ELEM_CB_NULL;

    d_l_list_node_s *tmp = list->front;

    do {
        elem_visit(tmp->elem);
        tmp = tmp->next;
    } while (tmp != list->front);

    return D_L_LIST_RC_OK;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_traverse_backward(d_l_list_s *list, void (*elem_visit)(void *))
{
    if (NULL == list)
        return D_L_LIST_RC_NULL;

    if (NULL == list->front && 0 == list->count)
        return D_L_LIST_RC_EMPTY;

    if (NULL == elem_visit)
        return D_L_LIST_RC_ELEM_CB_NULL;

    d_l_list_node_s *tmp = list->front->prev;

    do {
        elem_visit(tmp->elem);
        tmp = tmp->prev;
    } while (tmp != list->front->prev);

    return D_L_LIST_RC_OK;
}

/* ************************************************************************************************/

void *d_l_list_remove_front(d_l_list_s *list)
{
    if (NULL == list || NULL == list->front)
        return NULL;

    list->front = list->front->next;

    return d_l_list_remove_back(list);
}

/* ************************************************************************************************/

void *d_l_list_remove_back(d_l_list_s *list)
{
    if (NULL == list || NULL == list->front)
        return NULL;

    void *elem;

    if (list->front == list->front->next && list->front == list->front->prev) {
        elem = d_l_list_node_destroy(&list->front);
    } else {
        d_l_list_node_s *tmp = list->front->prev;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        elem = d_l_list_node_destroy(&tmp);
    }

    list->count--;

    return elem;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_clear(d_l_list_s *list, void (*elem_destroy)(void **))
{
    if (NULL == list)
        return D_L_LIST_RC_NULL;

    if (NULL == list->front && 0 == list->count)
        return D_L_LIST_RC_EMPTY;

    d_l_list_rc_e rc = (NULL == elem_destroy ? D_L_LIST_RC_ELEM_CB_NULL : D_L_LIST_RC_OK);

    d_l_list_node_s *tmp;
    void *elem;

    /* Firstly, make the circular list a non-circular one */
    list->front->prev->next = NULL;
    list->front->prev = NULL;

    while (NULL != list->front) {
        tmp = list->front->next;
        elem = d_l_list_node_destroy(&list->front);

        if (NULL != elem_destroy)
            elem_destroy(&elem);

        list->front = tmp;
    }

    list->count = 0;

    return rc;
}

/* ************************************************************************************************/

d_l_list_rc_e d_l_list_destroy(d_l_list_s **list, void (*elem_destroy)(void **))
{
    if (NULL == list || NULL == *list)
        return D_L_LIST_RC_NULL;

    d_l_list_rc_e rc = d_l_list_clear(*list, elem_destroy);

    free(*list);
    *list = NULL;

    return rc;
}
