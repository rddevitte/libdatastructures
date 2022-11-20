/**
 * \file   stack-test.c
 * \brief  Stack data structure - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/stack/stack.h"
#include "number/number.h"

int main(void)
{
    stack_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null stack */
    stack_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null stack */
    stack_init(numbers);
    assert(NULL == numbers);

    /* It should fail when trying to push elements into a null stack */
    void *dummy = number_new(0);
    rc = stack_push(numbers, dummy);
    assert(STACK_RC_NULL == rc);

    /* It should return zero when getting the number of elements of a null stack */
    size_t count = stack_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse a null stack */
    rc = stack_traverse(numbers, number_print);
    assert(STACK_RC_NULL == rc);

    /* It should return null when trying to pick an element at the top of a null stack */
    tmp = stack_pick(numbers);
    assert(NULL == tmp);

    /* It should return null when trying to pop an element off a null stack */
    tmp = stack_pop(numbers);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null stack */
    rc = stack_clear(numbers, number_destroy);
    assert(STACK_RC_NULL == rc);

    /* It should fail when trying to destroy a null stack */
    rc = stack_destroy(NULL, number_destroy);
    assert(STACK_RC_NULL == rc);
    rc = stack_destroy(&numbers, number_destroy);
    assert(STACK_RC_NULL == rc);

    /* End of part 1. */
    number_destroy(&dummy);

    /* Part 2. Empty stack */
    /* The newly crated stack should not be null */
    numbers = stack_new();
    assert(NULL != numbers && 0 == stack_count(numbers));

    /* The newly created stack should be empty */
    count = stack_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse an empty stack */
    rc = stack_traverse(numbers, number_print);
    assert(STACK_RC_EMPTY == rc);

    /* It should return null when trying to pick an element at the top of an empty stack */
    tmp = stack_pick(numbers);
    assert(NULL == tmp && 0 == stack_count(numbers));

    /* It should return null when trying to pop an element off an empty stack */
    tmp = stack_pop(numbers);
    assert(NULL == tmp && 0 == stack_count(numbers));

    /* It must return 'empty stack' after destroying an empty stack */
    rc = stack_destroy(&numbers, number_destroy);
    assert(STACK_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3: non-empty stack */
    numbers = stack_new();
    assert(NULL != numbers && 0 == stack_count(numbers));

    /* It should fail when trying to push a null element onto the stack */
    rc = stack_push(numbers, NULL);
    assert(STACK_RC_ELEM_NULL == rc && 0 == stack_count(numbers));

    /* It should succeed at pushing three elements onto the stack */
    rc = stack_push(numbers, number_new(10));
    assert(STACK_RC_OK == rc && 1 == stack_count(numbers));
    rc = stack_push(numbers, number_new(20));
    assert(STACK_RC_OK == rc && 2 == stack_count(numbers));
    rc = stack_push(numbers, number_new(30));
    assert(STACK_RC_OK == rc && 3 == stack_count(numbers));

    /* It should fail when trying to traverse the stack without a callback function provided */
    rc = stack_traverse(numbers, NULL);
    assert(STACK_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing a non-empty stack */
    rc = stack_traverse(numbers, number_print);
    assert(STACK_RC_OK == rc);

    /* It should succeed when picking the top element of the stack */
    tmp = stack_pick(numbers);
    assert(NULL != tmp && 3 == stack_count(numbers) && 30 == *(int *)tmp);

    /* It should succeed when popping the elements off the stack */
    tmp = stack_pop(numbers);
    assert(NULL != tmp && 2 == stack_count(numbers) && 30 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = stack_pop(numbers);
    assert(NULL != tmp && 1 == stack_count(numbers) && 20 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = stack_pop(numbers);
    assert(NULL != tmp && 0 == stack_count(numbers) && 10 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = stack_pop(numbers);
    assert(NULL == tmp && 0 == stack_count(numbers));

    /* Insert three elements again */
    rc = stack_push(numbers, number_new(40));
    assert(STACK_RC_OK == rc && 1 == stack_count(numbers));
    rc = stack_push(numbers, number_new(50));
    assert(STACK_RC_OK == rc && 2 == stack_count(numbers));
    rc = stack_push(numbers, number_new(60));
    assert(STACK_RC_OK == rc && 3 == stack_count(numbers));

    /* It should succeed at removing all elements from the stack (stack must be empty) */
    rc = stack_clear(numbers, number_destroy);
    assert(STACK_RC_OK == rc && 0 == stack_count(numbers));

    /* It should return 'list empty' after destroying the list */
    rc = stack_destroy(&numbers, number_destroy);
    assert(STACK_RC_EMPTY == rc && NULL == numbers && 0 == stack_count(numbers));

    return 0;
}
