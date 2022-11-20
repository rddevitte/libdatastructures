/**
 * \file   queue-test.c
 * \brief  Queue data structure - unit test simulation for basic functions
 */
#include <assert.h>
#include "libdatastructures/queue/queue.h"
#include "number/number.h"

int main(void)
{
    queue_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null queue */
    queue_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null queue */
    queue_init(numbers);
    assert(NULL == numbers);

    /* It should fail when trying to enqueue elements into a null queue */
    void *dummy = number_new(0);
    rc = queue_enqueue(numbers, dummy);
    assert(QUEUE_RC_NULL == rc);

    /* It should return zero when getting the number of elements of a null queue */
    size_t count = queue_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse a null queue */
    rc = queue_traverse(numbers, number_print);
    assert(QUEUE_RC_NULL == rc);

    /* It should return null when trying to pick an element at the front of a null queue */
    tmp = queue_pick(numbers);
    assert(NULL == tmp);

    /* It should return null when trying to dequeue an element off a null queue */
    tmp = queue_dequeue(numbers);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null queue */
    rc = queue_clear(numbers, number_destroy);
    assert(QUEUE_RC_NULL == rc);

    /* It should fail when trying to destroy a null queue */
    rc = queue_destroy(NULL, number_destroy);
    assert(QUEUE_RC_NULL == rc);
    rc = queue_destroy(&numbers, number_destroy);
    assert(QUEUE_RC_NULL == rc);

    /* End of part 1. */
    number_destroy(&dummy);

    /* Part 2. Empty queue */
    /* The newly crated queue should not be null */
    numbers = queue_new();
    assert(NULL != numbers && 0 == queue_count(numbers));

    /* The newly created queue should be empty */
    count = queue_count(numbers);
    assert(0 == count);

    /* It should fail when trying to traverse an empty queue */
    rc = queue_traverse(numbers, number_print);
    assert(QUEUE_RC_EMPTY == rc);

    /* It should return null when trying to pick an element at the front of an empty queue */
    tmp = queue_pick(numbers);
    assert(NULL == tmp && 0 == queue_count(numbers));

    /* It should return null when trying to dequeue an element off an empty queue */
    tmp = queue_dequeue(numbers);
    assert(NULL == tmp && 0 == queue_count(numbers));

    /* It must return 'empty queue' after destroying an empty queue */
    rc = queue_destroy(&numbers, number_destroy);
    assert(QUEUE_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3: non-empty queue */
    numbers = queue_new();
    assert(NULL != numbers && 0 == queue_count(numbers));

    /* It should fail when trying to enqueue a null element onto the queue */
    rc = queue_enqueue(numbers, NULL);
    assert(QUEUE_RC_ELEM_NULL == rc && 0 == queue_count(numbers));

    /* It should succeed at enqueuing three elements onto the queue */
    rc = queue_enqueue(numbers, number_new(10));
    assert(QUEUE_RC_OK == rc && 1 == queue_count(numbers));
    rc = queue_enqueue(numbers, number_new(20));
    assert(QUEUE_RC_OK == rc && 2 == queue_count(numbers));
    rc = queue_enqueue(numbers, number_new(30));
    assert(QUEUE_RC_OK == rc && 3 == queue_count(numbers));

    /* It should fail when trying to traverse the queue without a callback function provided */
    rc = queue_traverse(numbers, NULL);
    assert(QUEUE_RC_ELEM_CB_NULL == rc);

    /* It should succeed when traversing a non-empty queue */
    rc = queue_traverse(numbers, number_print);
    assert(QUEUE_RC_OK == rc);

    /* It should succeed when picking the front element of the queue */
    tmp = queue_pick(numbers);
    assert(NULL != tmp && 3 == queue_count(numbers) && 10 == *(int *)tmp);

    /* It should succeed when dequeueing the elements off the queue */
    tmp = queue_dequeue(numbers);
    assert(NULL != tmp && 2 == queue_count(numbers) && 10 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = queue_dequeue(numbers);
    assert(NULL != tmp && 1 == queue_count(numbers) && 20 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = queue_dequeue(numbers);
    assert(NULL != tmp && 0 == queue_count(numbers) && 30 == *(int *)tmp);
    number_destroy(&tmp);
    tmp = queue_dequeue(numbers);
    assert(NULL == tmp && 0 == queue_count(numbers));

    /* Enqueue three elements again */
    rc = queue_enqueue(numbers, number_new(40));
    assert(QUEUE_RC_OK == rc && 1 == queue_count(numbers));
    rc = queue_enqueue(numbers, number_new(50));
    assert(QUEUE_RC_OK == rc && 2 == queue_count(numbers));
    rc = queue_enqueue(numbers, number_new(60));
    assert(QUEUE_RC_OK == rc && 3 == queue_count(numbers));

    /* It should succeed at removing all elements from the queue (queue must be empty) */
    rc = queue_clear(numbers, number_destroy);
    assert(QUEUE_RC_OK == rc && 0 == queue_count(numbers));

    /* It should return 'list empty' after destroying the list */
    rc = queue_destroy(&numbers, number_destroy);
    assert(QUEUE_RC_EMPTY == rc && NULL == numbers && 0 == queue_count(numbers));

    return 0;
}
