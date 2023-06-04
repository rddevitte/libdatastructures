/**
 * \file   array.h
 * \brief  Array - struct. and type definitions and function declarations
 */
#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/array/array-node.h"

/* ************************************************************************************************/

/** Array structure */
struct array {
    /** Total length of the array (max. elements) */
    const size_t length;
    /** Pointer to the allocated pointer array */
    array_node_s **elems;
    /** No. of elements stored on the array */
    size_t count;
};

/** Array type */
typedef struct array array_s;

/** Array operations return codes */
enum array_rc {
    /** No error */
    ARRAY_RC_OK = 0,
    /** Array is null */
    ARRAY_RC_NULL = -1,
    /** Array is empty (contains no elements) */
    ARRAY_RC_EMPTY = -2,
    /** Array is full */
    ARRAY_RC_FULL = -3,
    /** Invalid position */
    ARRAY_RC_INVALID_POS = -4,
    /** The element to be inserted is null */
    ARRAY_RC_ELEM_NULL = -5,
    /** The callback function to operate on the element is null */
    ARRAY_RC_ELEM_CB_NULL = -6,
    /** The allocation of a new node has failed */
    ARRAY_RC_NODE_ALLOC_ERR = -7
};

/** Array operation return code type */
typedef enum array_rc array_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize an array.
 * \param  a       pointer to the array to be initialized
 * \param  length  the maximum length of the array
 */
void array_init(array_s *a, size_t length);

/**
 * \brief   Create and initialize a new array.
 * \param   length  the maximum length of the array
 * \return  a pointer to the allocated array
 */
array_s *array_new(size_t length);

/**
 * \brief   Push an element onto the back (end) of the array
 * \param   a     the array whose element is to be pushed onto
 * \param   elem  the element to be pushed
 * \return  the return code for the push operation
 */
array_rc_e array_push_back(array_s *a, void *elem);

/**
 * \brief   Push an element onto the front (beginning) of the array.
 * \param   a     the array whose element is to be pushed onto
 * \param   elem  the element to be pushed
 * \return  the return code for the push operation
 */
array_rc_e array_push_front(array_s *a, void *elem);

/**
 * \brief   Push an element onto an arbitrary position of the array.
 * \param   a     the array whose element is to be pushed onto
 * \param   elem  the element to be pushed
 * \param   pos   the position where the element is to be pushed
 * \return  the return code for the push operation
 */
array_rc_e array_push_at(array_s *a, void *elem, int pos);

/**
 * \brief   Get the number of elements stored in the array.
 * \param   a  the array whose number of elements is to be gotten
 * \return  the number of elements stored in the array
 */
size_t array_count(array_s *a);

/**
 * \brief   Get ('pick') the element from the back (end) of the array.
 * \param   a  the array whose element is to be picked from its back
 * \return  the element picked from the back of the array
 */
void *array_pick_back(array_s *a);

/**
 * \brief   Get ('pick') the element from the front (beginning) of the array.
 * \param   a  the array whose element is to be picked from its front
 * \return  the element picked from the front of the array
 */
void *array_pick_front(array_s *a);

/**
 * \brief   Get ('pick') the element from an arbitrary position of the array.
 * \param   a    the array whose element is to be picked from the given position
 * \param   pos  the position where the element is to be picked
 * \return  the element picked from the given position of the array
 */
void *array_pick_at(array_s *a, int pos);

/**
 * \brief   Remove ('pop') an element from the back (end) of the array.
 * \param   a  the array whose element is to be popped from its back
 * \return  the element popped from the back of the array
 */
void *array_pop_back(array_s *a);

/**
 * \brief   Remove ('pop') an element from the front (beginning) of the array.
 * \param   a  the array whose element is to be popped from its front
 * \return  the element popped from the front of the array
 */
void *array_pop_front(array_s *a);

/**
 * \brief   Remove ('pop') an element from an arbitrary position of the array.
 * \param   a  the array whose element is to be popped from the given position
 * \return  the element popped from the given position of the array
 */
void *array_pop_at(array_s *a, int pos);

/**
 * \brief   Replace the element on a given position of the array by another element.
 * \param   a     the array whose element is to be replaced
 * \param   elem  the new element that will replace the element on a given position
 * \param   pos   the position the old element is found
 * \return  the old element which was replaced by the new one
 */
void *array_replace(array_s *a, void *elem, int pos);

/**
 * \brief   Swap two elements from two given positions of the array.
 * \param   a     the array whose two elements will be swapped
 * \param   pos1  the position of the first element
 * \param   pos2  the position of the second element
 * \return  the return code for the swap operation
 */
array_rc_e array_swap(array_s *a, int pos1, int pos2);

/**
 * \brief   Find the first occurrence of an element starting at a position of the array.
 * \param   a             the array whose element is to be found
 * \param   elem          an 'example' element to be compared to every other in the array
 * \param   start_pos     the starting position of the array the search will take place
 * \param   elem_compare  pointer to a callback function used to compare the 'example' element
 *                        to the others in the array; it must return 0 if the provided element
 *                        is 'equal' to the element stored in the array, and non-zero otherwise
 * \return  the position where the element was found, -1 otherwise
 */
int array_find_next(array_s *a, void *elem, int start_pos, int (*elem_compare)(void *, void *));

/**
 * \brief   Traverse all the array elements from front to back, applying the 'elem_visit'
 *          callback function to all its elements.
 * \param   a           the array to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all elems. in the array
 * \return  the return code for the traversal operation
 */
array_rc_e array_traverse(array_s *a, void (*elem_visit)(void *));

/**
 * \brief   Deallocate ('destroy') all the nodes in the array, including its elements (if an
 *          'elem_destroy' callback function is provided), making the array empty.
 * \param   a             the array whose are to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback func. which deallocates all the array elements
 * \return  the return code for the 'destroy' operation
 */
array_rc_e array_clear(array_s *a, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the array and the array itself.
 * \param   a             pointer to the array to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback func. which deallocates all the array elements
 * \return  the return code for the 'destroy' operation
 */
array_rc_e array_destroy(array_s **a, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ARRAY_H */
