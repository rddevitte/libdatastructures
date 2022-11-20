/**
 * \file   tree-test.c
 * \brief  AVL tree data structure - unit test simulation for basic operations
 */
#include <assert.h>
#include <stddef.h>

#include "number/number.h"
#include "libdatastructures/tree/tree.h"

/* ************************************************************************************************/

int main(void)
{
    tree_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null tree */

    tree_s *numbers = NULL;

    /* It should do nothing when trying to initialize a null tree */
    tree_init(numbers, false);
    assert(NULL == numbers);

    /* It should fail when trying to insert elements into a null tree */
    void *dummy = number_new(0);
    rc = tree_insert(numbers, dummy, number_compare);
    assert(TREE_RC_NULL == rc);

    /* It should fail when trying to find an element in a null tree */
    tmp = tree_find(numbers, dummy, number_compare);
    assert(NULL == tmp);

    /* It should fail when trying to traverse a null tree */
    rc = tree_traverse(numbers, TREE_TRAVERSAL_INORDER, number_print);
    assert(TREE_RC_NULL == rc);

    /* It should fail when trying to remove an element from a null tree */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null tree */
    rc = tree_clear(numbers, number_destroy);
    assert(TREE_RC_NULL == rc);

    /* It should fail when trying to destroy a null tree */
    rc = tree_destroy(NULL, number_destroy);
    assert(TREE_RC_NULL == rc);
    rc = tree_destroy(&numbers, number_destroy);
    assert(TREE_RC_NULL == rc);

    /* End of part 1. */

    /* Part 2. Empty tree */

    /* The newly created tree should not be null */
    numbers = tree_new(false);
    assert(NULL != numbers);

    /* The newly created tree should be empty */
    assert(NULL == numbers->root && 0 == numbers->count);

    /* It should fail when trying to find an element in an empty tree */
    tmp = tree_find(numbers, dummy, number_compare);
    assert(NULL == tmp);

    /* It should return 'empty tree' when trying to traverse an empty tree */
    rc = tree_traverse(numbers, TREE_TRAVERSAL_INORDER, number_print);
    assert(TREE_RC_EMPTY == rc);

    /* It should return 'empty tree' when trying to remove an element from an empty tree */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL == tmp && NULL == numbers->root && 0 == numbers->count);

    /* The tree must have one element when adding an element to the empty tree */
    rc = tree_insert(numbers, dummy, number_compare);
    assert(TREE_RC_OK == rc && NULL != numbers->root && 1 == numbers->count);

    /* The tree must be empty after removing the single element from the tree
       (but not deleting the element from the memory) */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL != tmp && NULL == numbers->root && 0 == numbers->count && tmp == dummy);

    /* It must return 'empty tree' when trying to empty an already empty tree */
    rc = tree_clear(numbers, NULL);
    assert(TREE_RC_EMPTY == rc);

    /* It must return 'empty tree' after destroying an empty tree */
    rc = tree_destroy(&numbers, NULL);
    assert(TREE_RC_EMPTY == rc && NULL == numbers);

    /* End of part 2. */

    /* Part 3. Populated tree, no duplicates allowed */
    numbers = tree_new(false);
    assert(NULL != numbers && NULL == numbers->root && 0 == numbers->count);

    /* In the sequence of elements to be inserted below, 20 should be the root node
       due to self-balancing properties, and the tree element count should be equal
       to the number of elements inserted */
    rc = tree_insert(numbers, number_new(5), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(10), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(15), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(20), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(25), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(30), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(35), number_compare);
    assert(TREE_RC_OK == rc);
    *(int *)dummy = 20;
    assert(0 == number_compare(numbers->root->elem, dummy) && 7 == numbers->count);

    /* It should succeed when traversing a non-empty tree in all orders */
    rc = tree_traverse(numbers, TREE_TRAVERSAL_PREORDER, number_print);
    assert(TREE_RC_OK == rc);
    rc = tree_traverse(numbers, TREE_TRAVERSAL_INORDER, number_print);
    assert(TREE_RC_OK == rc);
    rc = tree_traverse(numbers, TREE_TRAVERSAL_POSTORDER, number_print);
    assert(TREE_RC_OK == rc);

    /* It should fail when trying to insert a valid element into a non-empty tree
       but without providing an elem. compare callback function */
    rc = tree_insert(numbers, dummy, NULL);
    assert(TREE_RC_ELEM_CB_NULL == rc);

    /* It should fail when trying to find a valid element in a non-empty tree
       but without providing an elem. compare callback function */
    tmp = tree_find(numbers, dummy, NULL);
    assert(NULL == tmp);

    /* It should fail when trying to remove a valid element from a non-empty tree
       but without providing an elem. compare callback function */
    tmp = tree_remove(numbers, dummy, NULL);
    assert(NULL == tmp && 7 == numbers->count);

    /* It should fail when trying to insert a null element into a non-empty tree */
    rc = tree_insert(numbers, NULL, number_compare);
    assert(TREE_RC_ELEM_NULL == rc);

    /* It should fail when trying to find a null element in a non-empty tree */
    tmp = tree_find(numbers, NULL, number_compare);
    assert(NULL == tmp);

    /* It should fail when trying to remove a null element from a non-empty tree */
    tmp = tree_remove(numbers, NULL, number_compare);
    assert(NULL == tmp);

    *(int *)dummy = 0;

    /* It should fail when trying to find a non-existing element in a non-empty tree */
    tmp = tree_find(numbers, dummy, number_compare);
    assert(NULL == tmp);

    /* It should fail when trying to remove a non-existing element in a non-empty tree */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL == tmp && 7 == numbers->count);

    /* It should succeed when trying to find an existing element in a non-empty tree */
    *(int *)dummy = 20;

    tmp = tree_find(numbers, dummy, number_compare);
    assert(NULL != tmp && 0 == number_compare(tmp, dummy));

    /* It should fail when trying to insert an existing element in a non-empty tree
       with no duplicate elements allowed */
    rc = tree_insert(numbers, dummy, number_compare);
    assert(TREE_RC_ELEM_DUPL == rc && 7 == numbers->count);

    /* It should succeed when trying to remove an existing element on a leaf node
       from a non-empty tree */
    *(int *)dummy = 25;
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL != tmp && numbers->count == 6);
    number_destroy(&tmp);
    tmp = tree_find(numbers, dummy, number_compare);
    assert(NULL == tmp);

    /* It should succeed when trying to destroy the tree and all its elements */
    rc = tree_destroy(&numbers, number_destroy);
    assert(TREE_RC_OK == rc && NULL == numbers);

    /* End of part 3. */

    /* Part 4. Populated tree, with duplicates allowed */
    numbers = tree_new(true);
    assert(NULL != numbers && NULL == numbers->root && 0 == numbers->count &&
           true == numbers->allow_duplicates);

    /* The unique elements in a tree that allow duplicates should be inserted normally
       as if it were inserted in a tree that doesn't allow duplicates */
    rc = tree_insert(numbers, number_new(5), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(10), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(15), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(20), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(25), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(30), number_compare);
    assert(TREE_RC_OK == rc);
    rc = tree_insert(numbers, number_new(35), number_compare);
    assert(TREE_RC_OK == rc);
    *(int *)dummy = 20;
    assert(0 == number_compare(numbers->root->elem, dummy) && 7 == numbers->count);

    /* It should succeed when trying to insert a duplicated element into the tree
       (case A: the existing element is in a leaf */
    rc = tree_insert(numbers, number_new(15), number_compare);
    assert(TREE_RC_OK == rc && 8 == numbers->count);

    /* It should succeed when trying to insert a duplicated element into the tree
       (case B: the existing element is in a node with a single child (either left or right) */
    rc = tree_insert(numbers, number_new(15), number_compare);
    assert(TREE_RC_OK == rc && 9 == numbers->count);

    /* It should succeed when trying to insert a duplicated element into the tree
       (case C: the existing element is in a node with two children */
    rc = tree_insert(numbers, number_new(30), number_compare);
    assert(TREE_RC_OK == rc && 10 == numbers->count);

    /* It should succeed when traversing the tree with duplicated elements, in all orders */
    rc = tree_traverse(numbers, TREE_TRAVERSAL_PREORDER, number_print);
    assert(TREE_RC_OK == rc);
    rc = tree_traverse(numbers, TREE_TRAVERSAL_INORDER, number_print);
    assert(TREE_RC_OK == rc);
    rc = tree_traverse(numbers, TREE_TRAVERSAL_POSTORDER, number_print);
    assert(TREE_RC_OK == rc);

    /* It should succeed when trying to find an element which is duplicated
       (Note: it is expected that only the first occurrence of the element is to be found */
    *(int *)dummy = 30;
    void *found1 = tree_find(numbers, dummy, number_compare);
    void *found2 = tree_find(numbers, dummy, number_compare);
    assert(NULL != found1 && found1 == found2);

    /* It should succeed when trying to remove a duplicated element */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL != tmp && 9 == numbers->count);
    number_destroy(&tmp);

    /* When trying to find an element which were duplicated but the first occurrence was deleted,
       it will return the element that remained */
    found2 = tree_find(numbers, dummy, number_compare);
    assert(NULL != found2 && found1 != found2);

    /* It should succeed when trying to remove an element which was duplicated
       but now it's unique */
    tmp = tree_remove(numbers, dummy, number_compare);
    assert(NULL != tmp && 8 == numbers->count && tmp == found2);
    number_destroy(&tmp);

    /* It should succeed when deleting all elements in a tree, whether it has duplicates */
    rc = tree_clear(numbers, number_destroy);
    assert(TREE_RC_OK == rc && NULL == numbers->root && 0 == numbers->count);
    rc = tree_destroy(&numbers, NULL);
    assert(TREE_RC_EMPTY == rc && NULL == numbers);

    /* End of all tests. */

    number_destroy(&dummy);

    return 0;
}
