/**
 * \file   map.h
 * \brief  Map - structure, types and functions
 */
#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libdatastructures/map/pair.h"
#include "libdatastructures/tree/tree.h"

/* ************************************************************************************************/

/** Map data structure type, which is actually a "wrapper" of an AVL tree */
typedef tree_s map_s;

/** Map operations return codes */
enum map_rc {
    /** No error */
    MAP_RC_OK = TREE_RC_OK,
    /** Map is null */
    MAP_RC_NULL = TREE_RC_NULL,
    /** Map is empty (contains no key-value pair elements) */
    MAP_RC_EMPTY = TREE_RC_EMPTY,
    /** Map key element to be inserted is null */
    MAP_RC_KEY_NULL = TREE_RC_ELEM_NULL,
    /** Map key element is duplicated (it already exists on the map) */
    MAP_RC_KEY_DUPL = TREE_RC_ELEM_DUPL,
    /** The callback function to operate on the map key or value elements is null */
    MAP_RC_PAIR_CB_NULL = TREE_RC_ELEM_CB_NULL,
};

/** Map operations return codes type */
typedef enum map_rc map_rc_e;

/* Map functions (operations) *********************************************************************/

/**
 * \brief  Initialize a map.
 * \param  map  pointer to the map to be initialized
 */
void map_init(map_s *map);

/**
 * \brief   Create and initialize a map.
 * \return  a pointer to the allocated map
 */
map_s *map_new(void);

/**
 * \brief   Search a value from a key-value pair element based on its key.
 * \param   map           the map where the search will take place
 * \param   key           the key element to be compared to all the others in the tree
 * \param   pair_compare  a pair comparing callback function, which must compare the keys of both
 *                        pairs; must return 0 if both are 'equal', > 0 if the second key is
 *                        'greater' than the first one, or < 0 if the second key is 'lesser' than
 *                        the first one
 * \return  pointer to the value element whose key is found in the map; NULL if the key wasn't found
 */
void *map_find(map_s *map, void *key, int (*pair_compare)(void *, void *));

/**
 * \brief   Insert a key-value pair onto the map.
 * \param   map           the map whose pair is to be inserted onto
 * \param   key           the key of the pair to be inserted
 * \param   value         the value of the pair to be inserted
 * \param   pair_compare  a pair comparing callback function, which must compare the keys of both
 *                        pairs, used to take the decision where the key-value pair should be
 *                        placed (whether at the right or left of the current pair elem.); must
 *                        return 0 if both are 'equal', > 0 if the second key is 'greater' than the
 *                        first key;, or < 0 if the second key is 'lesser' than the first one
 * \return  the return code for the insert operation
 */
map_rc_e map_insert(map_s *map, void *key, void *value, int (*pair_compare)(void *, void *));

/**
 * \brief   Replace the value of a key-value pair in the map, assuming its key exists
 * \param   map           the map whose value of the pair is to be replaced
 * \param   key           the key of the pair whose value is to be replaced
 * \param   new_value     the new value
 * \param   pair_compare  a pair comparing callback function, which must compare the keys of both
 *                        pairs; must return 0 if both are 'equal', > 0 if the second key is
 *                        'greater' than the first one, or < 0 if the second key is 'lesser' than
 *                        the first one
 * \return  the old value which was replaced by the new one; NULL if the key wasn't found or if the
 *          old value was actually null. It's the library user's responsibility to deallocate the
 *          returned value
 */
void *map_replace(map_s *map, void *key, void *new_value, int (*pair_compare)(void *, void *));

/**
 * \brief   Traverse all the key-value pair elements in-order, applying the 'pair_visit' callback
 *          function to all its elements
 * \param   map         the map to be traversed by
 * \param   pair_visit  pointer to a callback function to be applied to all pair elements in the map
 * \return  the return code for the traversal operation
 */
map_rc_e map_traverse(map_s *map, void (*pair_visit)(void *));

/**
 * \brief   Remove a key-value pair element from the tree.
 * \param   map           the tree whose pair is to be removed from
 * \param   key           the key of the pair to be removed
 * \param   pair_compare  a pair comparing callback function, which must compare the keys of both
 *                        pairs; must return 0 if both are 'equal', > 0 if the second key is
 *                        'greater' than the first one, or < 0 if the second key is 'lesser' than
 *                        the first one
 * \return  pointer to the pair removed from the map; NULL if the pair element wasn't found. It's
 *          the library user's responsibility to deallocate the key and values of the pair and the
 *          pair itself
 */
pair_s *map_remove(map_s *map, void *key, int (*pair_compare)(void *, void *));

/**
 * \brief   Deallocate ('destroy') all the nodes in the map, including its key-value pairs elements
 *          (if an 'pair_destroy' callback function is provided), making the map empty.
 * \param   map           the map whose nodes are to be destroyed
 * \param   pair_destroy  a pointer to the callback func. which deallocates all the map key-value
 *                        pairs
 * \return  the return code for the deallocation operation
 */
map_rc_e map_clear(map_s *map, void (*pair_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the map and the map itself
 * \param   map           pointer to the map to be 'destroyed'
 * \param   pair_destroy  a pointer to a callback func. which deallocates all the map key-value
 *                        pairs
 * \return  the return code for the 'destroy' operation
 */
map_rc_e map_destroy(map_s **map, void (*pair_destroy)(void **));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MAP_H */
