/**
 * \file   pair.h
 * \brief  Key-value Pair - structure, type and functions
 */
#ifndef LIBDATASTRUCTURES_PAIR_H
#define LIBDATASTRUCTURES_PAIR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Pair structure *********************************************************************************/

/** Pair structure definition */
struct pair {
    /** The key of the pair; must be unique */
    void *key;
    /** The value (element) of the pair, to be referenced by its key */
    void *value;
};

/** Pair type */
typedef struct pair pair_s;

/* Pair functions *********************************************************************************/

/**
 * \brief   Create and initialize a new pair with a key and a value.
 * \param   key    The key of the pair
 * \param   value  The value of the pair
 * \return  a pointer to the allocated pair
 */
pair_s *pair_new(void *key, void *value);

/**
 * \brief  Deallocate ('destroy') a pair element as well as its key and value.
 * \param  pair           pointer to the pair to be destroyed
 * \param  key_destroy    a pointer to a callback function which deallocates the key
 * \param  value_destroy  a pointer to a callback function which deallocates the value
 */
void pair_destroy(pair_s **pair, void (*key_destroy)(void **), void (*value_destroy)(void **));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_PAIR_H */
