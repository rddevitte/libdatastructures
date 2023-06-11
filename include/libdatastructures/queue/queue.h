/**
 * \file   queue.h
 * \brief  Queue data structure - struct. and type definitions and functions declarations
 */
#ifndef LIBDATASTRUCTURES_QUEUE_H
#define LIBDATASTRUCTURES_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/list/singly-linked-list.h"

/* ************************************************************************************************/

/** Queue data structure type, which is actually a "wrapper" of a circ. singly linked list */
typedef s_l_list_s queue_s;

/** Queue operations return codes */
enum queue_rc {
    /** No error */
    QUEUE_RC_OK = S_L_LIST_RC_OK,
    /** Queue is null */
    QUEUE_RC_NULL = S_L_LIST_RC_NULL,
    /** Queue is empty (contains no elements) */
    QUEUE_RC_EMPTY = S_L_LIST_RC_EMPTY,
    /** The element to be enqueued is null */
    QUEUE_RC_ELEM_NULL = S_L_LIST_RC_ELEM_NULL,
    /** The callback function to operate on the element is null */
    QUEUE_RC_ELEM_CB_NULL = S_L_LIST_RC_ELEM_CB_NULL,
    /** The allocation of a new node has failed */
    QUEUE_RC_NODE_ALLOC_ERR = S_L_LIST_RC_NODE_ALLOC_ERR
};

/** Queue operation return code type */
typedef enum queue_rc queue_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize a queue.
 * \param  queue  pointer to the queue to be initialized
 */
void queue_init(queue_s *queue);

/**
 * \brief   Create and initialize a queue.
 * \return  a pointer to the allocated queue
 */
queue_s *queue_new(void);

/**
 * \brief   Enqueue an element onto the queue.
 * \param   queue  the queue whose element is to be enqueued
 * \param   elem   the element to be enqueued
 * \return  the return code for the enqueue operation
 */
queue_rc_e queue_enqueue(queue_s *queue, void *elem);

/**
 * \brief   Get the number of enqueued elements.
 * \param   queue  the queue whose number of elements is to be gotten
 * \return  the number of elements enqueued onto the queue
 */
size_t queue_count(queue_s *queue);

/**
 * \brief   Traverse all the queue elements from front to back, applying the 'elem_visit'
 *          callback function to all its elements.
 * \param   queue       the queue to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the queue
 * \return  the return code for the traversal operation
 */
queue_rc_e queue_traverse(queue_s *queue, void (*elem_visit)(void *));

/**
 * \brief   Get ('pick') the element from the front of the queue without actually removing it.
 * \param   queue  the queue whose element is to be picked from its front
 * \return  the element picked from the front of the queue
 */
void *queue_pick(queue_s *queue);

/**
 * \brief   Dequeue an element from the queue.
 * \param   queue  the queue whose element is to be dequeued from
 * \return  the element dequeued from the queue
 */
void *queue_dequeue(queue_s *queue);

/**
 * \brief   Deallocate ('destroy') all the nodes in the queue, including its elements (if an
 *          'elem_destroy' callback function is provided), making the queue empty.
 * \param   queue         the queue whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to the callback func. which deallocates all the queue elems.
 * \return  the return code for the deallocation operation
 */
queue_rc_e queue_clear(queue_s *queue, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the queue and the queue itself.
 * \param   queue         pointer to the queue to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the queue elements
 * \return  the return code for the 'destroy' operation
 */
queue_rc_e queue_destroy(queue_s **queue, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_QUEUE_H */
