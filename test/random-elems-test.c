/**
 * \file   random-elems-test.c
 * \brief  Tree structure unit test simulation, which generates, prints and removes 1000 unique
 *         random number elements from the tree
 */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "number/number.h"
#include "rand-perm/rand-perm.h"
#include "libdatastructures/tree/tree.h"

int main()
{
    tree_rc_e rc;

    puts("1. generating 1000 numbers from 0 to 999");

    rand_perm_gen_t gen;

    rand_perm_gen_init(&gen, 0, 999);

    puts("2. inserting the 1000 numbers in the tree");

    tree_s *numbers = tree_new(false);

    for (int i = 1; i <= 1000; i++) {
        int n = rand_perm_gen_get_next(&gen);
        printf("2.%d. will insert %d\n", i, n);
        rc = tree_insert(numbers, number_new(n), number_compare);
        assert(TREE_RC_OK == rc && (size_t)i == numbers->count);
    }

    printf("numbers->count = %zu\n", numbers->count);

    puts("3. printing tree in an in-order fashion");

    tree_traverse(numbers, TREE_TRAVERSAL_INORDER, number_print);

    puts("4. removing the 1000 numbers from the tree");

    void *key = number_new(-1);

    for (int i = 999; i >= 0; i--) {
        *(int *)key = rand_perm_gen_get_next(&gen);
        printf("will remove %d\n", *(int *)key);
        void *elem = tree_remove(numbers, key, number_compare);
        assert(NULL != elem && (size_t)i == numbers->count);
        number_destroy(&elem);
    }

    number_destroy(&key);

    puts("5. destroying tree and generator");

    rand_perm_gen_destroy(&gen);

    rc = tree_destroy(&numbers, number_destroy);
    assert(TREE_RC_EMPTY == rc);

    return 0;
}
