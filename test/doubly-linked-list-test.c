/**
 * \file   doubly-linked-list-test.c
 * \brief  Circ. doubly linked list - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/list/doubly-linked-list.h"
#include "number/number.h"

int main(void)
{
    d_l_list_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null list */
    d_l_list_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null list */
    d_l_list_init(numbers);
    assert(NULL == numbers);

    /* It should fail when trying to insert elements into a null list */
    void *dummy = number_new(0);
    rc = d_l_list_insert_front(numbers, dummy);
    assert(D_L_LIST_RC_NULL == rc);
    rc = d_l_list_insert_back(numbers, dummy);
    assert(D_L_LIST_RC_NULL == rc);

    /* It should fail when trying to traverse a null list */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_NULL == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_NULL == rc);

    /* It should fail when trying to remove an element from a null list */
    tmp = d_l_list_remove_front(numbers);
    assert(NULL == tmp);
    tmp = d_l_list_remove_back(numbers);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null list */
    rc = d_l_list_clear(numbers, number_destroy);
    assert(D_L_LIST_RC_NULL == rc);

    /* It should fail when trying to destroy a null list */
    rc = d_l_list_destroy(NULL, number_destroy);
    assert(D_L_LIST_RC_NULL == rc);
    rc = d_l_list_destroy(&numbers, number_destroy);
    assert(D_L_LIST_RC_NULL == rc);

    /* End of part 1. */

    /* Part 2. Empty list */
    /* The newly created list should not be null */
    numbers = d_l_list_new();
    assert(NULL != numbers);

    /* The newly created list should be empty */
    assert(NULL == numbers->front && 0 == numbers->count);

    /* It should fail when trying to traverse an empty tree */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_EMPTY == rc);
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_EMPTY == rc);

    /* It should fail when trying to remove an element from an empty tree */
    tmp = d_l_list_remove_front(numbers);
    assert(NULL == tmp);
    tmp = d_l_list_remove_back(numbers);
    assert(NULL == tmp);

    /* It must return 'empty list' after destroying an empty list */
    rc = d_l_list_destroy(&numbers, number_destroy);
    assert(D_L_LIST_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3: list with a single element */
    numbers = d_l_list_new();
    assert(numbers != NULL && NULL == numbers->front && 0 == numbers->count);

    /* The list must have one node when inserting an element at the back of the empty list */
    rc = d_l_list_insert_back(numbers, dummy);
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && numbers->front->elem == dummy &&
           numbers->front->next == numbers->front && numbers->front->prev == numbers->front &&
           1 == numbers->count);

    /* The traverse functions must print the single element on the list */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);

    /* The list should be empty again after removing the single element from the list */
    dummy = d_l_list_remove_back(numbers);
    assert(NULL != dummy && NULL == numbers->front && 0 == numbers->count);

    /* The list must have one node when inserting an element at the front of the empty list */
    rc = d_l_list_insert_front(numbers, dummy);
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && numbers->front->elem == dummy &&
           numbers->front->next == numbers->front && numbers->front->prev == numbers->front &&
           1 == numbers->count);

    /* The traverse function must print the single element on the list */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);

    /* The list should be empty again after removing the single element from the list */
    dummy = d_l_list_remove_front(numbers);
    assert(NULL != dummy && NULL == numbers->front && 0 == numbers->count);

    /* Re-inserting an element into the empty list, again */
    rc = d_l_list_insert_back(numbers, dummy);
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && numbers->front->elem == dummy &&
           numbers->front->next == numbers->front && numbers->front->prev == numbers->front &&
           1 == numbers->count);

    /* It should succeed when destroying a list with one single element */
    rc = d_l_list_destroy(&numbers, number_destroy);
    assert(D_L_LIST_RC_OK == rc && NULL == numbers);

    /* End of part 3. */

    /* Part 4. List with multiple elements */
    numbers = d_l_list_new();
    assert(numbers != NULL && NULL == numbers->front && 0 == numbers->count);

    /* It must succeed when inserting 8 numbers into the list, 4 at front and 4 at back */
    rc = d_l_list_insert_back(numbers, number_new(5));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 1 == numbers->count &&
           5 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_front(numbers, number_new(4));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 2 == numbers->count &&
           4 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_back(numbers, number_new(6));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 3 == numbers->count &&
           4 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_front(numbers, number_new(3));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 4 == numbers->count &&
           3 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_back(numbers, number_new(7));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 5 == numbers->count &&
           3 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_front(numbers, number_new(2));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 6 == numbers->count &&
           2 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_back(numbers, number_new(8));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 7 == numbers->count &&
           2 == *(int *)numbers->front->elem);
    rc = d_l_list_insert_front(numbers, number_new(1));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 8 == numbers->count &&
           1 == *(int *)numbers->front->elem);

    /* It should succeed when traversing all the elements in the list after them being added */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);

    /* It should succeed at removing two elements from the front of the list */
    tmp = d_l_list_remove_front(numbers);
    assert(NULL != numbers->front && 7 == numbers->count && NULL != tmp && 1 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_front(numbers);
    assert(NULL != numbers->front && 6 == numbers->count && NULL != tmp && 2 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    /* It should succeed at removing two elements from the back of the list */
    tmp = d_l_list_remove_back(numbers);
    assert(NULL != numbers->front && 5 == numbers->count && NULL != tmp && 8 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_back(numbers);
    assert(NULL != numbers->front && 4 == numbers->count && NULL != tmp && 7 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    /* It should succeed when traversing all the elements in the list after them being removed */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);

    /* It should succeed at removing the remaining 4 elements (list should be empty) */
    tmp = d_l_list_remove_front(numbers);
    assert(NULL != numbers->front && 3 == numbers->count && NULL != tmp && 3 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_back(numbers);
    assert(NULL != numbers->front && 2 == numbers->count && NULL != tmp && 6 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_back(numbers);
    assert(NULL != numbers->front && 1 == numbers->count && NULL != tmp && 5 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_front(numbers);
    assert(NULL == numbers->front && 0 == numbers->count && NULL != tmp && 4 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = d_l_list_remove_front(numbers);
    assert(NULL == numbers->front && 0 == numbers->count && NULL == tmp);

    /* Inserting 4 elements again */
    rc = d_l_list_insert_front(numbers, number_new(8));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 1 == numbers->count);
    rc = d_l_list_insert_back(numbers, number_new(9));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 2 == numbers->count);
    rc = d_l_list_insert_front(numbers, number_new(7));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 3 == numbers->count);
    rc = d_l_list_insert_back(numbers, number_new(10));
    assert(D_L_LIST_RC_OK == rc && NULL != numbers->front && 4 == numbers->count);

    /* It should fail when trying to traverse the list without a callback function provided */
    rc = d_l_list_traverse_forward(numbers, NULL);
    assert(D_L_LIST_RC_ELEM_CB_NULL == rc);
    rc = d_l_list_traverse_backward(numbers, NULL);
    assert(D_L_LIST_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing the list */
    rc = d_l_list_traverse_forward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);
    rc = d_l_list_traverse_backward(numbers, number_print);
    assert(D_L_LIST_RC_OK == rc);

    /* It should succeed at removing all elements from the list (list must be empty) */
    rc = d_l_list_clear(numbers, number_destroy);
    assert(D_L_LIST_RC_OK == rc && NULL == numbers->front && 0 == numbers->count);

    /* It should return 'list empty' after destroying the list */
    rc = d_l_list_destroy(&numbers, number_destroy);
    assert(D_L_LIST_RC_EMPTY == rc);

    /* End of all tests. */

    return 0;
}
