/**
 * \file   singly-linked-list.c
 * \brief  Circ. singly linked list - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/singly-linked-list.h"
#include "libdatastructures/list/singly-linked-list-node.h"

/* ************************************************************************************************/

void s_l_list_init(s_l_list_s *list)
{
    if (NULL != list) {
        list->back = NULL;
        list->count = 0;
    }

    return;
}

/* ************************************************************************************************/

s_l_list_s *s_l_list_new(void)
{
    s_l_list_s *new_list = (s_l_list_s *)malloc(sizeof(*new_list));

    s_l_list_init(new_list);

    return new_list;
}

/* ************************************************************************************************/

s_l_list_rc_e s_l_list_insert_front(s_l_list_s *list, void *elem)
{
    if (NULL == list)
        return S_L_LIST_RC_NULL;

    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return S_L_LIST_RC_ELEM_NULL;

    s_l_list_node_s *new_node = s_l_list_node_new(elem);

    if (NULL == new_node)
        return S_L_LIST_RC_NODE_ALLOC_ERR;

    if (NULL != list->back) {
        new_node->next = list->back->next;
        list->back->next = new_node;
    } else {
        list->back = new_node;
    }

    list->count++;

    return S_L_LIST_RC_OK;
}

/* ************************************************************************************************/

s_l_list_rc_e s_l_list_insert_back(s_l_list_s *list, void *elem)
{
    if (NULL == list)
        return S_L_LIST_RC_NULL;

    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return S_L_LIST_RC_ELEM_NULL;

    s_l_list_node_s *new_node = s_l_list_node_new(elem);

    if (NULL == new_node)
        return S_L_LIST_RC_NODE_ALLOC_ERR;

    if (NULL != list->back) {
        new_node->next = list->back->next;
        list->back->next = new_node;
    }

    list->back = new_node;
    list->count++;

    return S_L_LIST_RC_OK;
}

/* ************************************************************************************************/

s_l_list_rc_e s_l_list_traverse(s_l_list_s *list, void (*elem_visit)(void *))
{
    if (NULL == list)
        return S_L_LIST_RC_NULL;

    if (NULL == list->back && 0 == list->count)
        return S_L_LIST_RC_EMPTY;

    if (NULL == elem_visit)
        return S_L_LIST_RC_ELEM_CB_NULL;

    s_l_list_node_s *tmp = list->back->next;

    do {
        elem_visit(tmp->elem);
        tmp = tmp->next;
    } while (tmp != list->back->next);

    return S_L_LIST_RC_OK;
}

/* ************************************************************************************************/

void *s_l_list_remove_front(s_l_list_s *list)
{
    if (NULL == list || NULL == list->back)
        return NULL;

    void *elem;

    if (list->back == list->back->next) {
        elem = s_l_list_node_destroy(&list->back);
    } else {
        s_l_list_node_s *tmp = list->back->next->next;
        elem = s_l_list_node_destroy(&list->back->next);
        list->back->next = tmp;
    }

    list->count--;

    return elem;
}

/* ************************************************************************************************/

s_l_list_rc_e s_l_list_clear(s_l_list_s *list, void (*elem_destroy)(void **))
{
    if (NULL == list)
        return S_L_LIST_RC_NULL;

    if (NULL == list->back && 0 == list->count)
        return S_L_LIST_RC_EMPTY;

    s_l_list_rc_e rc = (NULL == elem_destroy ? S_L_LIST_RC_ELEM_CB_NULL : S_L_LIST_RC_OK);

    s_l_list_node_s *tmp;
    void *elem;

    /* Firstly, make the circular list a non-circular one */
    s_l_list_node_s *front = list->back->next;
    list->back->next = NULL;

    while (NULL != front) {
        tmp = front->next;
        elem = s_l_list_node_destroy(&front);

        if (NULL != elem_destroy)
            elem_destroy(&elem);

        front = tmp;
    }

    list->back = NULL;
    list->count = 0;

    return rc;
}

/* ************************************************************************************************/

s_l_list_rc_e s_l_list_destroy(s_l_list_s **list, void (*elem_destroy)(void **))
{
    if (NULL == list || NULL == *list)
        return S_L_LIST_RC_NULL;

    s_l_list_rc_e rc = s_l_list_clear(*list, elem_destroy);

    free(*list);
    *list = NULL;

    return rc;
}
