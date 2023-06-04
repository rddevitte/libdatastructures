/**
 * \file   array-test.c
 * \brief  Array data structure - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/array/array.h"
#include "number/number.h"

int main(void)
{
    array_rc_e rc;
    void *tmp;

    /* Part 1. Null array */
    array_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null array */
    array_init(numbers, 5);
    assert(NULL == numbers);

    /* It should fail when trying to push elements onto a null array */
    void *dummy = number_new(0);
    rc = array_push_back(numbers, dummy);
    assert(ARRAY_RC_NULL == rc);
    rc = array_push_front(numbers, dummy);
    assert(ARRAY_RC_NULL == rc);
    rc = array_push_at(numbers, dummy, 0);
    assert(ARRAY_RC_NULL == rc);

    /* It should return zero when getting the number of elements of a null array */
    size_t count = array_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse a null array */
    rc = array_traverse(numbers, number_print);
    assert(ARRAY_RC_NULL == rc);

    /* It should return null when trying to pick an element from a null array */
    tmp = array_pick_front(numbers);
    assert(NULL == tmp);
    tmp = array_pick_back(numbers);
    assert(NULL == tmp);
    tmp = array_pick_at(numbers, 0);
    assert(NULL == tmp);

    /* It should return null when trying to pop an element off a null array */
    tmp = array_pop_front(numbers);
    assert(NULL == tmp);
    tmp = array_pop_back(numbers);
    assert(NULL == tmp);
    tmp = array_pop_at(numbers, 0);
    assert(NULL == tmp);

    /* It should return null when trying to replace an element of a null array */
    tmp = array_replace(numbers, NULL, 0);
    assert(NULL == tmp);

    /* It should fail when trying to swap two elements of a null array */
    rc = array_swap(numbers, 0, 0);
    assert(ARRAY_RC_NULL == rc);

    /* It should return an invalid position when trying to find an element in a null array */
    int pos = array_find_next(numbers, NULL, 0, number_compare);
    assert(-1 == pos);

    /* It should fail when trying to traverse a null array */
    rc = array_traverse(numbers, number_print);
    assert(ARRAY_RC_NULL == rc);

    /* It should fail when trying to clear a null array */
    rc = array_clear(numbers, number_destroy);
    assert(ARRAY_RC_NULL == rc);

    /* It should fail when trying to destroy a null array */
    rc = array_destroy(NULL, number_destroy);
    assert(ARRAY_RC_NULL == rc);
    rc = array_destroy(&numbers, number_destroy);
    assert(ARRAY_RC_NULL == rc && NULL == numbers);

    /* End of part 1. */
    number_destroy(&dummy);

    /* Part 2. Empty array */

    /* The newly created array should not be null */
    numbers = array_new(10);
    assert(NULL != numbers && 10 == numbers->length && 0 == array_count(numbers));

    /* It should return null when trying to pick an element from an empty array */
    tmp = array_pick_front(numbers);
    assert(NULL == tmp && 0 == array_count(numbers));
    tmp = array_pick_back(numbers);
    assert(NULL == tmp && 0 == array_count(numbers));
    tmp = array_pick_at(numbers, 0);
    assert(NULL == tmp && 0 == array_count(numbers));

    /* It should return null when trying to pop an element off an empty array */
    tmp = array_pop_front(numbers);
    assert(NULL == tmp && 0 == array_count(numbers));
    tmp = array_pop_back(numbers);
    assert(NULL == tmp && 0 == array_count(numbers));
    tmp = array_pop_at(numbers, 0);
    assert(NULL == tmp && 0 == array_count(numbers));

    /* It should return null when trying to replace an element of an empty array */
    tmp = array_replace(numbers, tmp, 0);
    assert(NULL == tmp);

    /* It should fail when trying to swap two elements of an empty array */
    rc = array_swap(numbers, 0, 0);
    assert(ARRAY_RC_EMPTY == rc);

    /* It should fail when trying to find an element in an empty array */
    pos = array_find_next(numbers, tmp, 0, number_compare);
    assert(-1 == pos);

    /* It should fail when trying to traverse an empty array */
    rc = array_traverse(numbers, number_print);
    assert(ARRAY_RC_EMPTY == rc);

    /* It should fail when trying to clear an already empty array */
    rc = array_clear(numbers, number_destroy);
    assert(ARRAY_RC_EMPTY == rc);

    /* It should succeed when trying to destroy an empty array */
    rc = array_destroy(&numbers, number_destroy);
    assert(ARRAY_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3. Non-empty array */

    numbers = array_new(10);
    assert(NULL != numbers && 10 == numbers->length && 0 == array_count(numbers));

    /* It should succeed when trying to push elements onto the array */
    rc = array_push_front(numbers, number_new(4));
    assert(ARRAY_RC_OK == rc && 1 == array_count(numbers));
    rc = array_push_back(numbers, number_new(4));
    assert(ARRAY_RC_OK == rc && 2 == array_count(numbers));
    rc = array_push_at(numbers, number_new(3), 1);
    assert(ARRAY_RC_OK == rc && 3 == array_count(numbers));
    rc = array_push_front(numbers, number_new(5));
    assert(ARRAY_RC_OK == rc && 4 == array_count(numbers));
    rc = array_push_back(numbers, number_new(5));
    assert(ARRAY_RC_OK == rc && 5 == array_count(numbers));
    rc = array_push_at(numbers, number_new(2), 4);
    assert(ARRAY_RC_OK == rc && 6 == array_count(numbers));

    /* It should succeed when trying to push a null element onto the array */
    rc = array_push_at(numbers, NULL, 2);
    assert(ARRAY_RC_OK == rc && 7 == array_count(numbers));

    /* It should fail when trying to push an element onto an invalid position of the array */
    rc = array_push_at(numbers, NULL, 8);
    assert(ARRAY_RC_INVALID_POS == rc);
    rc = array_push_at(numbers, NULL, -1);
    assert(ARRAY_RC_INVALID_POS == rc);

    /* It should succeed when trying to traverse a non-empty array */
    rc = array_traverse(numbers, number_print);
    assert(ARRAY_RC_OK == rc);

    /* It should fail when trying to traverse a non-empty array
       without a callback function provided */
    rc = array_traverse(numbers, NULL);
    assert(ARRAY_RC_ELEM_CB_NULL == rc);

    /* It should succeed when trying to pick elements from a non-null array */
    tmp = array_pick_front(numbers);
    assert(NULL != tmp && 5 == *(int *)tmp && 7 == array_count(numbers));
    tmp = array_pick_at(numbers, 3);
    assert(NULL != tmp && 3 == *(int *)tmp && 7 == array_count(numbers));
    tmp = array_pick_back(numbers);
    assert(NULL != tmp && 5 == *(int *)tmp && 7 == array_count(numbers));

    /* It should fail when trying to pick an element from an invalid position of the array */
    tmp = array_pick_at(numbers, 7);
    assert(NULL == tmp && 7 == array_count(numbers));

    /* It should succeed when trying to pop elements off a non-null array */
    tmp = array_pop_front(numbers);
    assert(NULL != tmp && 5 == *(int *)tmp && 6 == array_count(numbers));
    number_destroy(&tmp);
    tmp = array_pop_back(numbers);
    assert(NULL != tmp && 5 == *(int *)tmp && 5 == array_count(numbers));
    number_destroy(&tmp);
    tmp = array_pop_at(numbers, 2);
    assert(NULL != tmp && 3 == *(int *)tmp && 4 == array_count(numbers));
    number_destroy(&tmp);

    /* It should fail when trying to pop an element off an invalid position of the array */
    tmp = array_pop_at(numbers, 4);
    assert(NULL == tmp && 4 == array_count(numbers));
    tmp = array_pop_at(numbers, -1);
    assert(NULL == tmp && 4 == array_count(numbers));

    /* It should succeed when trying to replace an element from a
       valid, arbitrary position of the array */
    tmp = array_replace(numbers, number_new(8), 3);
    assert(NULL != tmp && 2 == *(int *)tmp && 4 == array_count(numbers));
    number_destroy(&tmp);

    /* It should fail when trying to replace an element from an invalid position of the array */
    tmp = array_replace(numbers, NULL, 5);
    assert(NULL == tmp && 4 == array_count(numbers));
    tmp = array_replace(numbers, NULL, -1);
    assert(NULL == tmp && 4 == array_count(numbers));

    /* It should succeed when trying to swap two elements of a non-empty array */
    rc = array_swap(numbers, 1, 3);
    assert(ARRAY_RC_OK == rc && 4 == array_count(numbers));

    /* It should fail when trying to swap two elements of a non-empty array
       providing invalid positions */
    rc = array_swap(numbers, 0, -1);
    assert(ARRAY_RC_INVALID_POS == rc);
    rc = array_swap(numbers, -1, -1);
    assert(ARRAY_RC_INVALID_POS == rc);
    rc = array_swap(numbers, -1, 0);
    assert(ARRAY_RC_INVALID_POS == rc);
    rc = array_swap(numbers, 0, 0);
    assert(ARRAY_RC_INVALID_POS == rc);

    /* It should succeed when trying to find an existing (either repeating or not) element
       of a non-empty array */
    tmp = number_new(4);
    assert(NULL != tmp && 4 == *(int *)tmp);
    pos = array_find_next(numbers, tmp, 0, number_compare);
    assert(0 == pos && 4 == array_count(numbers));
    pos = array_find_next(numbers, tmp, pos + 1, number_compare);
    assert(2 == pos && 4 == array_count(numbers));
    number_destroy(&tmp);

    /* It should fail when trying to find a non-existing element of a non-empty array */
    tmp = number_new(6);
    assert(NULL != tmp && 6 == *(int *)tmp);
    pos = array_find_next(numbers, tmp, 0, number_compare);
    assert(-1 == pos && 4 == array_count(numbers));

    /* It should fail when trying to find an element of a non-empty array
       providing an invalid starting position */
    pos = array_find_next(numbers, tmp, -1, number_compare);
    assert(-1 == pos && 4 == array_count(numbers));

    /* It should fail when trying to find an element of a non-empty array
       without a callback function provided */
    pos = array_find_next(numbers, tmp, 0, NULL);
    assert(-1 == pos && 4 == array_count(numbers));

    number_destroy(&tmp);

    /* It should succeed when trying to destroy a non-empty array */
    rc = array_destroy(&numbers, number_destroy);
    assert(ARRAY_RC_OK == rc && NULL == numbers);

    /* End of part 3. */

    /* Part 4. Full array */

    numbers = array_new(3);
    assert(NULL != numbers && 3 == numbers->length && 0 == array_count(numbers));
    rc = array_push_front(numbers, number_new(10));
    assert(ARRAY_RC_OK == rc && 1 == array_count(numbers));
    rc = array_push_back(numbers, number_new(30));
    assert(ARRAY_RC_OK == rc && 2 == array_count(numbers));
    rc = array_push_at(numbers, number_new(20), 1);
    assert(ARRAY_RC_OK == rc && 3 == array_count(numbers));

    /* It should fail when trying to push an element onto a full array */
    tmp = number_new(40);
    rc = array_push_front(numbers, tmp);
    assert(ARRAY_RC_FULL == rc && 3 == array_count(numbers));
    rc = array_push_back(numbers, tmp);
    assert(ARRAY_RC_FULL == rc && 3 == array_count(numbers));
    rc = array_push_at(numbers, tmp, 1);
    assert(ARRAY_RC_FULL == rc && 3 == array_count(numbers));
    number_destroy(&tmp);

    /* End of part 4. */

    rc = array_destroy(&numbers, number_destroy);
    assert(ARRAY_RC_OK == rc && NULL == numbers);

    /* End of all tests. */

    return 0;
}
