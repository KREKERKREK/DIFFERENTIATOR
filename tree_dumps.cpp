#include "tree_dumps.h"



int TreeGraphDump(Tree_t * tree) {
    assert(tree != NULL);

    FILE * file_tree_dump = fopen(FILE_NAME_TREE_GRAPH_DUMP ".dot", "w");
    if (file_tree_dump == NULL)
        return OPEN_FILE_ERR;
    
    WriteTreeGraphDump(tree, file_tree_dump);

    if(fclose(file_tree_dump) == EOF)
        return CLOSE_FILE_ERR;
    
    SystemCommandsForGraphDump();

    return SUCCESS;

}



void WriteTreeGraphDump(Tree_t * tree, FILE * file_tree_dump) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);

    WriteHeaderTreeDump(file_tree_dump);
    WriteNodeAndEdge(tree, file_tree_dump, tree->fict_node);

    fprintf(file_tree_dump, "}");

}



void WriteHeaderTreeDump(FILE * file_tree_dump) {
    assert(file_tree_dump != NULL);

    fprintf(file_tree_dump, "digraph graph_tree_dump\n{\n"
                            "\tnode [shape = plaintext];\n"
                            "\trankdir = \"TB\";\n"
                            "\n");

}



void WriteGraphNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    WriteBeginNode(file_tree_dump, node);

    WritePtrNode(tree, file_tree_dump, node);
    WritePtrParentNode(tree, file_tree_dump, node);
    WriteTypeNode(file_tree_dump, node);
    WriteValNode(tree, file_tree_dump, node);
    WriteSonsNode(file_tree_dump, node);

    WriteEndNode(file_tree_dump, node);

}



void WriteBeginNode(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\"node %p\" [label =<\n", node);
    fprintf(file_tree_dump, "\t\t<TABLE BORDER=\"5\" CELLBORDER=\"2\" CELLSPACING=\"4\">\n"
                            "\t\t\t<TR>\n");

}



void WritePtrNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);
    assert(node != NULL);
    
    fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\"");
    ColorizePtrAndPtrParentNode(tree, node);
    fprintf(file_tree_dump, ">%p</TD>\n", node);
    fprintf(file_tree_dump, "\t\t\t</TR>\n"
		                    "\t\t\t<TR>\n");

}



void WritePtrParentNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\"");
    ColorizePtrAndPtrParentNode(tree, node);
    fprintf(file_tree_dump, ">parent = %p</TD>\n", node->parent);
    fprintf(file_tree_dump, "\t\t\t</TR>\n"
		                    "\t\t\t<TR>\n");

}



void WriteTypeNode(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    switch (node->type_node) {
        case TYPE_OP:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#8ff397ff\">type = %s</TD>\n", "OP");
            break;
        
        case TYPE_VAR:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#ff6a97ff\">type = %s</TD>\n", "VAR");
            break;
        
        case TYPE_NUM:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#FFEDAB\">type = %s</TD>\n", "NUM");
            break;
        
        case TYPE_FUNC:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">type = %s</TD>\n", "FUNC");
            break;

        case TYPE_FICT:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#ffffffff\">type = %s</TD>\n", "FICT");
            break;

        default:
            assert(0);

    }

    fprintf(file_tree_dump, "\t\t\t</TR>\n"
		                    "\t\t\t<TR>\n");

}



void WriteValNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    switch (node->type_node) {
        case TYPE_OP:
            WriteValNodeForTypeOP(file_tree_dump, node);
            break;
        
        case TYPE_VAR:
            WriteValNodeForTypeVAR(file_tree_dump, node);
            break;
        
        case TYPE_NUM:
            WriteValNodeForTypeNUM(file_tree_dump, node);
            break;
        
        case TYPE_FUNC:
            WriteValNodeForTypeFUNC(file_tree_dump, node);
            break;

        case TYPE_FICT:
            WriteValNodeForTypeFICT(file_tree_dump, node);
            break;
        
        default:
            assert(0);

    }

    fprintf(file_tree_dump, "\t\t\t</TR>\n"
		                    "\t\t\t<TR>\n");

}



void WriteValNodeForTypeOP(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);
    
    switch (node->val.val_op) {
        case ADD:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#31c253ff\">value = %s</TD>\n", "ADD");
            break;
        
        case SUB:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#31c253ff\">value = %s</TD>\n", "SUB");
            break;
        
        case MUL:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#31c253ff\">value = %s</TD>\n", "MUL");
            break;
        
        case DIV:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#31c253ff\">value = %s</TD>\n", "DIV");
            break;
        
        case POW:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#31c253ff\">value = %s</TD>\n", "POW");
            break;
            
        case NOT_OP:
            break;
        
        default:
            assert(0);

    }

}



void WriteValNodeForTypeVAR(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#ff0202d1\">value = %lg \"%s\"</TD>\n", node->val.struct_var.value_var, node->val.struct_var.name_var);

}



void WriteValNodeForTypeNUM(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#f08731ff\">value = %lg</TD>\n", node->val.val_num);

}



void WriteValNodeForTypeFUNC(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);
    
    switch (node->val.val_func) {
        case SQRT:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "SQRT");
            break;
        
        case SIN:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "SIN");
            break;
        
        case COS:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "COS");
            break;
        
        case TAN:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "TAN");
            break;
        
        case ASIN:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "ASIN");
            break;
        
        case ACOS:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "ACOS");
            break;
        
        case ATAN:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "ATAN");
            break;
        
        case SINH:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "SINH");
            break;
        
        case COSH:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "COSH");
            break;
        
        case TANH:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "TANH");
            break;
        
        case EXP:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "EXP");
            break;
        
        case LN:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "LN");
            break;
        
        case LG:
            fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#e18ff3ff\">value = %s</TD>\n", "LG");
            break;

        case NOT_FUNC:
        default:
            assert(0);

    }

}



void WriteValNodeForTypeFICT(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"2\" bgcolor = \"#ffffffff\">value = %lg</TD>\n", node->val.val_num);

}



void WriteSonsNode(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    if (node->left == NULL) {
        fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"1\" bgcolor = \"#44a4f8ff\">%s</TD>\n", "NULL");

    } else {
        fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"1\"");
        ColorizeSonNode(node->left);
        fprintf(file_tree_dump, ">%p</TD>\n", node->left);

    }
    
    if (node->right == NULL) {
        fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"1\" bgcolor = \"#44a4f8ff\">%s</TD>\n", "NULL");

    } else {
        fprintf(file_tree_dump, "\t\t\t\t<TD COLSPAN = \"1\"");
        ColorizeSonNode(node->right);
        fprintf(file_tree_dump, ">%p</TD>\n", node->right);

    }
    
}



void WriteEndNode(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\t\t\t</TR>\n"
	                    	"\t\t</TABLE>\n"
	                        "\t>];\n\n");

}



void WriteNodeAndEdge(Tree_t * tree, FILE * file_tree_dump, Node_t * node) {
    assert(tree != NULL);
    assert(file_tree_dump != NULL);
    assert(node != NULL);
    
    WriteGraphNode(tree, file_tree_dump, node);

    if (node->left) {
        fprintf(file_tree_dump, "\t\"node %p\" -> \"node %p\";\n\n", node, node->left);
        WriteNodeAndEdge(tree, file_tree_dump, node->left);

    }

    if (node->right) {
        fprintf(file_tree_dump, "\t\"node %p\" -> \"node %p\";\n\n", node, node->right);
        WriteNodeAndEdge(tree, file_tree_dump, node->right);

    }

}



void SystemCommandsForGraphDump() {
    system("cd /Users/saveliy/WORKING/DIFFERENTIATOR/");
    system("dot -Tpng " FILE_NAME_TREE_GRAPH_DUMP ".dot -o " FILE_NAME_TREE_GRAPH_DUMP ".png");
    system("open " FILE_NAME_TREE_GRAPH_DUMP ".png");

}



int TexDump(Tree_t * tree, Tree_t * tree_diff, const char * diff_var) {
    assert(tree);
    assert(tree_diff);

    FILE * file_tree_dump = fopen("" FILE_NAME_TEX_DUMP ".tex", "w");    //Создать файл с расширением tex
    if (file_tree_dump == NULL)
        return OPEN_FILE_ERR;

    FillTexFile(tree, tree_diff, file_tree_dump, diff_var);     //заполнить файл

    if (fclose(file_tree_dump) == EOF)                          //закрыть файл
        return CLOSE_FILE_ERR;

    SystemCommandsForTexDump();                                 //системно переформатировать из tex в pdf и открыть
    return SUCCESS;

}



void FillTexFile(Tree_t * tree, Tree_t * tree_diff, FILE * file_tree_dump, const char * diff_var) {
    assert(tree);
    assert(tree_diff);
    assert(file_tree_dump);

    FillPreamble(file_tree_dump);
    FillTextAndInitialExpression(file_tree_dump, tree->fict_node->right, diff_var);
    FillTextAndDiffExpression(file_tree_dump, tree_diff->fict_node->right, diff_var);
    FillTextAndBuildGraph(file_tree_dump, tree->fict_node->right, tree_diff->fict_node->right, diff_var);
    FillEnd(file_tree_dump);

}



void FillPreamble(FILE * file_tree_dump) {
    assert(file_tree_dump);

    fprintf(file_tree_dump, "\\documentclass{article}\n"
                            "\\usepackage[utf8]{inputenc}\n"
                            "\\usepackage[T2A]{fontenc}\n"
                            "\\usepackage[english, russian]{babel}\n"
                            "\\usepackage{pgfplots}\n"
                            "\\usepackage{amsmath}\n"
                            "\\pgfplotsset{compat = 1.18}\n"
                            "\\usepackage{graphicx}\n"
                            "\\begin{document}\n\n\n\n");

}



void FillTextAndInitialExpression(FILE * file_tree_dump, Node_t * node, const char * diff_var) {
    assert(file_tree_dump);
    assert(node);
    assert(diff_var);

    fprintf(file_tree_dump, "Итак, имеется следующее выражение:\n"
                            "\\begin{equation}\n"
                            "f(%s) = ", diff_var);

    WriteSubExpressionToTex(file_tree_dump, node);

    fprintf(file_tree_dump, "\n"
                            "\\end{equation}\n\n");

}



void FillTextAndDiffExpression(FILE * file_tree_dump, Node_t * node, const char * diff_var) {
    assert(file_tree_dump);
    assert(node);
    assert(diff_var);

    fprintf(file_tree_dump, "Продифференцировав $f(%s)$ по $%s$ получаем:\n", diff_var, diff_var);
    fprintf(file_tree_dump, "\\begin{equation}\n");
    fprintf(file_tree_dump, "f'(%s) = \\frac{d(f(%s))}{d%s} = ", diff_var, diff_var, diff_var);

    WriteSubExpressionToTex(file_tree_dump, node);

    fprintf(file_tree_dump, "\n"
                            "\\end{equation}\n\n");

}



void FillTextAndBuildGraph(FILE * file_tree_dump, Node_t * node_tree, Node_t * node_tree_diff, const char * diff_var) {
    assert(file_tree_dump);
    assert(node_tree);
    assert(node_tree_diff);
    assert(diff_var);

    fprintf(file_tree_dump, "Ниже приведён график зависимости функций $f(%s)$ и $f'(%s)$:\n", diff_var, diff_var);

    WriteSettingsGraph(file_tree_dump, diff_var);
    BuildInitialFunction(file_tree_dump, node_tree, diff_var);
    BuildDiffFunction(file_tree_dump, node_tree_diff, diff_var);
    WriteTheEndGraph(file_tree_dump);

}



void WriteSettingsGraph(FILE * file_tree_dump, const char * diff_var) {
    assert(file_tree_dump);
    assert(diff_var);

    fprintf(file_tree_dump, "\\begin{figure}[h!]\n"
                            "\\centering\n"
                            "\\begin{tikzpicture}\n"
                            "\\begin{axis}[\n"
                            "\ttitle = {Сравнение функций},\n"
                                "\taxis lines = middle,\n"
                                "\txlabel = %s, ylabel = f(%s) и f'(%s)\n,", diff_var, diff_var, diff_var);
    fprintf(file_tree_dump,     "\tlegend pos = north west,\n"
                                "\twidth = 15cm,\n"
                                "\theight = 8cm,\n"
                                "\tdomain = -3:3,\n"
                                "\tsamples = 100\n"
                            "]\n");

}



void BuildInitialFunction(FILE * file_tree_dump, Node_t * node_tree, const char * diff_var) {
    assert(file_tree_dump);
    assert(node_tree);
    assert(diff_var);

    fprintf(file_tree_dump, "\\addplot[orange, very thick] {");
    WriteSubExpression(file_tree_dump, node_tree);

    fprintf(file_tree_dump, "};\n"
                            "\\addlegendentry{\\(f(%s) = ", diff_var);

    WriteSubExpressionToTex(file_tree_dump, node_tree);
    fprintf(file_tree_dump, "\\)}\n");

}



void BuildDiffFunction(FILE * file_tree_dump, Node_t * node_tree_diff, const char * diff_var) {
    assert(file_tree_dump);
    assert(node_tree_diff);
    assert(diff_var);

    fprintf(file_tree_dump, "\\addplot[blue, very thick] {");
    WriteSubExpression(file_tree_dump, node_tree_diff);

    fprintf(file_tree_dump, "};\n"
                            "\\addlegendentry{\\(f'(%s) = ", diff_var);

    WriteSubExpressionToTex(file_tree_dump, node_tree_diff);
    fprintf(file_tree_dump, "\\)}\n");

}



void WriteTheEndGraph(FILE * file_tree_dump) {
    assert(file_tree_dump);

    fprintf(file_tree_dump, "\\end{axis}\n"
                            "\\end{tikzpicture}\n"
                            "\\end{figure}");

}



void WriteSubExpressionToTex(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump);
    assert(node);

    switch (node->type_node) {
        case TYPE_OP:
            WriteOperator(file_tree_dump, node);
            break;
        
        case TYPE_VAR:
            WriteVariable(file_tree_dump, node);
            break;
        
        case TYPE_NUM:
            WriteNumber(file_tree_dump, node);
            break;

        case TYPE_FUNC:
            WriteFunction(file_tree_dump, node);
            break;

        case TYPE_FICT:
            break;
        
        default:
            assert(0);

    }

}



void WriteOperator(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    switch (node->val.val_op) {
        case ADD:
            WriteAdd(file_tree_dump, node);
            break;
        
        case SUB:
            WriteSub(file_tree_dump, node);
            break;
        
        case MUL:
            WriteMul(file_tree_dump, node);
            break;
        
        case DIV:
            WriteDiv(file_tree_dump, node);
            break;
        
        case POW:
            WritePow(file_tree_dump, node);
            break;
        
        case NOT_OP:
            break;
        
        default:
            assert(0);

    }

}



void WriteAdd(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    WriteSubExpressionToTex(file_tree_dump, node->left);
    fprintf(file_tree_dump, " + ");
    WriteSubExpressionToTex(file_tree_dump, node->right);

}



void WriteSub(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    WriteSubExpressionToTex(file_tree_dump, node->left);

    fprintf(file_tree_dump, " - ");

    if ((IsLeaf(node->right) == true) || (IsFunc(node->right) == true) || IsMUL(node->right)) {
        WriteSubExpressionToTex(file_tree_dump, node->right);

    } else {
        fprintf(file_tree_dump, "(");
        WriteSubExpressionToTex(file_tree_dump, node->right);
        fprintf(file_tree_dump, ")");

    }

}



bool IsMUL(Node_t * node) {
    assert(node);

    if (node->type_node == TYPE_OP) {
        if (node->val.val_op == MUL)
            return true;

    }

    return false;

}



void WriteMul(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    if ((IsLeaf(node->left) == true) || (IsFunc(node->left) == true) || (IsPOW(node->left) == true) || IsMUL(node->left)) {
        WriteSubExpressionToTex(file_tree_dump, node->left);

    } else {
        fprintf(file_tree_dump, "(");
        WriteSubExpressionToTex(file_tree_dump, node->left);
        fprintf(file_tree_dump, ")");

    }

    fprintf(file_tree_dump, "\\cdot ");

    if ((IsLeaf(node->right) == true) || (IsFunc(node->right) == true) || (IsPOW(node->right) == true) || IsMUL(node->right)) {
        WriteSubExpressionToTex(file_tree_dump, node->right);

    } else {
        fprintf(file_tree_dump, "(");
        WriteSubExpressionToTex(file_tree_dump, node->right);
        fprintf(file_tree_dump, ")");

    }

}



bool IsLeaf(Node_t * node) {
    assert(node != NULL);

    if ((node->left == NULL) && (node->right == NULL))
        return true;
    else
        return false;

}



bool IsFunc(Node_t * node) {
    assert(node != NULL);

    if (node->type_node == TYPE_FUNC)
        return true;
    else
        return false;

}



bool IsPOW(Node_t * node) {
    assert(node != NULL);

    if (node->type_node == TYPE_OP) {
        if (node->val.val_op == POW)
            return true;

    }

    return false;

}



void WriteDiv(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "\\frac{");
    WriteSubExpressionToTex(file_tree_dump, node->left);
    fprintf(file_tree_dump, "}");

    fprintf(file_tree_dump, "{");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, "}");

}



void WritePow(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    if ((IsLeaf(node->left) == true) || (IsFunc(node->left) == true)) {
        WriteSubExpressionToTex(file_tree_dump, node->left);
        fprintf(file_tree_dump, "^{");

        WriteSubExpressionToTex(file_tree_dump, node->right);
        fprintf(file_tree_dump, "}");

    } else {
        fprintf(file_tree_dump, "(");
        WriteSubExpressionToTex(file_tree_dump, node->left);
        fprintf(file_tree_dump, ")^{");

        WriteSubExpressionToTex(file_tree_dump, node->right);
        fprintf(file_tree_dump, "}");

    }

}



void WriteVariable(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "%s", node->val.struct_var.name_var);

}



void WriteNumber(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "%lg", node->val.val_num);

}



void WriteFunction(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump);
    assert(node);

    switch (node->val.val_func) {
        case SQRT:
            WriteSqrt(file_tree_dump, node);
            break;
        
        case SIN:
            WriteSin(file_tree_dump, node);
            break;
        
        case COS:
            WriteCos(file_tree_dump, node);
            break;
        
        case TAN:
            WriteTan(file_tree_dump, node);
            break;
        
        case ASIN:
            WriteAsin(file_tree_dump, node);
            break;
        
        case ACOS:
            WriteAcos(file_tree_dump, node);
            break;
        
        case ATAN:
            WriteAtan(file_tree_dump, node);
            break;
        
        case SINH:
            WriteSinh(file_tree_dump, node);
            break;
        
        case COSH:
            WriteCosh(file_tree_dump, node);
            break;
        
        case TANH:
            WriteTanh(file_tree_dump, node);
            break;
        
        case EXP:
            WriteExp(file_tree_dump, node);
            break;
        
        case LN:
            WriteLn(file_tree_dump, node);
            break;
        
        case LG:
            WriteLg(file_tree_dump, node);
            break;
        
        case NOT_FUNC:
            break;
        
        default:
            assert(0);

    }

}



void WriteSqrt(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\sqrt{");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, "}");

}



void WriteSin(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\sin{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteCos(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\cos{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteTan(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\tan{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteAsin(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\arcsin{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteAcos(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\arccos{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteAtan(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\arctan{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteSinh(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\sinh{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteCosh(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\cosh{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteTanh(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\tanh{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteExp(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " e^{");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, "}");

}



void WriteLn(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\ln{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteLg(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, " \\lg{(");
    WriteSubExpressionToTex(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")}");

}



void WriteSubExpression(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump);
    assert(node);

    switch (node->type_node) {
        case TYPE_OP:
            WriteOP(file_tree_dump, node);
            break;
        
        case TYPE_VAR:
            WriteVariable(file_tree_dump, node);
            break;
        
        case TYPE_NUM:
            WriteNumber(file_tree_dump, node);
            break;

        case TYPE_FUNC:
            WriteFUNC(file_tree_dump, node);
            break;

        case TYPE_FICT:
            break;
        
        default:
            assert(0);

    }

}



void WriteOP(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump != NULL);
    assert(node != NULL);

    fprintf(file_tree_dump, "(");
    WriteSubExpression(file_tree_dump, node->left);
    fprintf(file_tree_dump, ")");

    switch (node->val.val_op) {
        case ADD:
            fprintf(file_tree_dump, " + ");
            break;
        
        case SUB:
            fprintf(file_tree_dump, " - ");
            break;
        
        case MUL:
            fprintf(file_tree_dump, " * ");
            break;
        
        case DIV:
            fprintf(file_tree_dump, " / ");
            break;
        
        case POW:
            fprintf(file_tree_dump, "^");
            break;
        
        case NOT_OP:
            break;
        
        default:
            assert(0);

    }

    fprintf(file_tree_dump, "(");
    WriteSubExpression(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")");

}



void WriteFUNC(FILE * file_tree_dump, Node_t * node) {
    assert(file_tree_dump);
    assert(node);

    switch (node->val.val_func) {
        case SQRT:
            fprintf(file_tree_dump, "sqrt(");
            break;
        
        case SIN:
            fprintf(file_tree_dump, "sin(");
            break;
        
        case COS:
            fprintf(file_tree_dump, "cos(");
            break;
        
        case TAN:
            fprintf(file_tree_dump, "tan(");
            break;
        
        case ASIN:
            fprintf(file_tree_dump, "arcsin(");
            break;
        
        case ACOS:
            fprintf(file_tree_dump, "arccos(");
            break;
        
        case ATAN:
            fprintf(file_tree_dump, "arctan(");
            break;
        
        case SINH:
            fprintf(file_tree_dump, "sinh(");
            break;
        
        case COSH:
            fprintf(file_tree_dump, "cosh(");
            break;
        
        case TANH:
            fprintf(file_tree_dump, "tanh(");
            break;
        
        case EXP:
            fprintf(file_tree_dump, "exp(");
            break;
        
        case LN:
            fprintf(file_tree_dump, "ln(");
            break;
        
        case LG:
            fprintf(file_tree_dump, "lg(");
            break;
        
        case NOT_FUNC:
            break;
        
        default:
            assert(0);

    }

    WriteSubExpression(file_tree_dump, node->right);
    fprintf(file_tree_dump, ")");

}



void FillEnd(FILE * file_tree_dump) {
    assert(file_tree_dump != NULL);

    fprintf(file_tree_dump, "\n\n\\end{document}");

}



void SystemCommandsForTexDump() {
    system("pdflatex " FILE_NAME_TEX_DUMP ".tex > /dev/null");
    system("open " FILE_NAME_TEX_DUMP ".pdf");

}