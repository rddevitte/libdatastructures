/**
 * \file   singly-linked-list-node.h
 * \brief  Circ. singly linked list node - struct. and type definitions and func. declarations
 */
#ifndef LIBDATASTRUCTURES_SINGLY_LINKED_LIST_NODE_H
#define LIBDATASTRUCTURES_SINGLY_LINKED_LIST_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/** Forward declaration of singly linked list node structure */
struct singly_linked_list_node;

/** Singly linked list node type */
typedef struct singly_linked_list_node s_l_list_node_s;

/** Singly linked list node structure */
struct singly_linked_list_node {
    /** Pointer to the element stored in the node */
    void *elem;
    /** Pointer to the next node in the list, or to itself if it's single */
    s_l_list_node_s *next;
};

/* ************************************************************************************************/

/**
 * \brief   Create and initialize a circ. singly linked list node.
 * \param   elem  the element to be stored on the node
 * \return  the pointer to the allocated node
 */
s_l_list_node_s *s_l_list_node_new(void *elem);

/**
 * \brief   "Destroy" (deallocate) a circ. singly linked list node.
 * \param   node  pointer to the var. storing the node to be destroyed
 * \return  the element stored on the node; it's the user's responsibility to deallocate it
 */
void *s_l_list_node_destroy(s_l_list_node_s **node);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_SINGLY_LINKED_LIST_NODE_H */
