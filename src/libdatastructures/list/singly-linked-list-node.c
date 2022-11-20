/**
 * \file   singly-linked-list-node.c
 * \brief  Circ. singly linked list node - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/singly-linked-list-node.h"

/* ************************************************************************************************/

s_l_list_node_s *s_l_list_node_new(void *elem)
{
    s_l_list_node_s *new_node = (s_l_list_node_s *)malloc(sizeof(*new_node));

    if (NULL != new_node) {
        new_node->elem = elem;
        /* Since it's a *circular* singly linked list node,
           the 'next' pointer should point to itself */
        new_node->next = new_node;
    }

    return new_node;
}

/* ************************************************************************************************/

void *s_l_list_node_destroy(s_l_list_node_s **node)
{
    if (NULL == node || NULL == *node)
        return NULL;

    void *elem = (*node)->elem;

    free(*node);
    *node = NULL;

    return elem;
}
