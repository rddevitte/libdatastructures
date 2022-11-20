/**
 * \file   stack.h
 * \brief  Stack data structure - struct. and type definitions and functions declarations
 */
#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "libdatastructures/list/singly-linked-list.h"

/* ************************************************************************************************/

/** Stack data structure type, which is actually a "wrapper" of a circ. singly linked list */
typedef s_l_list_s stack_s;

/** Stack operations return codes */
enum stack_rc {
    /** No error */
    STACK_RC_OK = S_L_LIST_RC_OK,
    /** Stack is null */
    STACK_RC_NULL = S_L_LIST_RC_NULL,
    /** Stack is empty (contains no elements) */
    STACK_RC_EMPTY = S_L_LIST_RC_EMPTY,
    /** The element to be pushed is null */
    STACK_RC_ELEM_NULL = S_L_LIST_RC_ELEM_NULL,
    /** The callback function to operate on the element is null */
    STACK_RC_ELEM_CB_NULL = S_L_LIST_RC_ELEM_CB_NULL,
    /** The allocation of a new node has failed */
    STACK_RC_NODE_ALLOC_ERR = S_L_LIST_RC_NODE_ALLOC_ERR
};

/** Stack operation return code type */
typedef enum stack_rc stack_rc_e;

/* ************************************************************************************************/

/**
 * \brief  Initialize a stack.
 * \param  stack  pointer to the stack to be initialized
 */
void stack_init(stack_s *stack);

/**
 * \brief   Create and initialize a stack.
 * \return  a pointer to the allocated stack
 */
stack_s *stack_new(void);

/**
 * \brief   Push an element onto the stack.
 * \param   stack  the stack whose element is to be pushed onto
 * \param   elem   the element to be pushed
 * \return  the return code for the push operation
 */
stack_rc_e stack_push(stack_s *stack, void *elem);

/**
 * \brief   Get the number of elements pushed onto the stack.
 * \param   stack  the stack whose number of elements is to be gotten
 * \return  the number of elements pushed onto the stack
 */
size_t stack_count(stack_s *stack);

/**
 * \brief   Traverse all the stack elements from top to bottom, applying the 'elem_visit'
 *          callback function to all its elements.
 * \param   stack       the stack to be traversed by
 * \param   elem_visit  pointer to a callback function which 'visits' all the elems. in the stack
 * \return  the return code for the traversal operation
 */
stack_rc_e stack_traverse(stack_s *stack, void (*elem_visit)(void *));

/**
 * \brief   Get ('pick') the element from the top of the stack without actually removing it.
 * \param   stack  the stack whose element is to be picked from its top
 * \return  the element picked from the top of the stack
 */
void *stack_pick(stack_s *stack);

/**
 * \brief   Remove ('pop') an element off the stack.
 * \param   stack  the stack whose element is to be popped from
 * \return  the element popped off the stack
 */
void *stack_pop(stack_s *stack);

/**
 * \brief   Deallocate ('destroy') all the nodes in the stack, including its elements (if an
 *          'elem_destroy' callback function is provided), making the stack empty.
 * \param   stack         the stack whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to the callback func. which deallocates all the stack elems.
 * \return  the return code for the deallocation operation
 */
stack_rc_e stack_clear(stack_s *stack, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the stack and the stack itself.
 * \param   stack         pointer to the stack to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the stack elements
 * \return  the return code for the 'destroy' operation
 */
stack_rc_e stack_destroy(stack_s **stack, void (*elem_destroy)(void **));

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* STACK_H */
