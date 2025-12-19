#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>



#define NUM_ZERO (0.0)
#define NUM_ONE (1.0)
#define NUM_TWO (2.0)
#define START_CAPACITY_ARR_VARIABLES 3
#define START_CAPACITY_NAME_VAR 3

#define ColorizePtrAndPtrParentNode(tree, node)                      \
        if (node == tree->fict_node)                                 \
            fprintf(file_tree_dump, " bgcolor = \"#ffffffff\"");   \
        else if (node->type_node == TYPE_OP)                         \
            fprintf(file_tree_dump, " bgcolor = \"#8ff397ff\"");   \
        else if (node->type_node == TYPE_VAR)                        \
            fprintf(file_tree_dump, " bgcolor = \"#ff6a97ff\"");   \
        else if (node->type_node == TYPE_NUM)                        \
            fprintf(file_tree_dump, " bgcolor = \"#FFEDAB\"");     \
        else if (node->type_node == TYPE_FUNC)                       \
            fprintf(file_tree_dump, " bgcolor = \"#e18ff3ff\"");
        
#define ColorizeSonNode(node)                                        \
        if (node->type_node == TYPE_OP)                              \
            fprintf(file_tree_dump, " bgcolor = \"#8ff397ff\"");   \
        else if (node->type_node == TYPE_VAR)                        \
            fprintf(file_tree_dump, " bgcolor = \"#ff6a97ff\"");   \
        else if (node->type_node == TYPE_NUM)                        \
            fprintf(file_tree_dump, " bgcolor = \"#FFEDAB\"");     \
        else if (node->type_node == TYPE_FUNC)                       \
            fprintf(file_tree_dump, " bgcolor = \"#e18ff3ff\"");



enum val_flag_change {
    IT_HAS_NOT_BEEN_CHANGED = 0,
    IT_HAS_BEEN_CHANGED = 1

};

enum errors {
    SUCCESS = 0,
    OPEN_FILE_ERR = 1,
    CLOSE_FILE_ERR = 2,
    MEMORY_ERR = 3

};

enum type_nodes {
    TYPE_OP = 0,
    TYPE_VAR = 1,
    TYPE_NUM = 2,
    TYPE_FUNC = 3,
    TYPE_FICT = 4

};

enum values_type_op {
    NOT_OP = -1,
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
    POW = 4

};

enum values_type_func {
    NOT_FUNC = -1,
    SQRT = 0,
    SIN = 1,
    COS = 2,
    TAN = 3,
    ASIN = 4,
    ACOS = 5,
    ATAN = 6,
    SINH = 7,
    COSH = 8,
    TANH = 9,
    EXP = 10,
    LN = 11,
    LG = 12,

};



typedef struct {
    char * name_var;
    double value_var;

} Variable_t;

typedef struct node_t {
    node_t * parent;
    enum type_nodes type_node;
    union {
        enum values_type_op val_op;
        Variable_t struct_var;
        double val_num;
        enum values_type_func val_func;

    } val;
    node_t * left;
    node_t * right;

} Node_t;

typedef struct {
    Node_t * fict_node;

} Tree_t;



Tree_t * InitTree();
    Tree_t * AllocateMemoryForTree();

void DestroyTree(Tree_t * tree);
    void DeleteSubTree(Node_t * node);
        bool ExistLeftNode(Node_t * node);
        bool ExistRightNode(Node_t * node);
        void DetachParent(Node_t * node);

Node_t * CreateNode(Node_t * parent, Node_t * left_node, Node_t * right_node, enum type_nodes type_node, ...);
    Node_t * AllocateMemoryForNode();
    void InitValNode(Node_t * node, enum type_nodes type_node, va_list val_node);

Node_t * ParentSons(Node_t * node);