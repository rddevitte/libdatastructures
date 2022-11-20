/**
 * \file   deque-test.c
 * \brief  Doubly-ended queue ("deque") data structure - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/deque/deque.h"
#include "number/number.h"

int main(void)
{
    deque_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null deque */
    deque_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null deque */
    deque_init(numbers);
    assert(NULL == numbers);

    /* It should fail when trying to push elements onto a null deque */
    void *dummy = number_new(0);
    rc = deque_push_front(numbers, dummy);
    assert(DEQUE_RC_NULL == rc);
    rc = deque_push_back(numbers, dummy);
    assert(DEQUE_RC_NULL == rc);

    /* It should return zero when getting the number of elements of a null deque */
    size_t count = deque_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse a null deque */
    rc = deque_traverse(numbers, number_print);
    assert(DEQUE_RC_NULL == rc);

    /* It should return null when trying to pick an element at the front of a null deque */
    tmp = deque_pick_front(numbers);
    assert(NULL == tmp);

    /* It should return null when trying to pick an element at the back of a null deque */
    tmp = deque_pick_back(numbers);
    assert(NULL == tmp);

    /* It should return null when trying to pop an element off the front of a null deque */
    tmp = deque_pop_front(numbers);
    assert(NULL == tmp);

    /* It should return null when trying to pop an element off the back of a null deque */
    tmp = deque_pop_back(numbers);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null deque */
    rc = deque_clear(numbers, number_destroy);
    assert(DEQUE_RC_NULL == rc);

    /* It should fail when trying to destroy a null deque */
    rc = deque_destroy(NULL, number_destroy);
    assert(DEQUE_RC_NULL == rc);
    rc = deque_destroy(&numbers, number_destroy);
    assert(DEQUE_RC_NULL == rc);

    /* End of part 1. */
    number_destroy(&dummy);

    /* Part 2. Empty deque */
    /* The newly crated deque should not be null */
    numbers = deque_new();
    assert(NULL != numbers && 0 == deque_count(numbers));

    /* The newly created deque should be empty */
    count = deque_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse an empty deque */
    rc = deque_traverse(numbers, number_print);
    assert(DEQUE_RC_EMPTY == rc);

    /* It should return null when trying to pick an element at the front of an empty deque */
    tmp = deque_pick_front(numbers);
    assert(NULL == tmp && 0 == deque_count(numbers));

    /* It should return null when trying to pick an element at the back of an empty deque */
    tmp = deque_pick_back(numbers);
    assert(NULL == tmp && 0 == deque_count(numbers));

    /* It should return null when trying to pop an element off the front of an empty deque */
    tmp = deque_pop_front(numbers);
    assert(NULL == tmp && 0 == deque_count(numbers));

    /* It should return null when trying to pop an element off the back of an empty deque */
    tmp = deque_pop_back(numbers);
    assert(NULL == tmp && 0 == deque_count(numbers));

    /* It must return 'empty deque' after destroying an empty deque */
    rc = deque_destroy(&numbers, number_destroy);
    assert(DEQUE_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3: non-empty deque */
    numbers = deque_new();
    assert(NULL != numbers && 0 == deque_count(numbers));

    /* It should fail when trying to push a null element onto the deque */
    rc = deque_push_front(numbers, NULL);
    assert(DEQUE_RC_ELEM_NULL == rc && 0 == deque_count(numbers));
    rc = deque_push_back(numbers, NULL);
    assert(DEQUE_RC_ELEM_NULL == rc && 0 == deque_count(numbers));

    /* It must succeed when pushing 8 numbers onto the deque, 4 at front and 4 at back */
    rc = deque_push_back(numbers, number_new(5));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 1 == deque_count(numbers) &&
           5 == *(int *)numbers->front->elem);
    rc = deque_push_front(numbers, number_new(4));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 2 == deque_count(numbers) &&
           4 == *(int *)numbers->front->elem);
    rc = deque_push_back(numbers, number_new(6));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 3 == deque_count(numbers) &&
           4 == *(int *)numbers->front->elem);
    rc = deque_push_front(numbers, number_new(3));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 4 == deque_count(numbers) &&
           3 == *(int *)numbers->front->elem);
    rc = deque_push_back(numbers, number_new(7));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 5 == deque_count(numbers) &&
           3 == *(int *)numbers->front->elem);
    rc = deque_push_front(numbers, number_new(2));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 6 == deque_count(numbers) &&
           2 == *(int *)numbers->front->elem);
    rc = deque_push_back(numbers, number_new(8));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 7 == deque_count(numbers) &&
           2 == *(int *)numbers->front->elem);
    rc = deque_push_front(numbers, number_new(1));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 8 == deque_count(numbers) &&
           1 == *(int *)numbers->front->elem);

    /* It should fail when trying to traverse the deque without a callback function provided */
    rc = deque_traverse(numbers, NULL);
    assert(DEQUE_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing a non-empty deque */
    rc = deque_traverse(numbers, number_print);
    assert(DEQUE_RC_OK == rc);

    /* It should succeed when picking the front (first) element of the deque */
    tmp = deque_pick_front(numbers);
    assert(NULL != tmp && 8 == deque_count(numbers) && 1 == *(int *)tmp);

    /* It should succeed when picking the back (last) element of the deque */
    tmp = deque_pick_back(numbers);
    assert(NULL != tmp && 8 == deque_count(numbers) && 8 == *(int *)tmp);

    /* It should succeed at popping two elements from the front of the deque */
    tmp = deque_pop_front(numbers);
    assert(NULL != numbers->front && 7 == deque_count(numbers) && NULL != tmp && 1 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_front(numbers);
    assert(NULL != numbers->front && 6 == deque_count(numbers) && NULL != tmp && 2 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    /* It should succeed at popping two elements from the back of the deque */
    tmp = deque_pop_back(numbers);
    assert(NULL != numbers->front && 5 == deque_count(numbers) && NULL != tmp && 8 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_back(numbers);
    assert(NULL != numbers->front && 4 == deque_count(numbers) && NULL != tmp && 7 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    /* It should succeed when traversing all the elements in the deque after them being popped */
    rc = deque_traverse(numbers, number_print);
    assert(DEQUE_RC_OK == rc);

    /* It should succeed at popping the remaining 4 elements (deque should be empty) */
    tmp = deque_pop_front(numbers);
    assert(NULL != numbers->front && 3 == deque_count(numbers) && NULL != tmp && 3 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_back(numbers);
    assert(NULL != numbers->front && 2 == deque_count(numbers) && NULL != tmp && 6 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_back(numbers);
    assert(NULL != numbers->front && 1 == deque_count(numbers) && NULL != tmp && 5 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_front(numbers);
    assert(NULL == numbers->front && 0 == deque_count(numbers) && NULL != tmp && 4 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = deque_pop_front(numbers);
    assert(NULL == numbers->front && 0 == deque_count(numbers) && NULL == tmp);

    /* Pushing 4 elements again */
    rc = deque_push_front(numbers, number_new(8));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 1 == deque_count(numbers));
    rc = deque_push_back(numbers, number_new(9));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 2 == deque_count(numbers));
    rc = deque_push_front(numbers, number_new(7));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 3 == deque_count(numbers));
    rc = deque_push_back(numbers, number_new(10));
    assert(DEQUE_RC_OK == rc && NULL != numbers->front && 4 == deque_count(numbers));

    /* It should fail when trying to traverse the deque without a callback function provided */
    rc = deque_traverse(numbers, NULL);
    assert(DEQUE_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing the deque */
    rc = deque_traverse(numbers, number_print);
    assert(DEQUE_RC_OK == rc);

    /* It should succeed at removing all elements from the deque (deque must be empty) */
    rc = deque_clear(numbers, number_destroy);
    assert(DEQUE_RC_OK == rc && NULL == numbers->front && 0 == deque_count(numbers));

    /* It should return 'deque empty' after destroying the deque */
    rc = deque_destroy(&numbers, number_destroy);
    assert(DEQUE_RC_EMPTY == rc);

    /* End of all tests. */

    return 0;
}
