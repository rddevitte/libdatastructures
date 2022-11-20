/**
 * \file   tree-node.c
 * \brief  AVL tree node - functions definitions
 */
#include <stdlib.h>

#include "libdatastructures/tree/tree-node.h"

/* Static (helper) functions - declarations *******************************************************/

/**
 * \brief  Initialize a non-null tree node structure with a given element
 * \param  node  Pointer to a tree node struct
 * \param  elem  The element to be stored in the tree node
 */
static void tree_node_init(tree_node_s *node, void *elem);

/**
 * \brief  Update the height and the balance factor of a give node
 * \param  node  the tree node whose height and balance factor are to be updated
 */
static void tree_node_update_height_and_balance_factor(tree_node_s *node);

/**
 * \brief   Right-rotate a given subtree
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_right_rotation(tree_node_s *node);

/**
 * \brief   Left-rotate a given subtree
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_left_rotation(tree_node_s *node);

/**
 * \brief   Balance a subtree, left-left case
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_balance_left_left_case(tree_node_s *node);

/**
 * \brief   Balance a subtree, left-right case
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_balance_left_right_case(tree_node_s *node);

/**
 * \brief   Balance a subtree, right-right case
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_balance_right_right_case(tree_node_s *node);

/**
 * \brief   Balance a subtree, right-left case
 * \param   node  the current parent node to be rotated
 * \return  the new parent of the node in the subtree
 */
static tree_node_s *tree_node_balance_right_left_case(tree_node_s *node);

/**
 * \brief   Balance a subtree considering the balance factor of its root
 * \param   node  the parent (root) node of the subtree
 * \return  the new root node of the subtree, or the same if the subtree is already balanced
 */
static tree_node_s *tree_node_balance(tree_node_s *node);

/**
 * \brief   Find the rightmost ('greater') node in a subtree
 * \param   root  the root node of the subtree
 * \return  the rightmost ('greater') node found in the subtree
 */
static tree_node_s *tree_node_find_max(tree_node_s *root);

/**
 * \brief   Fid the leftmost ('lesser') node in a subtree
 * \param   root  the root node of the subtree
 * \return  the leftmost ('lesser') node found in the subtree
 */
static tree_node_s *tree_node_find_min(tree_node_s *root);

/* All other functions ****************************************************************************/

tree_node_s *tree_node_new(void *elem)
{
    if (NULL == elem)
        return NULL;

    tree_node_s *node = (tree_node_s *)malloc(sizeof(tree_node_s));

    tree_node_init(node, elem);

    return node;
}

/* ************************************************************************************************/

tree_node_s *tree_node_find(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *))
{
    if (NULL == root || NULL == elem || NULL == elem_compare)
        return NULL;

    int comp = elem_compare(root->elem, elem);

    if (comp < 0)
        return tree_node_find(root->left, elem, elem_compare);

    if (comp > 0)
        return tree_node_find(root->right, elem, elem_compare);

    return root;
}

/* ************************************************************************************************/

void *tree_node_find_elem(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *))
{
    tree_node_s *found_node = tree_node_find(root, elem, elem_compare);

    if (NULL == found_node) {
        return NULL;
    }

    return found_node->elem;
}

/* ************************************************************************************************/

tree_node_s *tree_node_insert(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *),
                              bool allow_duplicates)
{
    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return root;

    if (NULL == root) {
        return tree_node_new(elem);
    }

    if (NULL == elem_compare)
        return root;

    int comp = elem_compare(root->elem, elem);

    if (comp < 0) {
        root->left = tree_node_insert(root->left, elem, elem_compare, allow_duplicates);
    } else if (comp > 0 || allow_duplicates) {
        root->right = tree_node_insert(root->right, elem, elem_compare, allow_duplicates);
    } else { /* if (comp == 0 && !allow_duplicates) */
        return root;
    }

    tree_node_update_height_and_balance_factor(root);

    return tree_node_balance(root);
}

/* ************************************************************************************************/

void tree_node_traverse_preorder(tree_node_s *root, void (*elem_visit)(void *))
{
    if (NULL == root || NULL == elem_visit)
        return;

    elem_visit(root->elem);
    tree_node_traverse_preorder(root->left, elem_visit);
    tree_node_traverse_preorder(root->right, elem_visit);
}

/* ************************************************************************************************/

void tree_node_traverse_inorder(tree_node_s *root, void (*elem_visit)(void *))
{
    if (NULL == root || NULL == elem_visit)
        return;

    tree_node_traverse_inorder(root->left, elem_visit);
    elem_visit(root->elem);
    tree_node_traverse_inorder(root->right, elem_visit);
}

/* ************************************************************************************************/

void tree_node_traverse_postorder(tree_node_s *root, void (*elem_visit)(void *))
{

    if (NULL == root || NULL == elem_visit)
        return;

    tree_node_traverse_postorder(root->left, elem_visit);
    tree_node_traverse_postorder(root->right, elem_visit);
    elem_visit(root->elem);
}

/* ************************************************************************************************/

tree_node_s *tree_node_remove(tree_node_s *root, void *elem, int (*elem_compare)(void *, void *))
{
    if (NULL == root)
        return NULL;

    if (NULL == elem || NULL == elem_compare)
        return root;

    int comp = elem_compare(root->elem, elem);

    if (comp < 0) {
        root->left = tree_node_remove(root->left, elem, elem_compare);
    } else if (comp > 0) {
        root->right = tree_node_remove(root->right, elem, elem_compare);
    } else {
        tree_node_s *tmp;

        if (NULL == root->left && NULL == root->right) {
            free(root);
            root = NULL;
        } else if (NULL == root->right) {
            tmp = root->left;
            free(root);
            root = tmp;
        } else if (NULL == root->left) {
            tmp = root->right;
            free(root);
            root = tmp;
        } else {

            if (root->left->height > root->right->height) {
                tmp = tree_node_find_max(root->left);

                root->elem = tmp->elem;
                root->left = tree_node_remove(root->left, tmp->elem, elem_compare);
            } else {
                tmp = tree_node_find_min(root->right);

                root->elem = tmp->elem;
                root->right = tree_node_remove(root->right, tmp->elem, elem_compare);
            }
        }
    }

    tree_node_update_height_and_balance_factor(root);

    return tree_node_balance(root);
}

/* ************************************************************************************************/

void tree_node_destroy(tree_node_s **root, void (*elem_destroy)(void **))
{
    if (NULL == root || NULL == *root) {
        return;
    }

    tree_node_destroy(&(*root)->left, elem_destroy);
    tree_node_destroy(&(*root)->right, elem_destroy);

    if (NULL != elem_destroy && NULL != (*root)->elem) {
        elem_destroy(&(*root)->elem);
        (*root)->elem = NULL;
    }

    free(*root);
    *root = NULL;

    return;
}

/* Static (helper) functions - implementations ****************************************************/

static void tree_node_init(tree_node_s *node, void *elem)
{
    if (NULL != node) {
        node->elem = elem;
        node->balance_factor = 0;
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return;
}

/* ************************************************************************************************/

/** Macro for tree height calculation */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static void tree_node_update_height_and_balance_factor(tree_node_s *node)
{
    if (NULL == node)
        return;

    int left_node_height = (NULL == node->left ? -1 : node->left->height);
    int right_node_height = (NULL == node->right ? -1 : node->right->height);

    node->height = 1 + MAX(left_node_height, right_node_height);

    node->balance_factor = right_node_height - left_node_height;

    return;
}

/* ************************************************************************************************/

static tree_node_s *tree_node_right_rotation(tree_node_s *node)
{
    tree_node_s *new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    tree_node_update_height_and_balance_factor(node);
    tree_node_update_height_and_balance_factor(new_parent);

    return new_parent;
}

/* ************************************************************************************************/

static tree_node_s *tree_node_left_rotation(tree_node_s *node)
{
    tree_node_s *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    tree_node_update_height_and_balance_factor(node);
    tree_node_update_height_and_balance_factor(new_parent);

    return new_parent;
}

/* ************************************************************************************************/

static tree_node_s *tree_node_balance_left_left_case(tree_node_s *node)
{
    return tree_node_right_rotation(node);
}

/* ************************************************************************************************/

static tree_node_s *tree_node_balance_left_right_case(tree_node_s *node)
{
    node->left = tree_node_left_rotation(node->left);
    return tree_node_balance_left_left_case(node);
}

/* ************************************************************************************************/

static tree_node_s *tree_node_balance_right_right_case(tree_node_s *node)
{
    return tree_node_left_rotation(node);
}

/* ************************************************************************************************/

static tree_node_s *tree_node_balance_right_left_case(tree_node_s *node)
{
    node->right = tree_node_right_rotation(node->right);
    return tree_node_balance_right_right_case(node);
}

/* ************************************************************************************************/

static tree_node_s *tree_node_balance(tree_node_s *node)
{
    if (NULL == node)
        return NULL;

    /* Left heavy subtree */
    if (node->balance_factor == -2) {
        if (node->left->balance_factor <= 0) {
            return tree_node_balance_left_left_case(node);
        } else {
            return tree_node_balance_left_right_case(node);
        }
    }
    /* Right heavy subtree */
    else if (node->balance_factor == +2) {
        if (node->right->balance_factor >= 0) {
            return tree_node_balance_right_right_case(node);
        } else {
            return tree_node_balance_right_left_case(node);
        }
    }

    /* Node either has a balance factor of 0, +1 or -1, which is fine */
    return node;
}

/* ************************************************************************************************/

static tree_node_s *tree_node_find_max(tree_node_s *root)
{
    while (root && root->right != NULL)
        root = root->right;

    return root;
}

/* ************************************************************************************************/

static tree_node_s *tree_node_find_min(tree_node_s *root)
{
    while (root && root->left != NULL)
        root = root->left;

    return root;
}
