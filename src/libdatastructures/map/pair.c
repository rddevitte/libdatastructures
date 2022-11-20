/**
 * \file   pair.c
 * \brief  Key-value Pair - functions implementations
 */
#include <stdlib.h>
#include "libdatastructures/map/pair.h"

/* ************************************************************************************************/

pair_s *pair_new(void *key, void *value)
{
    pair_s *new_pair = (pair_s *)malloc(sizeof(*new_pair));

    if (NULL != new_pair) {
        new_pair->key = key;
        new_pair->value = value;
    }

    return new_pair;
}

/* ************************************************************************************************/

void pair_destroy(pair_s **pair, void (*key_destroy)(void **), void (*value_destroy)(void **))
{
    if (NULL == pair || NULL == *pair)
        return;

    if (NULL != key_destroy)
        key_destroy(&(*pair)->key);

    if (NULL != value_destroy)
        value_destroy(&(*pair)->value);

    free(*pair);
    *pair = NULL;

    return;
}
