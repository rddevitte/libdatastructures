/**
 * \file   tree.h
 * \brief  AVL Tree - structure, types and functions
 */
#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include "tree-node.h"

/* Tree structure *********************************************************************************/

/** Tree structure definition */
struct tree {
    /** Pointer to the root node */
    tree_node_s *root;
    /** Boolean indicating whether the tree should allow insertion of duplicated elements */
    bool allow_duplicates;
    /** Number of elements currently stored on the tree */
    size_t count;
};

/** Tree structure type */
typedef struct tree tree_s;

/** Tree operations return codes */
enum tree_rc {
    /** No error */
    TREE_RC_OK = 0,
    /** Tree is null */
    TREE_RC_NULL = -1,
    /** Tree is empty (contains no elements) */
    TREE_RC_EMPTY = -2,
    /** Tree element to be inserted is null */
    TREE_RC_ELEM_NULL = -3,
    /** Tree element is duplicated (it already exists on the tree) */
    TREE_RC_ELEM_DUPL = -4,
    /** The callback function to operate on the tree element is null */
    TREE_RC_ELEM_CB_NULL = -5,
};

/** Tree operations return codes type */
typedef enum tree_rc tree_rc_e;

/** Tree traversal orders */
enum tree_traversal {
    /** Pre-order tree traversal */
    TREE_TRAVERSAL_PREORDER,
    /** In-order tree traversal */
    TREE_TRAVERSAL_INORDER,
    /** Post-order tree traversal */
    TREE_TRAVERSAL_POSTORDER
};

/** Tree traversal type */
typedef enum tree_traversal tree_traversal_e;

/* Tree functions (operations) ********************************************************************/

/**
 * \brief   Initialize a tree.
 * \param   tree              pointer to the tree to be initialized.
 * \param   allow_duplicates  flag to indicate it should allow insertion of duplicated elements
 */
void tree_init(tree_s *tree, bool allow_duplicates);

/**
 * \brief   Create and initialize a tree.
 * \param   allow_duplicates  flag to indicate it should allow insertion of duplicated elements
 * \return  a pointer to the allocated tree
 */
tree_s *tree_new(bool allow_duplicates);

/**
 * \brief   Search an element within the tree that matches a certain criteria.
 * \param   tree          the tree where the search will take place
 * \param   elem          a 'model' element to be compared to all the others in the tree
 * \param   elem_compare  an element comparing callback function; must return 0 if both are 'equal',
 *                        > 0 if the second elem. is 'greater' than the first one, or < 0 if the
 *                        second elem. is 'lesser' than the first one
 * \return  pointer to the first element found in the tree; NULL if the elem. wasn't found
 */
void *tree_find(tree_s *tree, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief   Insert an element onto the tree.
 * \param   tree          the tree whose element is to be inserted onto
 * \param   elem          the element to be inserted
 * \param   elem_compare  an element comparing callback function, used to take the decision where
 *                        the element should be placed (whether at the right or left of the current
 *                        elem.); must return 0 if both are 'equal', > 0 if the second elem. is
 *                        'greater' than the first one, or < 0 if the second elem. is 'lesser' than
 *                        the first one
 * \return  the return code for the insert operation
 */
tree_rc_e tree_insert(tree_s *tree, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief   Traverse all the elements in the tree by a giving traversal order, applying the
 *          'elem_visit' callback function to all its elements.
 * \param   tree        the tree to be traversed by
 * \param   order       the tree traversal order (inorder, preorder or postorder)
 * \param   elem_visit  pointer to a callback function to be applied to all elements in the tree
 * \return  the return code for the traversal operation
 */
tree_rc_e tree_traverse(tree_s *tree, tree_traversal_e order, void (*elem_visit)(void *));

/**
 * \brief   Remove an element from the tree.
 * \param   tree          the tree whose element is to be removed from
 * \param   elem          a 'model' element to be compared to all the others in the tree
 * \param   elem_compare  an element comparing callback function; must return 0 if both are 'equal',
 *                        > 0 if the second elem. is 'greater' than the first one, or < 0 if the
 *                        second elem. is 'lesser' than the first one
 * \return  pointer to the element removed from the tree; NULL if the elem. wasn't found
 */
void *tree_remove(tree_s *tree, void *elem, int (*elem_compare)(void *, void *));

/**
 * \brief   Deallocate ('destroy') all the nodes in the tree, including its elements (if an
 *          'elem_destroy' callback function is provided), making the tree empty.
 * \param   tree          the tree whose nodes are to be 'destroyed'
 * \param   elem_destroy  a pointer to the callback func. which deallocates all the tree elements
 * \return  the return code for the deallocation operation
 */
tree_rc_e tree_clear(tree_s *tree, void (*elem_destroy)(void **));

/**
 * \brief   Deallocate ('destroy') all the nodes in the tree and the tree itself.
 * \param   tree          pointer to the tree to be 'destroyed'
 * \param   elem_destroy  a pointer to a callback function which deallocates all the tree elements
 * \return  the return code for the 'destroy' operation
 */
tree_rc_e tree_destroy(tree_s **tree, void (*elem_destroy)(void **));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TREE_H */
