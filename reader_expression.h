#include <ctype.h>
#include <string.h>
#include "expression_tree_base.h"



Node_t * ReadExpression(char * str);

Node_t * GetE(char ** ip);
    Node_t * CreateAndFillNewOpNode(enum values_type_op val_op, Node_t * first_node, Node_t * second_node);

Node_t * GetT(char ** ip);

Node_t * GetJ(char ** ip);

Node_t * GetP(char ** ip);
    bool IsVariable(char symbol);

Node_t * GetF(char ** ip, char * word);
    bool IsKeyWord(char * word);
        enum values_type_func KeyWord(char * word);

Node_t * GetV(char ** ip);
    int InitNameVar(char ** name_var, size_t capacity_name_var);
    int AddSymbolToNameVar(char ** name_var, size_t * capacity_alloc_mem, size_t * size_name_var, char new_symbol);
        int IncreaseCapacityName(char ** adrs_name_var, size_t * capacity_alloc_mem);

Node_t * GetN(char ** ip);