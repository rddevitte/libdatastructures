/**
 * \file   array-node.c
 * \brief  Array node - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/array/array-node.h"

/* ************************************************************************************************/

array_node_s *array_node_new(void *elem)
{
    array_node_s *node = (array_node_s *)malloc(sizeof(array_node_s));

    if (NULL != node) {
        node->elem = elem;
    }

    return node;
}

/* ************************************************************************************************/

void *array_node_destroy(array_node_s **node)
{
    if (NULL == node || NULL == *node)
        return NULL;

    void *elem = (*node)->elem;

    free(*node);
    *node = NULL;

    return elem;
}
