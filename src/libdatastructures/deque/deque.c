/**
 * \file   deque.c
 * \brief  Doubly-ended queue ("deque") data structure - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/doubly-linked-list.h"
#include "libdatastructures/deque/deque.h"

/* ************************************************************************************************/

/**
 * \brief   Convert a circ. doubly linked list return code to a deque one
 * \param   rc  the circular doubly linked list operation return code
 * \return  an equivalent deque operation return code
 */
static deque_rc_e d_l_list_rc_to_deque_rc(d_l_list_rc_e rc)
{
    deque_rc_e new_rc;

    switch (rc) {
        case D_L_LIST_RC_OK:
            new_rc = DEQUE_RC_OK;
            break;
        case D_L_LIST_RC_EMPTY:
            new_rc = DEQUE_RC_EMPTY;
            break;
        case D_L_LIST_RC_ELEM_NULL:
            new_rc = DEQUE_RC_ELEM_NULL;
            break;
        case D_L_LIST_RC_ELEM_CB_NULL:
            new_rc = DEQUE_RC_ELEM_CB_NULL;
            break;
        case D_L_LIST_RC_NODE_ALLOC_ERR:
            new_rc = DEQUE_RC_NODE_ALLOC_ERR;
            break;
        default:
            new_rc = DEQUE_RC_NULL;
    }

    return new_rc;
}

/* ************************************************************************************************/

void deque_init(deque_s *deque)
{
    d_l_list_init(deque);

    return;
}

/* ************************************************************************************************/

deque_s *deque_new(void)
{
    return d_l_list_new();
}

/* ************************************************************************************************/

deque_rc_e deque_push_front(deque_s *deque, void *elem)
{
    return d_l_list_rc_to_deque_rc(d_l_list_insert_front(deque, elem));
}

/* ************************************************************************************************/

deque_rc_e deque_push_back(deque_s *deque, void *elem)
{
    return d_l_list_rc_to_deque_rc(d_l_list_insert_back(deque, elem));
}

/* ************************************************************************************************/

size_t deque_count(deque_s *deque)
{
    if (NULL == deque)
        return 0;

    return deque->count;
}

/* ************************************************************************************************/

deque_rc_e deque_traverse(deque_s *deque, void (*elem_visit)(void *))
{
    return d_l_list_rc_to_deque_rc(d_l_list_traverse_forward(deque, elem_visit));
}

/* ************************************************************************************************/

void *deque_pick_front(deque_s *deque)
{
    if (NULL == deque || NULL == deque->front)
        return NULL;

    return deque->front->elem;
}

/* ************************************************************************************************/

void *deque_pick_back(deque_s *deque)
{
    if (NULL == deque || NULL == deque->front)
        return NULL;

    return deque->front->prev->elem;
}

/* ************************************************************************************************/

void *deque_pop_front(deque_s *deque)
{
    return d_l_list_remove_front(deque);
}

/* ************************************************************************************************/

void *deque_pop_back(deque_s *deque)
{
    return d_l_list_remove_back(deque);
}

/* ************************************************************************************************/

deque_rc_e deque_clear(deque_s *deque, void (*elem_destroy)(void **))
{
    return d_l_list_rc_to_deque_rc(d_l_list_clear(deque, elem_destroy));
}

/* ************************************************************************************************/

deque_rc_e deque_destroy(deque_s **deque, void (*elem_destroy)(void **))
{
    return d_l_list_rc_to_deque_rc(d_l_list_destroy(deque, elem_destroy));
}
