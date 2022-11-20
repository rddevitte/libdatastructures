/**
 * \file   singly-linked-list-test.c
 * \brief  Circ. singly linked list - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/list/singly-linked-list.h"
#include "number/number.h"

int main(void)
{
    s_l_list_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null list */
    s_l_list_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null list */
    s_l_list_init(numbers);
    assert(NULL == numbers);

    /* It should fail when trying to insert elements into a null list */
    void *dummy = number_new(0);
    rc = s_l_list_insert_front(numbers, dummy);
    assert(S_L_LIST_RC_NULL == rc);
    rc = s_l_list_insert_back(numbers, dummy);
    assert(S_L_LIST_RC_NULL == rc);

    /* It should fail when trying to traverse a null list */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_NULL == rc);

    /* It should fail when trying to remove an element from a null list */
    tmp = s_l_list_remove_front(numbers);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null list */
    rc = s_l_list_clear(numbers, number_destroy);
    assert(S_L_LIST_RC_NULL == rc);

    /* It should fail when trying to destroy a null list */
    rc = s_l_list_destroy(NULL, number_destroy);
    assert(S_L_LIST_RC_NULL == rc);
    rc = s_l_list_destroy(&numbers, number_destroy);
    assert(S_L_LIST_RC_NULL == rc);

    /* End of part 1. */

    /* Part 2. Empty list */
    /* The newly created list should not be null */
    numbers = s_l_list_new();
    assert(NULL != numbers);

    /* The newly created list should be empty */
    assert(NULL == numbers->back && 0 == numbers->count);

    /* It should fail when trying to traverse an empty tree */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_EMPTY == rc);

    /* It should fail when trying to remove an element from an empty tree */
    tmp = s_l_list_remove_front(numbers);
    assert(NULL == tmp);

    /* It must return 'empty list' after destroying an empty list */
    rc = s_l_list_destroy(&numbers, number_destroy);
    assert(S_L_LIST_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3: list with a single element */
    numbers = s_l_list_new();
    assert(numbers != NULL && NULL == numbers->back && 0 == numbers->count);

    /* The list must have one node when inserting an element at the back of the empty list */
    rc = s_l_list_insert_back(numbers, dummy);
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && numbers->back->elem == dummy &&
           numbers->back->next == numbers->back && 1 == numbers->count);

    /* The traverse function must print the single element on the list */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_OK == rc);

    /* The list should be empty again after removing the single element from the list */
    dummy = s_l_list_remove_front(numbers);
    assert(NULL != dummy && NULL == numbers->back && 0 == numbers->count);

    /* The list must have one node when inserting an element at the front of the empty list */
    rc = s_l_list_insert_front(numbers, dummy);
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && numbers->back->elem == dummy &&
           numbers->back->next == numbers->back && 1 == numbers->count);

    /* The traverse function must print the single element on the list */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_OK == rc);

    /* It should succeed when destroying a list with one single element */
    rc = s_l_list_destroy(&numbers, number_destroy);
    assert(S_L_LIST_RC_OK == rc && NULL == numbers);

    /* End of part 3. */

    /* Part 4. List with multiple elements */
    numbers = s_l_list_new();
    assert(numbers != NULL && NULL == numbers->back && 0 == numbers->count);

    /* It must succeed when inserting 6 numbers into the list, 3 at front and 3 at back */
    rc = s_l_list_insert_back(numbers, number_new(4));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 1 == numbers->count &&
           4 == *(int *)numbers->back->elem);
    rc = s_l_list_insert_front(numbers, number_new(3));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 2 == numbers->count &&
           4 == *(int *)numbers->back->elem);
    rc = s_l_list_insert_back(numbers, number_new(5));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 3 == numbers->count &&
           5 == *(int *)numbers->back->elem);
    rc = s_l_list_insert_front(numbers, number_new(2));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 4 == numbers->count &&
           5 == *(int *)numbers->back->elem);
    rc = s_l_list_insert_back(numbers, number_new(6));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 5 == numbers->count &&
           6 == *(int *)numbers->back->elem);
    rc = s_l_list_insert_front(numbers, number_new(1));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 6 == numbers->count &&
           6 == *(int *)numbers->back->elem);

    /* It should succeed when traversing all the elements in the list after them being added */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_OK == rc);

    /* It should succeed at removing two elements from the front of the list */
    tmp = s_l_list_remove_front(numbers);
    assert(NULL != numbers->back && 5 == numbers->count && NULL != tmp && 1 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = s_l_list_remove_front(numbers);
    assert(NULL != numbers->back && 4 == numbers->count && NULL != tmp && 2 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    /* It should succeed when traversing all the elements in the list after them being removed */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_OK == rc);

    /* It should succeed at removing the remaining 4 elements (list should be empty) */
    tmp = s_l_list_remove_front(numbers);
    assert(NULL != numbers->back && 3 == numbers->count && NULL != tmp && 3 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = s_l_list_remove_front(numbers);
    assert(NULL != numbers->back && 2 == numbers->count && NULL != tmp && 4 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = s_l_list_remove_front(numbers);
    assert(NULL != numbers->back && 1 == numbers->count && NULL != tmp && 5 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = s_l_list_remove_front(numbers);
    assert(NULL == numbers->back && 0 == numbers->count && NULL != tmp && 6 == *(int *)tmp);
    number_print(tmp);
    number_destroy(&tmp);

    tmp = s_l_list_remove_front(numbers);
    assert(NULL == numbers->back && 0 == numbers->count && NULL == tmp);

    /* Inserting 4 elements again */
    rc = s_l_list_insert_front(numbers, number_new(9));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 1 == numbers->count);
    rc = s_l_list_insert_front(numbers, number_new(8));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 2 == numbers->count);
    rc = s_l_list_insert_back(numbers, number_new(10));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 3 == numbers->count);
    rc = s_l_list_insert_front(numbers, number_new(7));
    assert(S_L_LIST_RC_OK == rc && NULL != numbers->back && 4 == numbers->count);

    /* It should fail when trying to traverse the list without a callback function provided */
    rc = s_l_list_traverse(numbers, NULL);
    assert(S_L_LIST_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing the list */
    rc = s_l_list_traverse(numbers, number_print);
    assert(S_L_LIST_RC_OK == rc);

    /* It should succeed at removing all elements from the tree (list must be empty) */
    rc = s_l_list_clear(numbers, number_destroy);
    assert(S_L_LIST_RC_OK == rc && NULL == numbers->back && 0 == numbers->count);

    /* It should return 'list empty' after destroying the list */
    rc = s_l_list_destroy(&numbers, number_destroy);
    assert(S_L_LIST_RC_EMPTY == rc);

    /* End of all tests. */

    return 0;
}
