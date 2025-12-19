#include "expression_tree_base.h"



#pragma once



void OptimizingSubTree(Node_t * node);
    void OptimizingOp(Node_t * node, enum val_flag_change * flag);
        void ValueFlag(enum val_flag_change * flag, enum val_flag_change value);
        enum val_flag_change OptimizingMUL(Node_t * node);
        enum val_flag_change OptimizingDIV(Node_t * node);
        enum val_flag_change OptimizingADD(Node_t * node);
        enum val_flag_change OptimizingSUB(Node_t * node);
        enum val_flag_change OptimizingPOW(Node_t * node);
    void OptimizingFunc(Node_t * node, enum val_flag_change * flag);
        enum val_flag_change OptimizingSQRT(Node_t * node);
        enum val_flag_change OptimizingSIN(Node_t * node);
        enum val_flag_change OptimizingCOS(Node_t * node);
        enum val_flag_change OptimizingTAN(Node_t * node);
        enum val_flag_change OptimizingASIN(Node_t * node);
        enum val_flag_change OptimizingACOS(Node_t * node);
        enum val_flag_change OptimizingATAN(Node_t * node);
        enum val_flag_change OptimizingSINH(Node_t * node);
        enum val_flag_change OptimizingCOSH(Node_t * node);
        enum val_flag_change OptimizingTANH(Node_t * node);
        enum val_flag_change OptimizingEXP(Node_t * node);
        enum val_flag_change OptimizingLN(Node_t * node);
        enum val_flag_change OptimizingLG(Node_t * node);
    bool IsZero(Node_t * node);
    bool IsOne(Node_t * node);
    bool IsNUM(Node_t * node);
    bool IsDIV(Node_t * node);
    extern bool IsMUL(Node_t * node);
    extern bool IsPOW(Node_t * node);
    void ExchangeOfSons(Node_t * first_son, Node_t * second_son);
        void ChangeSonOfParent(Node_t * SonIsNow, Node_t * NextSon);
    void ChangeValNode(Node_t * to_node, Node_t * from_node);
    bool SimilarSubTree(Node_t * first_node, Node_t * second_node);
        bool CheckingForNULL(Node_t * first_node, Node_t * second_node);
        bool SimilarSubTreeOP(Node_t * first_node, Node_t * second_node);
        bool SimilarSubTreeVAR(Node_t * first_node, Node_t * second_node);
        bool SimilarSubTreeNUM(Node_t * first_node, Node_t * second_node);
            bool NumbersAreEqual(double num1, double num2);
        bool SimilarSubTreeFUNC(Node_t * first_node, Node_t * second_node);
        bool SimilarSubTreeFICT(Node_t * first_node, Node_t * second_node);