/**
 * \file   map-test.c
 * \brief  Map data structure - unit test simulation for basic operations
 */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "fruit/fruit.h"
#include "number/number.h"
#include "libdatastructures/map/map.h"
#include "libdatastructures/map/pair.h"

/* ************************************************************************************************/

/**
 * \brief   Compare two fruit-number pairs by its key, which is a fruit element.
 * \param   p1  the first fruit-number pair element
 * \param   p2  the second fruit-number pair element
 * \return  a value which is the difference of the two keys of the pairs
 */
int fruits_numbers_pair_compare(void *p1, void *p2);

/**
 * \brief  Print a fruit-number pair
 * \param  p  the fruit-number pair to be printed
 */
void fruits_numbers_pair_print(void *p);

/**
 * \brief  Deallocate ('destroy') a fruit-number pair as well as its key (fruit) and value (number).
 * \param  p  the pair to be destroyed
 */
void fruits_numbers_pair_destroy(void **p);

/* ************************************************************************************************/

int main(void)
{
    map_rc_e rc;
    void *tmp = NULL;

    /* Part 1. Null map */

    map_s *fruits_to_numbers = NULL;

    /* It should do nothing when trying to initialize a null map */
    map_init(fruits_to_numbers);
    assert(NULL == fruits_to_numbers);

    /* It should fail when trying to insert a key-value pair into a null map */
    void *dummy_key = fruit_new(MANGO);
    void *dummy_value = number_new(0);

    rc = map_insert(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(MAP_RC_NULL == rc);

    /* It should fail when trying to replace a value of a pair in a null map */
    tmp = map_replace(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to find a value by its key in a null map */
    tmp = map_find(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to traverse a null map */
    rc = map_traverse(fruits_to_numbers, fruits_numbers_pair_print);
    assert(MAP_RC_NULL == rc);

    /* It should fail when trying to remove a value from a null map by its key */
    tmp = map_remove(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to empty a null map */
    rc = map_clear(fruits_to_numbers, fruits_numbers_pair_destroy);
    assert(MAP_RC_NULL == rc);

    /* It should fail when trying to destroy a null map */
    rc = map_destroy(NULL, fruits_numbers_pair_destroy);
    assert(MAP_RC_NULL == rc);
    rc = map_destroy(&fruits_to_numbers, fruits_numbers_pair_destroy);
    assert(MAP_RC_NULL == rc);

    /* End of part 1. */

    /* Part 2. Empty map */

    /* The newly created map should not be null */
    fruits_to_numbers = map_new();
    assert(NULL != fruits_to_numbers);

    /* The newly created map should be empty */
    assert(NULL == fruits_to_numbers->root && 0 == fruits_to_numbers->count);

    /* It should fail when trying to find a value in an empty map */
    tmp = map_find(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should return 'empty map' when trying to traverse an empty map */
    rc = map_traverse(fruits_to_numbers, fruits_numbers_pair_print);
    assert(MAP_RC_EMPTY == rc);

    /* It should fail when trying to replace a value of a pair in an empty map */
    tmp = map_replace(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should return 'empty map' when trying to remove a value by its key from an empty map */
    tmp = map_remove(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp && NULL == fruits_to_numbers->root && 0 == fruits_to_numbers->count);

    /* The map must have one key-value pair elem. when adding an element to the empty map */
    rc = map_insert(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc && NULL != fruits_to_numbers->root && 1 == fruits_to_numbers->count);

    /* It should succeed at replacing a value of a single pair giving its key in the map
       (in this case, the original and new value are the same) */
    tmp = map_replace(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(NULL != tmp && tmp == dummy_value);

    /* The map must be empty after removing the single pair from the map
       (but not deleting the pair from the memory) */
    pair_s *ptmp = map_remove(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL != ptmp && NULL == fruits_to_numbers->root && 0 == fruits_to_numbers->count &&
           ptmp->key == dummy_key && ptmp->value == dummy_value);
    pair_destroy(&ptmp, NULL, NULL);

    /* It must return 'empty map' after destroying an empty map */
    rc = map_destroy(&fruits_to_numbers, NULL);
    assert(MAP_RC_EMPTY == rc && NULL == fruits_to_numbers);

    /* End of part 2. */

    /* Part 3. Populated map */
    fruits_to_numbers = map_new();
    assert(NULL != fruits_to_numbers && NULL == fruits_to_numbers->root &&
           0 == fruits_to_numbers->count && false == fruits_to_numbers->allow_duplicates);

    /* Insert some fruits and random numbers into the fruits-numbers map */
    rc = map_insert(fruits_to_numbers, fruit_new(APPLE), number_new(18),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(BANANA), number_new(32),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(WATERMELON), number_new(25),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(PAPAYA), number_new(16),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(GRAPE), number_new(47),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(TANGERINE), number_new(50),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    rc = map_insert(fruits_to_numbers, fruit_new(ORANGE), number_new(88),
                    fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);
    assert(7 == fruits_to_numbers->count);

    /* It should succeed when traversing a non-empty map */
    rc = map_traverse(fruits_to_numbers, fruits_numbers_pair_print);
    assert(MAP_RC_OK == rc);

    /* It should fail when trying to insert a valid fruit into a non-empty fruits-numbers map
       but without providing a pair key compare callback function */
    rc = map_insert(fruits_to_numbers, dummy_key, dummy_value, NULL);
    assert(MAP_RC_PAIR_CB_NULL == rc);

    /* It should fail when trying to replace the number value of an existing fruit in the map,
       but without providing a pair key compare callback function */
    tmp = map_replace(fruits_to_numbers, dummy_key, dummy_value, NULL);
    assert(NULL == tmp);

    /* It should fail when trying to find a valid key-value pair in the map,
       but without providing a pair key compare callback function */
    tmp = map_find(fruits_to_numbers, dummy_key, NULL);
    assert(NULL == tmp);

    /* It should fail when trying to remove a valid key-value pair in the map,
       but without providing a pair key compare callback function */
    tmp = map_remove(fruits_to_numbers, dummy_key, NULL);
    assert(NULL == tmp);

    /* It shoud fail when trying to insert a key-value pair into the map with a null key */
    rc = map_insert(fruits_to_numbers, NULL, dummy_value, fruits_numbers_pair_compare);
    assert(MAP_RC_KEY_NULL == rc);

    /* It should fail when trying to replace the value of a pair in the map giving a null key */
    tmp = map_replace(fruits_to_numbers, NULL, dummy_value, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to find a pair in the map giving a null key */
    tmp = map_find(fruits_to_numbers, NULL, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to remove a pair from the map giving a null key */
    tmp = map_remove(fruits_to_numbers, NULL, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to find the number value of a non-existing fruit in the map */
    tmp = map_find(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should fail when trying to remove a non-existing fruit in the map */
    tmp = map_remove(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL == tmp);

    /* It should succeed when trying to insert a yet non-existing fruit in the map */
    rc = map_insert(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(MAP_RC_OK == rc);

    /* It should succeed when trying to find an existing element in the map */
    tmp = map_find(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(tmp == dummy_value && 8 == fruits_to_numbers->count);

    /* It should fail when trying to insert a key-value pair in the map with an existing key */
    rc = map_insert(fruits_to_numbers, dummy_key, dummy_value, fruits_numbers_pair_compare);
    assert(MAP_RC_KEY_DUPL == rc);

    /* It should succeed when trying to replace the value of a pair in the map
       with an existing key */
    void *new_dummy_value = number_new(68);
    tmp = map_replace(fruits_to_numbers, dummy_key, new_dummy_value, fruits_numbers_pair_compare);
    assert(tmp == dummy_value);

    /* It should succeed when trying to remove a pair with an existing key from the map */
    pair_s *removed = map_remove(fruits_to_numbers, dummy_key, fruits_numbers_pair_compare);
    assert(NULL != removed && removed->key == dummy_key && removed->value == new_dummy_value &&
           7 == fruits_to_numbers->count);
    pair_destroy(&removed, NULL, NULL);

    /* It should succeed when trying to destroy the map and all its pair elements */
    rc = map_destroy(&fruits_to_numbers, fruits_numbers_pair_destroy);
    assert(MAP_RC_OK == rc && NULL == fruits_to_numbers);

    /* End of all tests. */

    fruit_destroy(&dummy_key);
    number_destroy(&dummy_value);
    number_destroy(&new_dummy_value);

    return 0;
}

/* ************************************************************************************************/

int fruits_numbers_pair_compare(void *p1, void *p2)
{
    if (NULL == p1 && NULL == p2)
        return 0;

    if (NULL == p2)
        return -*(int *)(*(pair_s *)p1).key;

    if (NULL == p1)
        return *(int *)(*(pair_s *)p2).key;

    return fruit_compare((*(pair_s *)p1).key, (*(pair_s *)p2).key);
}

void fruits_numbers_pair_print(void *p)
{
    printf("p = %p", p);

    if (NULL != p) {
        pair_s *pair = (pair_s *)p;

        printf("\n  p->key: ");
        fruit_print(pair->key);
        printf("  p->value: ");
        number_print(pair->value);
    }

    putchar('\n');

    return;
}

void fruits_numbers_pair_destroy(void **p)
{
    pair_destroy((pair_s **)p, fruit_destroy, number_destroy);
    return;
}
