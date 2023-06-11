/**
 * \file   tree-node.h
 * \brief  AVL tree node - struct. and types definitions and functions declarations
 */
#ifndef LIBDATASTRUCTURES_TREE_NODE_H
#define LIBDATASTRUCTURES_TREE_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* Tree node **************************************************************************************/

struct tree_node;

/** Tree node type */
typedef struct tree_node tree_node_s;

/** Tree node structure definition */
struct tree_node {
    /** The pointer to the element to be stored on the node */
    void *elem;
    /** The node's balance factor between its right and left subtrees */
    int balance_factor;
    /** The node's height */
    int height;
    /** Pointer to the left child node */
    tree_node_s *left;
    /** Pointer to the right child node */
    tree_node_s *right;
};

/* Tree node functions ****************************************************************************/

/**
 * \brief   Create and initialize a tree node with an element.
 * \param   elem  The element to be stored in the tree node
 * \return  a pointer to the allocated tree node
 */
tree_node_s *tree_node_new(void *elem);

/**
 * \brief   Find a tree node containing an element 'equal' to the one passed in the argument.
 * \param   root          the root tree node where the search will start from
 * \param   elem          a "model" element to be compared with the every other one in the tree
 * \param   elem_compare  a non-null element comparator callback function. It should return 0
 *                        if the current node element is "equal" (or if matches a certain criteria)
 *                        to the given "model" element; > 0 if the "model" element is 'greater'
 *                        than the current element; or < 0 otherwise
 * \return  pointer to the tree node which contains the found element
 */
tree_node_s *tree_node_find(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief   Find an element of a tree node wich is 'equal' to the one passed in the argument.
 * \param   root          the root tree node where the search will start from
 * \param   elem          a "model" element to be compared with the every other one in the tree
 * \param   elem_compare  a non-null element comparator callback function. It should return 0
 *                        if the current node element is "equal" (or if matches a certain criteria)
 *                        to the given "model" element; > 0 if the "model" element is 'greater'
 *                        than the current element; or < 0 otherwise
 * \return  pointer to the found element (or NULL if the element wasn't found)
 */
void *tree_node_find_elem(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief   Insert an element onto the tree, given its root node.
 * \param   root              the root node of the tree
 * \param   elem              the element to be inserted
 * \param   elem_compare      an element comparing callback function, used to take the decision
 *                            where the element should be placed (whether at the right or left of
 *                            current elem.); must return 0 if both are 'equal', > 0 if the second
 *                            elem. is 'greater' than the first one, or < 0 if the second elem. is
 *                            'lesser' than the first one
 * \param   allow_duplicates  flag to indicate it should allow insertion of duplicated elements
 * \return  the new node inserted
 */
tree_node_s *tree_node_insert(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *),
                              bool allow_duplicates);

/**
 * \brief   Traverse all the elements in the tree in a pre-order fashion, starting from its root
 *          node, applying the 'elem_visit' callback function to all its elements.
 * \param   root        pointer to the root node of the tree where the traversal will start from
 * \param   elem_visit  pointer to a callback function to be applied to all elements in the tree
 */
void tree_node_traverse_preorder(tree_node_s *root, void (*elem_visit)(void *));

/**
 * \brief  Traverse all the elements in the tree in a in-order fashion, starting from its root
 *         node, applying the 'elem_visit' callback function to all its elements.
 * \param  root        pointer to the root node of the tree where the traversal will start from
 * \param  elem_visit  pointer to a callback function to be applied to all elements in the tree
 */
void tree_node_traverse_inorder(tree_node_s *root, void (*elem_visit)(void *));

/**
 * \brief  Traverse all the elements in the tree in a post-order fashion, starting from its root
 *         node, applying the 'elem_visit' callback function to all its elements.
 * \param  root        pointer to the root node of the tree where the traversal will start from
 * \param  elem_visit  pointer to a callback function to be applied to all elements in the tree
 */
void tree_node_traverse_postorder(tree_node_s *root, void (*elem_visit)(void *));

/**
 * \brief   Remove an element from the tree.
 * \param   root          the root node of the tree
 * \param   elem          a 'model' element to be compared to all the others in the tree
 * \param   elem_compare  an element comparing callback function; must return 0 if both are 'equal',
 *                        > 0 if the second elem. is 'greater' than the first one, or < 0 if the
 *                        second elem. is 'lesser' than the first one
 * \return  the 'successor' node that will replace the one where the element was removed
 */
tree_node_s *tree_node_remove(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief  Deallocate ('destroy') all the nodes in the tree.
 * \param  root          the root node of the tree to be destroyed
 * \param  elem_destroy  a pointer to a callback function which deallocates all the tree elements
 */
void tree_node_destroy(tree_node_s **root, void (*elem_destroy)(void **));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_TREE_NODE_H */
