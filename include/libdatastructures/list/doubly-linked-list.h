/**
 * \file   doubly-linked-list.h
 * \brief  Circular doubly linked list - struct. and type definitions and function declarations
 */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/list/doubly-linked-list-node.h"

/* ************************************************************************************************/

/** Doubly linked list structure */
struct doubly_linked_list {
    /** Pointer to the first node (the 'front' of the list) */
    d_l_list_node_s *front;
    /** No. of nodes stored in the list */
    size_t count;
};

/** Doubly linked list type */
typedef struct doubly_linked_list d_l_list_s;

/** Doubly linked list operations return codes */
enum doubly_linked_list_rc {
    /** No error */
    D_L_LIST_RC_OK = 0,
    /** List is null */
    D_L_LIST_RC_NULL = -1,
    /** List is empty (contains no elements) */
    D_L_LIST_RC_EMPTY = -2,
    /** The element to be inserted is null */
    D_L_LIST_RC_ELEM_NULL = -3,
    /** The callback function to operate on the element is null */
    D_L_LIST_RC_ELEM_CB_NULL = -4,
    /** The allocation of a new node has failed */
    D_L_LIST_RC_NODE_ALLOC_ERR = -5,
};

/** Doubly linked list operation return code type */
typedef enum doubly_linked_list_rc d_l_list_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize a circular doubly linked list.
 * \param  list  pointer to the list to be initialized
 */
void d_l_list_init(d_l_list_s *list);

/**
 * \brief   Create and initialize a new circular doubly linked list.
 * \return  a pointer to the allocated list
 */
d_l_list_s *d_l_list_new(void);

/**
 * \brief   Insert a non-null element to the 'front' (beginning) of a circ. doubly linked list.
 * \param   list  the list whose element is to be inserted onto
 * \param   elem  the element to be inserted onto the list
 * \return  the return code for the insert operation
 */
d_l_list_rc_e d_l_list_insert_front(d_l_list_s *list, void *elem);

/**
 * \brief   Insert a non-null element to the 'back' (end) of a circ. doubly linked list.
 * \param   list  the list whose element is to be inserted onto
 * \param   elem  the element to be inserted onto the list
 * \return  the return code for the insert operation
 */
d_l_list_rc_e d_l_list_insert_back(d_l_list_s *list, void *elem);

/**
 * \brief   Traverse all the list nodes in a forward direction, from the beginning to the end,
 *          applying the 'elem_visit' callback function to all its elements.
 * \param   list        the list to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the list
 * \return  the return code for the traversal operation
 */
d_l_list_rc_e d_l_list_traverse_forward(d_l_list_s *list, void (*elem_visit)(void *));

/**
 * \brief   Traverse all the list nodes in a backward direction, from the end to the beginning,
 *          applying the 'elem_visit' callback function to all its elements.
 * \param   list        the list to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the list
 * \return  the return code for the traversal operation
 */
d_l_list_rc_e d_l_list_traverse_backward(d_l_list_s *list, void (*elem_visit)(void *));

/**
 * \brief   Remove the element at the 'front' (beginning) of the circ. doubly linked list.
 * \param   list  the list whose element is to be removed
 * \return  the element removed from the list; it's the user's responsibility to deallocate it
 */
void *d_l_list_remove_front(d_l_list_s *list);

/**
 * \brief   Remove the element at the 'back' (end) of the circ. doubly linked list.
 * \param   list  the list whose element is to be removed
 * \return  the element removed from the list; it's the user's responsibility to deallocate it
 */
void *d_l_list_remove_back(d_l_list_s *list);

/**
 * \brief   Deallocate ('destroy') all the nodes in the list, including its elements (if an
 *          'elem_destroy' callback function is provided), making the list empty.
 * \param   list          the list whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the list elements
 * \return  the return code for the deallocation operation
 */
d_l_list_rc_e d_l_list_clear(d_l_list_s *list, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the list and the list itself.
 * \param   list          pointer to the list to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the list elements 
 * \return  the return code for the 'destroy' operation
 */
d_l_list_rc_e d_l_list_destroy(d_l_list_s **list, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DOUBLY_LINKED_LIST_H */
