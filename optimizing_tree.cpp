#include "optimizing_tree.h"



void  OptimizingSubTree(Node_t * node) {
    assert(node);
    
    enum val_flag_change flag_change = IT_HAS_NOT_BEEN_CHANGED;
    do {
        flag_change = IT_HAS_NOT_BEEN_CHANGED;

        if (ExistLeftNode(node) == true)
            OptimizingSubTree(node->left);
        if (ExistRightNode(node) == true)
            OptimizingSubTree(node->right);

        if (node->type_node == TYPE_OP)
            OptimizingOp(node, &flag_change);
        else if (node->type_node == TYPE_FUNC)
            OptimizingFunc(node, &flag_change);

        ParentSons(node->parent);

    } while (flag_change == IT_HAS_BEEN_CHANGED);

}



void OptimizingOp(Node_t * node, enum val_flag_change * flag) {
    assert(node);
    assert(flag);

    switch (node->val.val_op) {
        case MUL:
            ValueFlag(flag, OptimizingMUL(node));
            break;
        
        case DIV:
            ValueFlag(flag, OptimizingDIV(node));
            break;
    
        case ADD:
            ValueFlag(flag, OptimizingADD(node));
            break;

        case SUB:
            ValueFlag(flag, OptimizingSUB(node));
            break;
        
        case POW:
            ValueFlag(flag, OptimizingPOW(node));
            break;
        
        case NOT_OP:
        default:
            break;

    }

}



void ValueFlag(enum val_flag_change * flag, enum val_flag_change value) {
    assert(flag);

    if (*flag == IT_HAS_BEEN_CHANGED)
        return;
    else
        *flag = value;

}



enum val_flag_change OptimizingMUL(Node_t * node) {
    assert(node);

    if ((IsZero(node->left) == true) || (IsZero(node->right) == true)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = NUM_ZERO;
        
        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsOne(node->left) == true) {
        DeleteSubTree(node->left);

        Node_t * right_node = node->right;

        node->type_node = right_node->type_node;
        ChangeValNode(node, right_node);
        node->left = right_node->left;
        node->right = right_node->right;

        free(right_node);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsOne(node->right) == true) {
        DeleteSubTree(node->right);

        Node_t * left_node = node->left;

        node->type_node = left_node->type_node;
        ChangeValNode(node, left_node);
        node->left = left_node->left;
        node->right = left_node->right;

        free(left_node);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->left) && IsNUM(node->right)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = (node->left->val.val_num) * (node->right->val.val_num);

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsDIV(node->left) == true) {
        Node_t * node_div = node->left;

        ChangeSonOfParent(node, node_div);
        node->left = node_div->left;
        node_div->left = node;
        return IT_HAS_BEEN_CHANGED;

    } else if (IsDIV(node->right) == true) {
        Node_t * node_div = node->right;

        ChangeSonOfParent(node, node_div);
        node->right = node_div->left;
        node_div->left = node;
        return IT_HAS_BEEN_CHANGED;

    } else if (IsMUL(node->left) && IsNUM(node->right) && IsNUM(node->left->left)) {
        ExchangeOfSons(node->right, node->left->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsMUL(node->left) && IsNUM(node->right) && IsNUM(node->left->right)) {
        ExchangeOfSons(node->right, node->left->left);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsMUL(node->right) && IsNUM(node->left) && IsNUM(node->right->left)) {
        ExchangeOfSons(node->left, node->right->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsMUL(node->right) && IsNUM(node->left) && IsNUM(node->right->right)) {
        ExchangeOfSons(node->left, node->right->left);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->right) == true) {
        Node_t * time_node = node->left;

        node->left = node->right;
        node->right = time_node;
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



void ExchangeOfSons(Node_t * first_son, Node_t * second_son) {
    assert(first_son);
    assert(second_son);
    
    ChangeSonOfParent(first_son, second_son);
    ChangeSonOfParent(second_son, first_son);

}



void ChangeSonOfParent(Node_t * SonIsNow, Node_t * NextSon) {
    assert(SonIsNow);
    assert(NextSon);
    
    if (SonIsNow->parent->left == SonIsNow)
        SonIsNow->parent->left = NextSon;
    else if (SonIsNow->parent->right == SonIsNow)
        SonIsNow->parent->right = NextSon;
    else
        assert(0);

}



bool IsDIV(Node_t * node) {
    assert(node);

    if (node->type_node == TYPE_OP) {
        if (node->val.val_op == DIV)
            return true;

    }

    return false;

}



enum val_flag_change OptimizingDIV(Node_t * node) {
    assert(node);

    if (IsZero(node->left) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = NUM_ZERO;

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsOne(node->right) == true) {
        Node_t * numerator_of_fraction = node->left;

        node->type_node = numerator_of_fraction->type_node;
        ChangeValNode(node, numerator_of_fraction);
        node->left = numerator_of_fraction->left;
        node->right = numerator_of_fraction->right;

        free(numerator_of_fraction);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->left) && IsNUM(node->right)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = (node->left->val.val_num) / (node->right->val.val_num);

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsPOW(node->left) == true) {
        if (SimilarSubTree(node->right, node->left->left) == true) {
            node->right->type_node = TYPE_NUM;
            node->right->val.val_num = NUM_ONE;

            Node_t * degree_node = CreateNode(NULL,
                                        node->left->right,
                                        CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                                    TYPE_OP, SUB);

            node->left->right = degree_node;
            return IT_HAS_BEEN_CHANGED;
            
        }

    } else if (IsMUL(node->left) == true) {
        if (IsPOW(node->left->right) == true) {
            if (SimilarSubTree(node->right, node->left->right->left) == true) {
                node->right->type_node = TYPE_NUM;
                node->right->val.val_num = NUM_ONE;

                Node_t * degree_node = CreateNode(NULL,
                                            node->left->right->right,
                                            CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                                        TYPE_OP, SUB);

                node->left->right->right = degree_node;
                return IT_HAS_BEEN_CHANGED;
            
            }
                
        } else if (IsPOW(node->left->left) == true) {
            if (SimilarSubTree(node->right, node->left->left->left) == true) {
                node->right->type_node = TYPE_NUM;
                node->right->val.val_num = NUM_ONE;

                Node_t * degree_node = CreateNode(NULL,
                                            node->left->left->right,
                                            CreateNode(NULL, NULL, NULL, TYPE_NUM, NUM_ONE),
                                        TYPE_OP, SUB);

                node->left->left->right = degree_node;
                return IT_HAS_BEEN_CHANGED;
            
            }
                
        } else if (SimilarSubTree(node->right, node->left->left) == true) {
            node->right->type_node = TYPE_NUM;
            node->right->val.val_num = NUM_ONE;

            node->left->left->type_node = TYPE_NUM;
            node->left->left->val.val_num = NUM_ONE;
            return IT_HAS_BEEN_CHANGED;
        
        } else if (SimilarSubTree(node->right, node->left->right) == true) {
            node->right->type_node = TYPE_NUM;
            node->right->val.val_num = NUM_ONE;

            node->left->right->type_node = TYPE_NUM;
            node->left->right->val.val_num = NUM_ONE;
            return IT_HAS_BEEN_CHANGED;
        
        }

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



bool SimilarSubTree(Node_t * first_node, Node_t * second_node) {
    if (!first_node || !second_node)
        return CheckingForNULL(first_node, second_node);

    switch (first_node->type_node) {
        case TYPE_OP:
            return SimilarSubTreeOP(first_node, second_node);
        
        case TYPE_VAR:
            return SimilarSubTreeVAR(first_node, second_node);
        
        case TYPE_NUM:
            return SimilarSubTreeNUM(first_node, second_node);
        
        case TYPE_FUNC:
            return SimilarSubTreeFUNC(first_node, second_node);
        
        case TYPE_FICT:
            return SimilarSubTreeFICT(first_node, second_node);
            
        default:
            break;

    }

}



bool CheckingForNULL(Node_t * first_node, Node_t * second_node) {
    if ((!first_node && second_node) || (first_node && !second_node))
        return false;

    if (!first_node && !second_node)
        return true;
    
    assert(0);

}



bool SimilarSubTreeOP(Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    if (second_node->type_node != TYPE_OP)
        return false;

    if (first_node->val.val_op == second_node->val.val_op) {
        bool left_result = SimilarSubTree(first_node->left, second_node->left);
        bool right_result = SimilarSubTree(first_node->right, second_node->right);

        if ((left_result == true) && (right_result == true))
            return true;

    }

    return false;

}



bool SimilarSubTreeVAR(Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    if (second_node->type_node != TYPE_VAR)
        return false;

    if (strcmp(first_node->val.struct_var.name_var, second_node->val.struct_var.name_var) == false)
        return true;

    return false;

}



bool SimilarSubTreeNUM(Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    if (second_node->type_node != TYPE_NUM)
        return false;

    if (NumbersAreEqual(first_node->val.val_num, second_node->val.val_num) == true)
        return true;

    return false;

}



bool NumbersAreEqual(double num1, double num2) {
    double epsilon = 1e-12;
    if (fabs(num1-num2) < epsilon)
        return true;
    else
        return false;

}



bool SimilarSubTreeFUNC(Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    if (second_node->type_node != TYPE_FUNC)
        return false;

    if (first_node->val.val_func == second_node->val.val_func)
        return SimilarSubTree(first_node->right, second_node->right);

    return false;

}



bool SimilarSubTreeFICT(Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    if (second_node->type_node != TYPE_FICT)
        return false;

    return SimilarSubTree(first_node->right, second_node->right);

}



enum val_flag_change OptimizingADD(Node_t * node) {
    assert(node);

    if (IsZero(node->left) == true) {
        DeleteSubTree(node->left);

        Node_t * right_node = node->right;

        node->type_node = right_node->type_node;
        ChangeValNode(node, right_node);
        node->left = right_node->left;
        node->right = right_node->right;

        free(right_node);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsZero(node->right) == true) {
        DeleteSubTree(node->right);

        Node_t * left_node = node->left;

        node->type_node = left_node->type_node;
        ChangeValNode(node, left_node);
        node->left = left_node->left;
        node->right = left_node->right;

        free(left_node);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->left) && IsNUM(node->right)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = (node->left->val.val_num) + (node->right->val.val_num);

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingSUB(Node_t * node) {
    assert(node != NULL);

    if (IsZero(node->right) == true) {
        DeleteSubTree(node->right);

        Node_t * left_node = node->left;

        node->type_node = left_node->type_node;
        ChangeValNode(node, left_node);
        node->left = left_node->left;
        node->right = left_node->right;

        free(left_node);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->left) && IsNUM(node->right)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = (node->left->val.val_num) - (node->right->val.val_num);

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingPOW(Node_t * node) {
    assert(node != NULL);

    if (IsZero(node->right) == true) {
        DeleteSubTree(node->left);
        DeleteSubTree(node->right);

        node->type_node = TYPE_NUM;
        node->val.val_num = NUM_ONE;
        return IT_HAS_BEEN_CHANGED;

    } else if (IsOne(node->right) == true) {
        DeleteSubTree(node->right);

        node->type_node = node->left->type_node;
        ChangeValNode(node, node->left);

        DeleteSubTree(node->left);
        return IT_HAS_BEEN_CHANGED;

    } else if (IsNUM(node->left) && IsNUM(node->right)) {
        node->type_node = TYPE_NUM;
        node->val.val_num = pow((node->left->val.val_num), (node->right->val.val_num));

        DeleteSubTree(node->left);
        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



void OptimizingFunc(Node_t * node, enum val_flag_change * flag) {
    assert(node);
    assert(flag);

    switch (node->val.val_func) {
        case SQRT:
            ValueFlag(flag, OptimizingSQRT(node));
            break;
        
        case SIN:
            ValueFlag(flag, OptimizingSIN(node));
            break;
        
        case COS:
            ValueFlag(flag, OptimizingCOS(node));
            break;
        
        case TAN:
            ValueFlag(flag, OptimizingTAN(node));
            break;
        
        case ASIN:
            ValueFlag(flag, OptimizingASIN(node));
            break;
        
        case ACOS:
            ValueFlag(flag, OptimizingACOS(node));
            break;
        
        case ATAN:
            ValueFlag(flag, OptimizingATAN(node));
            break;
        
        case SINH:
            ValueFlag(flag, OptimizingSINH(node));
            break;
        
        case COSH:
            ValueFlag(flag, OptimizingCOSH(node));
            break;
        
        case TANH:
            ValueFlag(flag, OptimizingTANH(node));
            break;
        
        case EXP:
            ValueFlag(flag, OptimizingEXP(node));
            break;
        
        case LN:
            ValueFlag(flag, OptimizingLN(node));
            break;
        
        case LG:
            ValueFlag(flag, OptimizingLG(node));
            break;

        case NOT_FUNC:
        default:
            assert(0);

    }

}



enum val_flag_change OptimizingSQRT(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = sqrt(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingSIN(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = sin(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingCOS(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = cos(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingTAN(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = tan(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingASIN(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = asin(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingACOS(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = acos(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingATAN(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = atan(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingSINH(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = sinh(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingCOSH(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = cosh(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingTANH(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = tanh(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingEXP(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = exp(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingLN(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = log(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



enum val_flag_change OptimizingLG(Node_t * node) {
    assert(node);

    if (IsNUM(node->right) == true) {
        node->type_node = TYPE_NUM;
        node->val.val_num = log10(node->right->val.val_num);

        DeleteSubTree(node->right);
        return IT_HAS_BEEN_CHANGED;

    }

    return IT_HAS_NOT_BEEN_CHANGED;

}



bool IsZero(Node_t * node) {
    assert(node != NULL);

    double epsilon = 1e-12;

    if (node->type_node == TYPE_NUM) {
        if (fabs(node->val.val_num) < epsilon)
            return true;

    }

    return false;

}



bool IsOne(Node_t * node) {
    assert(node != NULL);

    double epsilon = 1e-12;

    if (node->type_node == TYPE_NUM) {
        if ((1 - epsilon < node->val.val_num) && (node->val.val_num < 1 + epsilon))
            return true;

    }

    return false;

}



bool IsNUM(Node_t * node) {
    assert(node);

    if (node->type_node == TYPE_NUM)
        return true;
    else
        return false;

}



void ChangeValNode(Node_t * to_node, Node_t * from_node) {
    assert(to_node != NULL);
    assert(from_node != NULL);
    
    switch (from_node->type_node) {
        case TYPE_OP:
            to_node->val.val_op = from_node->val.val_op;
            break;
        
        case TYPE_VAR:
            to_node->val.struct_var = from_node->val.struct_var;
            break;
        
        case TYPE_NUM:
            to_node->val.val_num = from_node->val.val_num;
            break;
        
        case TYPE_FUNC:
            to_node->val.val_func = from_node->val.val_func;
            break;

        case TYPE_FICT:
            to_node->val.val_num = from_node->val.val_num;
            break;
        
        default:
            assert(0);
            
    }

}