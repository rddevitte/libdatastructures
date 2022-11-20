/**
 * \file   tree.c
 * \brief  AVL Tree - functions implementations
 */
#include <stdlib.h>

#include "libdatastructures/tree/tree.h"
#include "libdatastructures/tree/tree-node.h"

/* ************************************************************************************************/

void tree_init(tree_s *tree, bool allow_duplicates)
{
    if (NULL != tree) {
        tree->root = NULL;
        tree->allow_duplicates = allow_duplicates;
        tree->count = 0;
    }

    return;
}

/* ************************************************************************************************/

tree_s *tree_new(bool allow_duplicates)
{
    tree_s *tree = (tree_s *)malloc(sizeof(tree_s));

    tree_init(tree, allow_duplicates);

    return tree;
}

/* ************************************************************************************************/

void *tree_find(tree_s *tree, void *elem, int (*elem_compare)(void *, void *))
{
    if (NULL == tree || NULL == elem || NULL == elem_compare)
        return NULL;

    return tree_node_find_elem(tree->root, elem, elem_compare);
}

/* ************************************************************************************************/

tree_rc_e tree_insert(tree_s *tree, void *elem, int (*elem_compare)(void *, void *))
{
    if (NULL == tree)
        return TREE_RC_NULL;

    /* Don't allow insertion of null elements */
    if (NULL == elem)
        return TREE_RC_ELEM_NULL;

    if (NULL == elem_compare)
        return TREE_RC_ELEM_CB_NULL;

    tree_node_s *found_elem_node = tree_node_find(tree->root, elem, elem_compare);

    if (NULL != found_elem_node && !tree->allow_duplicates)
        return TREE_RC_ELEM_DUPL;

    tree->root = tree_node_insert(tree->root, elem, elem_compare, tree->allow_duplicates);
    tree->count++;

    return TREE_RC_OK;
}

/* ************************************************************************************************/

tree_rc_e tree_traverse(tree_s *tree, tree_traversal_e order, void (*elem_visit)(void *))
{
    if (NULL == tree)
        return TREE_RC_NULL;

    if (NULL == tree->root)
        return TREE_RC_EMPTY;

    if (NULL == elem_visit)
        return TREE_RC_ELEM_CB_NULL;

    if (order == TREE_TRAVERSAL_PREORDER)
        tree_node_traverse_preorder(tree->root, elem_visit);
    else if (order == TREE_TRAVERSAL_INORDER)
        tree_node_traverse_inorder(tree->root, elem_visit);
    else if (order == TREE_TRAVERSAL_POSTORDER)
        tree_node_traverse_postorder(tree->root, elem_visit);

    return TREE_RC_OK;
}

/* ************************************************************************************************/

void *tree_remove(tree_s *tree, void *elem, int (*elem_compare)(void *, void *))
{
    if (NULL == tree || NULL == tree->root || NULL == elem || NULL == elem_compare)
        return NULL;

    tree_node_s *node = tree_node_find(tree->root, elem, elem_compare);

    if (NULL == node) {
        return NULL;
    }

    void *removed = node->elem;

    tree->root = tree_node_remove(tree->root, elem, elem_compare);
    tree->count--;

    return removed;
}

/* ************************************************************************************************/

tree_rc_e tree_clear(tree_s *tree, void (*elem_destroy)(void **))
{
    if (NULL == tree)
        return TREE_RC_NULL;

    tree_rc_e rc;

    if (NULL == tree->root)
        rc = TREE_RC_EMPTY;
    else if (NULL == elem_destroy)
        rc = TREE_RC_ELEM_CB_NULL;
    else
        rc = TREE_RC_OK;

    if (rc != TREE_RC_EMPTY)
        tree_node_destroy(&tree->root, elem_destroy);

    tree->count = 0;

    return rc;
}

/* ************************************************************************************************/

tree_rc_e tree_destroy(tree_s **tree, void (*elem_destroy)(void **))
{
    if (NULL == tree)
        return TREE_RC_NULL;

    tree_rc_e rc = tree_clear(*tree, elem_destroy);

    if (rc != TREE_RC_NULL) {
        free(*tree);
        *tree = NULL;
    }

    return rc;
}
