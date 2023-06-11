/**
 * \file   array-node.h
 * \brief  Array node - struct. and type definitions and func. declarations
 */
#ifndef LIBDATASTRUCTURES_ARRAY_NODE_H
#define LIBDATASTRUCTURES_ARRAY_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/** Array node structure */
struct array_node {
    /** Pointer to the element stored in the node */
    void *elem;
};

/** Array node structure type */
typedef struct array_node array_node_s;

/* ************************************************************************************************/

/**
 * \brief   Create and initialize an array node.
 * \param   elem  the element to be stored on the node
 * \return  the pointer to the allocated node
 */
array_node_s *array_node_new(void *elem);

/**
 * \brief   "Destroy" (deallocate) an array node.
 * \param   node  pointer to the var. storing the node to be destroyed
 * \return  the element stored on the node; it's the user's responsibility to deallocate it
 */
void *array_node_destroy(array_node_s **node);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_ARRAY_NODE_H */
