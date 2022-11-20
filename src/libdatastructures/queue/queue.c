/**
 * \file   queue.c
 * \brief  Queue data structure - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/singly-linked-list.h"
#include "libdatastructures/queue/queue.h"

/* ************************************************************************************************/

/**
 * \brief   Convert a circ. singly linked list return code to a queue one
 * \param   rc  the circular singly linked list operation return code
 * \return  an equivalent queue operation return code
 */
static queue_rc_e s_l_list_rc_to_queue_rc(s_l_list_rc_e rc)
{
    queue_rc_e new_rc;

    switch (rc) {
        case S_L_LIST_RC_OK:
            new_rc = QUEUE_RC_OK;
            break;
        case S_L_LIST_RC_EMPTY:
            new_rc = QUEUE_RC_EMPTY;
            break;
        case S_L_LIST_RC_ELEM_NULL:
            new_rc = QUEUE_RC_ELEM_NULL;
            break;
        case S_L_LIST_RC_ELEM_CB_NULL:
            new_rc = QUEUE_RC_ELEM_CB_NULL;
            break;
        case S_L_LIST_RC_NODE_ALLOC_ERR:
            new_rc = QUEUE_RC_NODE_ALLOC_ERR;
            break;
        default:
            new_rc = QUEUE_RC_NULL;
    }

    return new_rc;
}

/* ************************************************************************************************/

void queue_init(queue_s *queue)
{
    s_l_list_init(queue);

    return;
}

/* ************************************************************************************************/

queue_s *queue_new(void)
{
    return s_l_list_new();
}

/* ************************************************************************************************/

queue_rc_e queue_enqueue(queue_s *queue, void *elem)
{
    return s_l_list_rc_to_queue_rc(s_l_list_insert_back(queue, elem));
}

/* ************************************************************************************************/

size_t queue_count(queue_s *queue)
{
    if (NULL == queue)
        return 0;

    return queue->count;
}

/* ************************************************************************************************/

queue_rc_e queue_traverse(queue_s *queue, void (*elem_visit)(void *))
{
    return s_l_list_rc_to_queue_rc(s_l_list_traverse(queue, elem_visit));
}

/* ************************************************************************************************/

void *queue_pick(queue_s *queue)
{
    if (NULL == queue || NULL == queue->back)
        return NULL;

    return queue->back->next->elem;
}

/* ************************************************************************************************/

void *queue_dequeue(queue_s *queue)
{
    return s_l_list_remove_front(queue);
}

/* ************************************************************************************************/

queue_rc_e queue_clear(queue_s *queue, void (*elem_destroy)(void **))
{
    return s_l_list_rc_to_queue_rc(s_l_list_clear(queue, elem_destroy));
}

/* ************************************************************************************************/

queue_rc_e queue_destroy(queue_s **queue, void (*elem_destroy)(void **))
{
    return s_l_list_rc_to_queue_rc(s_l_list_destroy(queue, elem_destroy));
}
