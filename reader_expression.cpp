#include "reader_expression.h"



Node_t * GetN(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    char * start_ip = *ip;
    double val = 0;
    while ('0' <= **ip && **ip <= '9') {
        val = val * 10 + (**ip - '0');
        (*ip)++;

    }
    
    if (**ip == '.') {
        (*ip)++;

        int number_of_symbol_after_dot = 0;
        while ('0' <= **ip && **ip <= '9') {
            number_of_symbol_after_dot++;
            val += ((double) (**ip - '0')) / pow(10, number_of_symbol_after_dot);

            (*ip)++;

        }

    }

    if (*ip == start_ip)
        assert(0);
    
    return CreateNode(NULL, NULL, NULL, TYPE_NUM, val);

}



Node_t * GetV(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    char * start_ip = *ip;
    char * name_var = NULL;
    size_t capacity_alloc_mem = START_CAPACITY_NAME_VAR;
    size_t size_name_var = 0;

    InitNameVar(&name_var, capacity_alloc_mem);

    while (IsVariable(**ip) == true) {
        AddSymbolToNameVar(&name_var, &capacity_alloc_mem, &size_name_var, **ip);
        (*ip)++;

    }

    if (*ip == start_ip)
        assert(0);

    *(name_var + size_name_var) = '\0';
    if (IsKeyWord(name_var) == true)
        return GetF(ip, name_var);
    
    return CreateNode(NULL, NULL, NULL, TYPE_VAR, name_var);

}



int InitNameVar(char ** name_var, size_t capacity_name_var) {
    assert(name_var != NULL);

    *name_var = (char *) calloc(capacity_name_var , sizeof(char));
    if (*name_var == NULL)
        return MEMORY_ERR;
    
    return SUCCESS;

}



int AddSymbolToNameVar(char ** name_var, size_t * capacity_alloc_mem, size_t * size_name_var, char new_symbol) {
    assert(name_var != NULL);
    assert(*name_var != NULL);
    assert(capacity_alloc_mem != NULL);
    assert(size_name_var != NULL);

    if(*size_name_var >= *capacity_alloc_mem - 1) {
        if (IncreaseCapacityName(name_var, capacity_alloc_mem) != SUCCESS)
            return MEMORY_ERR;

    }

    *(*name_var + *size_name_var) = new_symbol;
    (*size_name_var)++;

    return SUCCESS;

}



int IncreaseCapacityName(char ** adrs_name_var, size_t * capacity_alloc_mem) {
    assert(adrs_name_var != NULL);
    assert(*adrs_name_var != NULL);
    assert(capacity_alloc_mem != NULL);

    char * new_ptr_name_var = (char *) realloc(*adrs_name_var, 2 * sizeof(char) * *capacity_alloc_mem);
    if (new_ptr_name_var == NULL)
        return MEMORY_ERR;
    
    *adrs_name_var = new_ptr_name_var;
    *capacity_alloc_mem *= 2;

    return SUCCESS;

}



Node_t * GetF(char ** ip, char * word) {
    assert(ip);
    assert(*ip);
    assert(word);

    return CreateNode(NULL,
                NULL,
                GetP(ip),
            TYPE_FUNC, KeyWord(word));

}



bool IsKeyWord(char * word) {
    assert(word);

    if (KeyWord(word) == NOT_FUNC)
        return false;
    else
        return true;

}



enum values_type_func KeyWord(char * word) {
    assert(word);

    if (strcmp(word, "sqrt") == false) return SQRT;
    if (strcmp(word, "sin") == false) return SIN;
    if (strcmp(word, "cos") == false) return COS;
    if (strcmp(word, "tan") == false) return TAN;
    if ((strcmp(word, "asin") == false) || (strcmp(word, "arcsin") == false)) return ASIN;
    if ((strcmp(word, "acos") == false) || (strcmp(word, "arccos") == false)) return ACOS;
    if ((strcmp(word, "atan") == false) || (strcmp(word, "arctan") == false)) return ATAN;
    if (strcmp(word, "sinh") == false) return SINH;
    if (strcmp(word, "cosh") == false) return COSH;
    if (strcmp(word, "tanh") == false) return TANH;
    if (strcmp(word, "exp") == false) return EXP;
    if (strcmp(word, "ln") == false) return LN;
    if (strcmp(word, "lg") == false) return LG;

    return NOT_FUNC;

}



Node_t * GetP(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    if (**ip == '(') {
        (*ip)++;
        Node_t * new_node = GetE(ip);
        (*ip)++;
        return new_node;

    } else if (isdigit(**ip) == true) {
        return GetN(ip);

    } else if (IsVariable(**ip) == true) {
        return GetV(ip);

    } else
        assert(0);

}



bool IsVariable(char symbol) {
    if (('a' <= symbol && symbol <= 'z') || (symbol == '_'))
        return true;
    else
        return false;

}



Node_t * GetJ(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    Node_t * first_node = GetP(ip);
    if (!first_node) return NULL;

    Node_t * new_node = first_node;

    while (**ip == '^') {
        (*ip)++;

        Node_t * second_node = GetP(ip);
        if (!second_node) return NULL;

        new_node = CreateAndFillNewOpNode(POW, first_node, second_node);

        first_node = new_node;

    }

    return new_node;

}



Node_t * GetT(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    Node_t * first_node = GetJ(ip);
    if (!first_node) return NULL;

    Node_t * new_node = first_node;

    while (**ip == '*' || **ip == '/') {
        char operation = **ip;
        (*ip)++;

        Node_t * second_node = GetJ(ip);
        if (!second_node) return NULL;

        if (operation == '*')
            new_node = CreateAndFillNewOpNode(MUL, first_node, second_node);
        else
            new_node = CreateAndFillNewOpNode(DIV, first_node, second_node);

        first_node = new_node;

    }

    return new_node;

}



Node_t * GetE(char ** ip) {
    assert(ip != NULL);
    assert(*ip != NULL);

    Node_t * first_node = GetT(ip);
    if (!first_node) return NULL;

    Node_t * new_node = first_node;

    while (**ip == '+' || **ip == '-') {
        char operation = **ip;
        (*ip)++;

        Node_t * second_node = GetT(ip);
        if (!second_node) return NULL;

        if (operation == '+')
            new_node = CreateAndFillNewOpNode(ADD, first_node, second_node);
        else
            new_node = CreateAndFillNewOpNode(SUB, first_node, second_node);

        first_node = new_node;

    }

    return new_node;

}



Node_t * CreateAndFillNewOpNode(enum values_type_op val_op, Node_t * first_node, Node_t * second_node) {
    assert(first_node);
    assert(second_node);

    Node_t * new_node = CreateNode(NULL, first_node, second_node, TYPE_OP, val_op);
    if (!new_node) {
        DeleteSubTree(first_node);
        DeleteSubTree(second_node);
        return NULL;

    }

    return new_node;

}



Node_t * ReadExpression(char * str) {
    assert(str);

    char * ip = str;
    Node_t * new_node = GetE(&ip);

    if (*ip != '$') {
        printf(". %c%c%c\n", *(ip-1), *ip, *(ip+1));
        DeleteSubTree(new_node);
        return NULL;

    }

    ParentSons(new_node);
    return new_node;

}