/**
 * \file   deque.h
 * \brief  Doubly-ended queue ("deque") data structure - struct. and type defs. and funcs. decls.
 */
#ifndef LIBDATASTRUCTURES_DEQUE_H
#define LIBDATASTRUCTURES_DEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/list/doubly-linked-list.h"

/* ************************************************************************************************/

/** Deque data structure type, which is actually a "wrapper" of a circ. doubly linked list */
typedef d_l_list_s deque_s;

/** Deque operations return codes */
enum deque_rc {
    /** No error */
    DEQUE_RC_OK = D_L_LIST_RC_OK,
    /** Deque is null */
    DEQUE_RC_NULL = D_L_LIST_RC_NULL,
    /** Deque is empty (contains no elements) */
    DEQUE_RC_EMPTY = D_L_LIST_RC_EMPTY,
    /** The element to be pushed is null */
    DEQUE_RC_ELEM_NULL = D_L_LIST_RC_ELEM_NULL,
    /** The callback function to operate on the element is null */
    DEQUE_RC_ELEM_CB_NULL = D_L_LIST_RC_ELEM_CB_NULL,
    /** The allocation of a new node has failed */
    DEQUE_RC_NODE_ALLOC_ERR = D_L_LIST_RC_NODE_ALLOC_ERR
};

/** Deque operation return code type */
typedef enum deque_rc deque_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize a deque.
 * \param  deque  pointer to the deque to be initialized
 */
void deque_init(deque_s *deque);

/**
 * \brief   Create and initialize a deque.
 * \return  a pointer to the allocated deque
 */
deque_s *deque_new(void);

/**
 * \brief   Push and element onto the front (beginning) of the deque.
 * \param   deque  the deque whose element is to be pushed
 * \param   elem   the element to be pushed
 * \return  the return code for the push operation
 */
deque_rc_e deque_push_front(deque_s *deque, void *elem);

/**
 * \brief   Push and element onto the back (end) of the deque.
 * \param   deque  the deque whose element is to be pushed
 * \param   elem   the element to be pushed
 * \return  the return code for the push operation
 */
deque_rc_e deque_push_back(deque_s *deque, void *elem);

/**
 * \brief   Get the number of enqueued elements.
 * \param   deque  the deque whose number of elements is to be gotten
 * \return  the number of elements enqueued onto the deque
 */
size_t deque_count(deque_s *deque);

/**
 * \brief   Traverse all the deque elements from front to back, applying the 'elem_visit'
 *          callback function to all its elements.
 * \param   deque       the deque to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the deque
 * \return  the return code for the traversal operation
 */
deque_rc_e deque_traverse(deque_s *deque, void (*elem_visit)(void *));

/**
 * \brief   Get ('pick') the element from the front of the deque without actually removing it.
 * \param   deque  the deque whose element is to be picked from its front
 * \return  the element picked from the front of the deque
 */
void *deque_pick_front(deque_s *deque);

/**
 * \brief   Get ('pick') the element from the back of the deque without actually removing it.
 * \param   deque  the deque whose element is to be picked from its back
 * \return  the element picked from the back of the deque
 */
void *deque_pick_back(deque_s *deque);

/**
 * \brief   Remove ('pop') an element from the front of the deque.
 * \param   deque  the deque whose element is to be removed from its front
 * \return  the element removed from the front of the deque
 */
void *deque_pop_front(deque_s *deque);

/**
 * \brief   Remove ('pop') an element from the back of the deque.
 * \param   deque  the deque whose element is to be removed from its back
 * \return  the element removed from the back of the deque
 */
void *deque_pop_back(deque_s *deque);

/**
 * \brief   Deallocate ('destroy') all the nodes in the deque, including its elements (if an
 *          'elem_destroy' callback function is provided), making the deque empty.
 * \param   deque         the deque whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to the callback func. which deallocates all the deque elems.
 * \return  the return code for the deallocation operation
 */
deque_rc_e deque_clear(deque_s *deque, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the deque and the deque itself.
 * \param   deque         pointer to the deque to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the deque elements
 * \return  the return code for the 'destroy' operation
 */
deque_rc_e deque_destroy(deque_s **deque, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_DEQUE_H */
