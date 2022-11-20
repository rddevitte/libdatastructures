/**
 * \file   doubly-linked-list-node.c
 * \brief  Circ. doubly linked list node - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/doubly-linked-list.h"

/* ************************************************************************************************/

d_l_list_node_s *d_l_list_node_new(void *elem)
{
    d_l_list_node_s *new_node = (d_l_list_node_s *)malloc(sizeof(*new_node));

    if (NULL != new_node) {
        new_node->elem = elem;
        /* Since it's a *circular* doubly linked list node,
           the 'prev' and 'next' pointers should point to itself */
        new_node->prev = new_node;
        new_node->next = new_node;
    }

    return new_node;
}

/* ************************************************************************************************/

void *d_l_list_node_destroy(d_l_list_node_s **node)
{
    if (NULL == node || NULL == *node)
        return NULL;

    void *elem = (*node)->elem;

    free(*node);
    *node = NULL;

    return elem;
}
