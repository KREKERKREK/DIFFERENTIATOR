#include "expression_tree_base.h"



Tree_t * InitTree() {
    Tree_t * new_tree = AllocateMemoryForTree();
    if (!new_tree) return NULL;

    new_tree->fict_node = CreateNode(NULL, NULL, NULL, TYPE_FICT, 0.0);
    if (new_tree->fict_node == NULL) {
        free(new_tree);
        return NULL;

    }

    return new_tree;

}



Tree_t * AllocateMemoryForTree() {
    return (Tree_t *) calloc(1, sizeof(Tree_t));

}



void DestroyTree(Tree_t * tree) {
    if (!tree) return;

    DeleteSubTree(tree->fict_node);
    free(tree);

}



Node_t * CreateNode(Node_t * parent, Node_t * left_node, Node_t * right_node, enum type_nodes type_node, ...) {
    Node_t * node = AllocateMemoryForNode();
    if (!node) return NULL;

    node->parent = parent;
    node->type_node = type_node;

    va_list val_node;
    va_start(val_node, type_node);
    InitValNode(node, type_node, val_node);
    va_end(val_node);

    node->left = left_node;
    node->right = right_node;

    return node;

}



Node_t * AllocateMemoryForNode() {
    return (Node_t *) calloc(1, sizeof(Node_t));

}



void InitValNode(Node_t * node, enum type_nodes type_node, va_list val_node) {
    assert(node);

    switch (type_node) {
        case TYPE_OP:
            node->val.val_op = va_arg(val_node, enum values_type_op);
            break;

        case TYPE_VAR:
            node->val.struct_var.name_var = va_arg(val_node, char *);
            break;

        case TYPE_NUM:
            node->val.val_num = va_arg(val_node, double);
            break;
            
        case TYPE_FUNC:
            node->val.val_func = va_arg(val_node, enum values_type_func);
            break;

        case TYPE_FICT:
            node->val.val_num = NUM_ZERO;
            break;

        default:
            break;

    }

}



Node_t * ParentSons(Node_t * node) {
    if (!node) return NULL;

    if (node->left) {
        ParentSons(node->left);
        node->left->parent = node;

    }

    if (node->right) {
        ParentSons(node->right);
        node->right->parent = node;
    
    }
    
    return node;

}



void DeleteSubTree(Node_t * node) {
    if (!node) return;

    if (ExistLeftNode(node) == true)
        DeleteSubTree(node->left);
    if (ExistRightNode(node) == true)
        DeleteSubTree(node->right);

    DetachParent(node);
    free(node);

}



bool ExistLeftNode(Node_t * node) {
    assert(node != NULL);

    if (node->left != NULL)
        return true;
    else
        return false;

}



bool ExistRightNode(Node_t * node) {
    assert(node != NULL);

    if (node->right != NULL)
        return true;
    else
        return false;

}



void DetachParent(Node_t * node) {
    assert(node != NULL);

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = NULL;

        if (node->parent->right == node)
            node->parent->right = NULL;

    }

}