/**
 * \file   singly-linked-list.h
 * \brief  Circular singly linked list - struct. and type definitions and function declarations
 */
#ifndef LIBDATASTRUCTURES_SINGLY_LINKED_LIST_H
#define LIBDATASTRUCTURES_SINGLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/list/singly-linked-list-node.h"

/* ************************************************************************************************/

/** Singly linked list structure */
struct singly_linked_list {
    /** Pointer to the last node (the 'back' of the list) */
    s_l_list_node_s *back;
    /** No. of nodes stored in the list */
    size_t count;
};

/** Singly linked list type */
typedef struct singly_linked_list s_l_list_s;

/** Singly linked list operations return codes */
enum singly_linked_list_rc {
    /** No error */
    S_L_LIST_RC_OK = 0,
    /** List is null */
    S_L_LIST_RC_NULL = -1,
    /** List is empty (contains no elements) */
    S_L_LIST_RC_EMPTY = -2,
    /** The element to be inserted is null */
    S_L_LIST_RC_ELEM_NULL = -3,
    /** The callback function to operate on the element is null */
    S_L_LIST_RC_ELEM_CB_NULL = -4,
    /** The allocation of a new node has failed */
    S_L_LIST_RC_NODE_ALLOC_ERR = -5,
};

/** Singly linked list operation return code type */
typedef enum singly_linked_list_rc s_l_list_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize a circular singly linked list.
 * \param  list  pointer to the list to be initialized
 */
void s_l_list_init(s_l_list_s *list);

/**
 * \brief   Create and initialize a new circular singly linked list.
 * \return  a pointer to the allocated list
 */
s_l_list_s *s_l_list_new(void);

/**
 * \brief   Insert a non-null element to the 'front' (beginning) of a circ. singly linked list.
 * \param   list  the list whose element is to be inserted onto
 * \param   elem  the element to be inserted onto the list
 * \return  the return code for the insert operation
 */
s_l_list_rc_e s_l_list_insert_front(s_l_list_s *list, void *elem);

/**
 * \brief   Insert a non-null element to the 'back' (end) of a circ. singly linked list.
 * \param   list  the list whose element is to be inserted onto
 * \param   elem  the element to be inserted onto the list
 * \return  the return code for the insert operation
 */
s_l_list_rc_e s_l_list_insert_back(s_l_list_s *list, void *elem);

/**
 * \brief   Traverse all the list nodes from the beginning to the end, applying the 'elem_visit'
 *          callback function to all its elements.
 * \param   list        the list to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the list
 * \return  the return code for the traversal operation
 */
s_l_list_rc_e s_l_list_traverse(s_l_list_s *list, void (*elem_visit)(void *));

/**
 * \brief   Remove the element at the 'front' (beginning) of the circ. singly linked list.
 * \param   list  the list whose element is to be removed
 * \return  the element removed from the list; it's the user's responsibility to deallocate it
 */
void *s_l_list_remove_front(s_l_list_s *list);

/**
 * \brief   Deallocate ('destroy') all the nodes in the list, including its elements (if an
 *          'elem_destroy' callback function is provided), making the list empty.
 * \param   list          the list whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the list elements
 * \return  the return code for the deallocation operation
 */
s_l_list_rc_e s_l_list_clear(s_l_list_s *list, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the list and the list itself.
 * \param   list          pointer to the list to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the list elements 
 * \return  the return code for the 'destroy' operation
 */
s_l_list_rc_e s_l_list_destroy(s_l_list_s **list, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_SINGLY_LINKED_LIST_H */
