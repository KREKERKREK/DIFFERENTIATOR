#include "expression_tree_base.h"



#define D(node, diff_var) CalcDiff(node, diff_var)
#define C(node) CopyNode(node)
#define L (node->left)
#define R (node->right)



Tree_t * BuildTreeDiff(Tree_t * tree, const char * diff_var);
    Node_t * CalcDiff(Node_t * node, const char * diff_var);
        Node_t * CalcDiffTypeOp(Node_t * node, const char * diff_var);
            Node_t * CalcDiffADD(Node_t * node, const char * diff_var);
            Node_t * CalcDiffSUB(Node_t * node, const char * diff_var);
            Node_t * CalcDiffMUL(Node_t * node, const char * diff_var);
            Node_t * CalcDiffDIV(Node_t * node, const char * diff_var);
            Node_t * CalcDiffPOW(Node_t * node, const char * diff_var);
        Node_t * ParentSons(Node_t * node);
        Node_t * CalcDiffTypeVar(Node_t * node, const char * diff_var);
        Node_t * CalcDiffTypeNum();
        Node_t * CalcDiffTypeFunc(Node_t * node, const char * diff_var);
            Node_t * CalcDiffSQRT(Node_t * node, const char * diff_var);
            Node_t * CalcDiffSIN(Node_t * node, const char * diff_var);
            Node_t * CalcDiffCOS(Node_t * node, const char * diff_var);
            Node_t * CalcDiffTAN(Node_t * node, const char * diff_var);
            Node_t * CalcDiffASIN(Node_t * node, const char * diff_var);
            Node_t * CalcDiffACOS(Node_t * node, const char * diff_var);
            Node_t * CalcDiffATAN(Node_t * node, const char * diff_var);
            Node_t * CalcDiffSINH(Node_t * node, const char * diff_var);
            Node_t * CalcDiffCOSH(Node_t * node, const char * diff_var);
            Node_t * CalcDiffTANH(Node_t * node, const char * diff_var);
            Node_t * CalcDiffEXP(Node_t * node, const char * diff_var);
            Node_t * CalcDiffLN(Node_t * node, const char * diff_var);
            Node_t * CalcDiffLG(Node_t * node, const char * diff_var);
        Node_t * CalcDiffTypeFict(Node_t * node, const char * diff_var);
        Node_t * CopyNode(Node_t * node);
            Node_t * CopyTypeAndVal(Node_t * node);