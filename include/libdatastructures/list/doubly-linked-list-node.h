/**
 * \file   doubly-linked-list-node.h
 * \brief  Circ. doubly linked list node - struct. and type definitions and func. declarations
 */
#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/** Forward declaration of doubly linked list node structure */
struct doubly_linked_list_node;

/** Doubly linked list node type */
typedef struct doubly_linked_list_node d_l_list_node_s;

/** Doubly linked list node structure */
struct doubly_linked_list_node {
    /** Pointer to the element stored in the node */
    void *elem;
    /** Pointer to the previous node in the list, or to itself if it's single */
    d_l_list_node_s *prev;
    /** Pointer to the next node in the list, or to itself if it's single */
    d_l_list_node_s *next;
};

/* ************************************************************************************************/

/**
 * \brief   Create and initialize a circ. doubly linked list node.
 * \param   elem  the element to be stored on the node
 * \return  the pointer to the allocated node
 */
d_l_list_node_s *d_l_list_node_new(void *elem);

/**
 * \brief   "Destroy" (deallocate) a circ. doubly linked list node.
 * \param   node  pointer to the var. storing the node to be destroyed
 * \return  the element stored on the node; it's the user's responsibility to deallocate it
 */
void *d_l_list_node_destroy(d_l_list_node_s **node);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DOUBLY_LINKED_LIST_NODE_H */
