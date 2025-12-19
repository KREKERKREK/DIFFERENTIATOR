#include "differentiator.h"



Tree_t * BuildTreeDiff(Tree_t * tree, const char * diff_var) {
    assert(tree);
    assert(diff_var);

    Tree_t * tree_diff = InitTree();
    if (!tree_diff) return NULL;

    tree_diff->fict_node->right = CalcDiff(tree->fict_node, diff_var);
    if (!(tree_diff->fict_node->right)) {
        DestroyTree(tree_diff);
        return NULL;

    }

    ParentSons(tree_diff->fict_node);
    return tree_diff;

}



Node_t * CalcDiff(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    switch (node->type_node) {
        case TYPE_OP:
            return CalcDiffTypeOp(node, diff_var);
        
        case TYPE_VAR:
            return CalcDiffTypeVar(node, diff_var);
        
        case TYPE_NUM:
            return CalcDiffTypeNum();
        
        case TYPE_FUNC:
            return CalcDiffTypeFunc(node, diff_var);
        
        case TYPE_FICT:
            return CalcDiffTypeFict(node, diff_var);
        
        default:
            assert(0);
            break;

    }

}



Node_t * CalcDiffTypeOp(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    switch (node->val.val_op) {
        case ADD:
            return CalcDiffADD(node, diff_var);
        
        case SUB:
            return CalcDiffSUB(node, diff_var);
        
        case MUL:
            return CalcDiffMUL(node, diff_var);
        
        case DIV:
            return CalcDiffDIV(node, diff_var);
        
        case POW:
            return CalcDiffPOW(node, diff_var);
            
        case NOT_OP:
        default:
            assert(0);
            break;

    }

}



Node_t * CalcDiffADD(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(L, diff_var),
                D(R, diff_var),
            TYPE_OP, ADD);

}



Node_t * CalcDiffSUB(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(L, diff_var),
                D(R, diff_var),
            TYPE_OP, SUB);

}



Node_t * CalcDiffMUL(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                CreateNode(NULL,
                    D(L, diff_var),
                    C(R),
                TYPE_OP, MUL),
                CreateNode(NULL,
                    C(L),
                    D(R, diff_var),
                TYPE_OP, MUL),
            TYPE_OP, ADD);
    
}



Node_t * CalcDiffDIV(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                CreateNode(NULL,
                    CreateNode(NULL,
                        D(L, diff_var),
                        C(R),
                    TYPE_OP, MUL),
                    CreateNode(NULL,
                        C(L),
                        D(R, diff_var),
                    TYPE_OP, MUL),
                TYPE_OP, SUB),
                CreateNode(NULL,
                    C(R),
                    C(R),
                TYPE_OP, MUL),
            TYPE_OP, DIV);

}



Node_t * CalcDiffPOW(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    Node_t * time_node_for_diff = CreateNode(NULL,
                                    CreateNode(NULL,
                                        NULL,
                                        C(L),
                                    TYPE_FUNC, LN),
                                    C(R),
                                TYPE_OP, MUL);

    Node_t * new_node = CreateNode(NULL,
                            D(time_node_for_diff, diff_var),
                            C(node),
                        TYPE_OP, MUL);

    DeleteSubTree(time_node_for_diff);
    return new_node;

}



Node_t * CopyNode(Node_t * node) {
    if (!node) return NULL;

    Node_t * new_node = CopyTypeAndVal(node);
    if (!new_node) return NULL;

    new_node->left = C(L);
    new_node->right = C(R);

    return new_node;

}



Node_t * CopyTypeAndVal(Node_t * node) {
    assert(node);

    switch (node->type_node) {
        case TYPE_OP:
            return CreateNode(NULL, NULL, NULL, TYPE_OP, node->val.val_op);
        
        case TYPE_VAR:
            return CreateNode(NULL, NULL, NULL, TYPE_VAR, node->val.struct_var.name_var);
        
        case TYPE_NUM:
            return CreateNode(NULL, NULL, NULL, TYPE_NUM, node->val.val_num);
        
        case TYPE_FUNC:
            return CreateNode(NULL, NULL, NULL, TYPE_FUNC, node->val.val_func);
        
        case TYPE_FICT:
            return CreateNode(NULL, NULL, NULL, TYPE_FICT, node->val.val_num);
        
        default:
            assert(0);
            break;

    }

}



Node_t * CalcDiffTypeVar(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    if (strcmp(node->val.struct_var.name_var, diff_var) == false)
        return CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE);
    else
        return CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ZERO);

}



Node_t * CalcDiffTypeNum() {
    return CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ZERO);

}



Node_t * CalcDiffTypeFunc(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);
    
    switch (node->val.val_func) {
        case SQRT:
            return CalcDiffSQRT(node, diff_var);
        
        case SIN:
            return CalcDiffSIN(node, diff_var);
        
        case COS:
            return CalcDiffCOS(node, diff_var);
        
        case TAN:
            return CalcDiffTAN(node, diff_var);
        
        case ASIN:
            return CalcDiffASIN(node, diff_var);
        
        case ACOS:
            return CalcDiffACOS(node, diff_var);
        
        case ATAN:
            return CalcDiffATAN(node, diff_var);
        
        case SINH:
            return CalcDiffSINH(node, diff_var);
        
        case COSH:
            return CalcDiffCOSH(node, diff_var);
        
        case TANH:
            return CalcDiffTANH(node, diff_var);
        
        case EXP:
            return CalcDiffEXP(node, diff_var);
        
        case LN:
            return CalcDiffLN(node, diff_var);
        
        case LG:
            return CalcDiffLG(node, diff_var);

        case NOT_FUNC:
        default:
            assert(0);

    }

}



Node_t * CalcDiffSQRT(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);
    
    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_TWO),
                    CreateNode(NULL,
                        NULL,
                        C(R),
                    TYPE_FUNC, SQRT),
                TYPE_OP, MUL),
            TYPE_OP, DIV);

}



Node_t * CalcDiffSIN(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    NULL,
                    C(R),
                TYPE_FUNC, COS),
            TYPE_OP, MUL);

}



Node_t * CalcDiffCOS(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                CreateNode(NULL,
                    CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ZERO),
                    D(R, diff_var),
                TYPE_OP, SUB),
                CreateNode(NULL,
                    NULL,
                    C(R),
                TYPE_FUNC, SIN),
            TYPE_OP, MUL);

}



Node_t * CalcDiffTAN(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    CreateNode(NULL,
                        NULL,
                        C(R),
                    TYPE_FUNC, COS),
                    CreateNode(NULL,
                        NULL,
                        C(R),
                    TYPE_FUNC, COS),
                TYPE_OP, MUL),
            TYPE_OP, DIV);

}



Node_t * CalcDiffASIN(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    NULL,
                    CreateNode(NULL,
                        CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                        CreateNode(NULL,
                            C(R),
                            C(R),
                        TYPE_OP, MUL),
                    TYPE_OP, SUB),
                TYPE_FUNC, SQRT),
            TYPE_OP, DIV);

}



Node_t * CalcDiffACOS(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ZERO),
                CreateNode(NULL,
                    D(R, diff_var),
                    CreateNode(NULL,
                        NULL,
                        CreateNode(NULL,
                            CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                            CreateNode(NULL,
                                C(R),
                                C(R),
                            TYPE_OP, MUL),
                        TYPE_OP, SUB),
                    TYPE_FUNC, SQRT),
                TYPE_OP, DIV),
            TYPE_OP, SUB);

}



Node_t * CalcDiffATAN(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                    CreateNode(NULL,
                        C(R),
                        C(R),
                    TYPE_OP, MUL),
                TYPE_OP, ADD),
            TYPE_OP, DIV);

}



Node_t * CalcDiffSINH(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    NULL,
                    C(R),
                TYPE_FUNC, COSH),
            TYPE_OP, MUL);

}



Node_t * CalcDiffCOSH(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    NULL,
                    C(R),
                TYPE_FUNC, SINH),
            TYPE_OP, MUL);

}



Node_t * CalcDiffTANH(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    CreateNode(NULL,
                        NULL,
                        C(R),
                    TYPE_FUNC, COSH),
                    CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_TWO),
                TYPE_OP, POW),
            TYPE_OP, DIV);

}



Node_t * CalcDiffEXP(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                C(node),
            TYPE_OP, MUL);

}



Node_t * CalcDiffLN(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                C(R),
            TYPE_OP, DIV);

}



Node_t * CalcDiffLG(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return CreateNode(NULL,
                D(R, diff_var),
                CreateNode(NULL,
                    C(R),
                    CreateNode(NULL, NULL, NULL, TYPE_NUM, log(10)),
                TYPE_OP, MUL),
            TYPE_OP, DIV);

}



Node_t * CalcDiffTypeFict(Node_t * node, const char * diff_var) {
    assert(node);
    assert(diff_var);

    return D(R, diff_var);

}