/**
 * \file   stack.c
 * \brief  Stack data structure - functions definitions
 */
#include <stdlib.h>
#include "libdatastructures/list/singly-linked-list.h"
#include "libdatastructures/stack/stack.h"

/* ************************************************************************************************/

/**
 * \brief   Convert a circ. singly linked list return code to a stack one
 * \param   rc  the circular singly linked list operation return code
 * \return  an equivalent stack operation return code
 */
static stack_rc_e s_l_list_rc_to_stack_rc(s_l_list_rc_e rc)
{
    stack_rc_e new_rc;

    switch (rc) {
        case S_L_LIST_RC_OK:
            new_rc = STACK_RC_OK;
            break;
        case S_L_LIST_RC_EMPTY:
            new_rc = STACK_RC_EMPTY;
            break;
        case S_L_LIST_RC_ELEM_NULL:
            new_rc = STACK_RC_ELEM_NULL;
            break;
        case S_L_LIST_RC_ELEM_CB_NULL:
            new_rc = STACK_RC_ELEM_CB_NULL;
            break;
        case S_L_LIST_RC_NODE_ALLOC_ERR:
            new_rc = STACK_RC_NODE_ALLOC_ERR;
            break;
        default:
            new_rc = STACK_RC_NULL;
    }

    return new_rc;
}

/* ************************************************************************************************/

void stack_init(stack_s *stack)
{
    s_l_list_init(stack);

    return;
}

/* ************************************************************************************************/

stack_s *stack_new(void)
{
    return s_l_list_new();
}

/* ************************************************************************************************/

stack_rc_e stack_push(stack_s *stack, void *elem)
{
    return s_l_list_rc_to_stack_rc(s_l_list_insert_front(stack, elem));
}

/* ************************************************************************************************/

size_t stack_count(stack_s *stack)
{
    if (NULL == stack)
        return 0;

    return stack->count;
}

/* ************************************************************************************************/

stack_rc_e stack_traverse(stack_s *stack, void (*elem_visit)(void *))
{
    return s_l_list_rc_to_stack_rc(s_l_list_traverse(stack, elem_visit));
}

/* ************************************************************************************************/

void *stack_pick(stack_s *stack)
{
    if (NULL == stack || NULL == stack->back)
        return NULL;

    return stack->back->next->elem;
}

/* ************************************************************************************************/

void *stack_pop(stack_s *stack)
{
    return s_l_list_remove_front(stack);
}

/* ************************************************************************************************/

stack_rc_e stack_clear(stack_s *stack, void (*elem_destroy)(void **))
{
    return s_l_list_rc_to_stack_rc(s_l_list_clear(stack, elem_destroy));
}

/* ************************************************************************************************/

stack_rc_e stack_destroy(stack_s **stack, void (*elem_destroy)(void **))
{
    return s_l_list_rc_to_stack_rc(s_l_list_destroy(stack, elem_destroy));
}
