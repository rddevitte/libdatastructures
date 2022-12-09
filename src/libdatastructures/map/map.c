/**
 * \file   map.c
 * \brief  Map - functions implementations
 */
#include <stdlib.h>
#include "libdatastructures/map/map.h"
#include "libdatastructures/map/pair.h"
#include "libdatastructures/tree/tree.h"

/* ************************************************************************************************/

static map_rc_e tree_rc_to_map_rc(tree_rc_e rc)
{
    map_rc_e new_rc;

    switch (rc) {
        case TREE_RC_OK:
            new_rc = MAP_RC_OK;
            break;
        case TREE_RC_EMPTY:
            new_rc = MAP_RC_EMPTY;
            break;
        case TREE_RC_ELEM_NULL:
            new_rc = MAP_RC_KEY_NULL;
            break;
        case TREE_RC_ELEM_DUPL:
            new_rc = MAP_RC_KEY_DUPL;
            break;
        case TREE_RC_ELEM_CB_NULL:
            new_rc = MAP_RC_PAIR_CB_NULL;
            break;
        default:
            new_rc = MAP_RC_NULL;
    }

    return new_rc;
}

/* ************************************************************************************************/

void map_init(map_s *map)
{
    tree_init(map, false);

    return;
}

/* ************************************************************************************************/

map_s *map_new(void)
{
    return tree_new(false);
}

/* ************************************************************************************************/

void *map_find(map_s *map, void *key, int (*map_pair_compare)(void *, void *))
{
    if (NULL == map || NULL == key || NULL == map_pair_compare)
        return NULL;

    pair_s *dummy = pair_new(key, NULL);

    pair_s *found_pair = (pair_s *)tree_find(map, dummy, map_pair_compare);

    free(dummy);

    if (NULL == found_pair)
        return NULL;

    return found_pair->value;
}

/* ************************************************************************************************/

map_rc_e map_insert(map_s *map, void *key, void *value, int (*map_pair_compare)(void *, void *))
{
    if (NULL == map)
        return MAP_RC_NULL;

    if (NULL == key)
        return MAP_RC_KEY_NULL;

    if (NULL == map_pair_compare)
        return MAP_RC_PAIR_CB_NULL;

    pair_s *new_pair = pair_new(key, value);

    map_rc_e rc = tree_rc_to_map_rc(tree_insert(map, new_pair, map_pair_compare));

    if (MAP_RC_OK != rc)
        free(new_pair);

    return rc;
}

/* ************************************************************************************************/

void *map_replace(map_s *map, void *key, void *new_value, int (*map_pair_compare)(void *, void *))
{
    if (NULL == map || NULL == key || NULL == map_pair_compare)
        return NULL;

    pair_s *dummy = pair_new(key, NULL);

    pair_s *found = (pair_s *)tree_find(map, dummy, map_pair_compare);

    free(dummy);

    if (NULL == found)
        return NULL;

    void *old_value = found->value;
    found->value = new_value;

    return old_value;
}

/* ************************************************************************************************/

map_rc_e map_traverse(map_s *map, void (*map_pair_visit)(void *))
{
    return tree_rc_to_map_rc(tree_traverse(map, TREE_TRAVERSAL_INORDER, map_pair_visit));
}

/* ************************************************************************************************/

pair_s *map_remove(map_s *map, void *key, int (*map_pair_compare)(void *, void *))
{
    if (NULL == map || NULL == key || NULL == map_pair_compare)
        return NULL;

    pair_s *dummy = pair_new(key, NULL);

    pair_s *removed = (pair_s *)tree_remove(map, dummy, map_pair_compare);

    free(dummy);

    return removed;
}

/* ************************************************************************************************/

map_rc_e map_clear(map_s *map, void (*map_pair_destroy)(void **))
{
    return tree_rc_to_map_rc(tree_clear(map, map_pair_destroy));
}

/* ************************************************************************************************/

map_rc_e map_destroy(map_s **map, void (*map_pair_destroy)(void **))
{
    return tree_rc_to_map_rc(tree_destroy(map, map_pair_destroy));
}
