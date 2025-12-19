#include "expression_tree_base.h"



#pragma once

#define FILE_NAME_TREE_GRAPH_DUMP "tree_graph_dump"
#define FILE_NAME_TEX_DUMP "tex_dump"
#define FILE_NAME_GRAPH_OF_FUNCTIONS "graph_of_functions"



int TreeGraphDump(Tree_t * tree);
    void WriteTreeGraphDump(Tree_t * tree, FILE * file_tree_dump);
        void WriteHeaderTreeDump(FILE * file_tree_dump);
        void WriteNodeAndEdge(Tree_t * tree, FILE * file_tree_dump, Node_t * node);
            void WriteGraphNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node);
                void WriteBeginNode(FILE * file_tree_dump, Node_t * node);
                void WritePtrNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node);
                void WritePtrParentNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node);
                void WriteTypeNode(FILE * file_tree_dump, Node_t * node);
                void WriteValNode(Tree_t * tree, FILE * file_tree_dump, Node_t * node);
                    void WriteValNodeForTypeOP(FILE * file_tree_dump, Node_t * node);
                    void WriteValNodeForTypeVAR(FILE * file_tree_dump, Node_t * node);
                    void WriteValNodeForTypeNUM(FILE * file_tree_dump, Node_t * node);
                    void WriteValNodeForTypeFUNC(FILE * file_tree_dump, Node_t * node);
                    void WriteValNodeForTypeFICT(FILE * file_tree_dump, Node_t * node);
                void WriteSonsNode(FILE * file_tree_dump, Node_t * node);
                void WriteEndNode(FILE * file_tree_dump, Node_t * node);
    void SystemCommandsForGraphDump();

int TexDump(Tree_t * tree, Tree_t * tree_diff, const char * diff_var);
    void FillTexFile(Tree_t * tree, Tree_t * tree_diff, FILE * file_tree_dump, const char * diff_var);
        void FillPreamble(FILE * file_tree_dump);
        void FillTextAndInitialExpression(FILE * file_tree_dump, Node_t * node, const char * diff_var);
        void FillTextAndDiffExpression(FILE * file_tree_dump, Node_t * node, const char * diff_var);
        void FillTextAndBuildGraph(FILE * file_tree_dump, Node_t * node_tree, Node_t * node_tree_diff, const char * diff_var);
            void WriteSettingsGraph(FILE * file_tree_dump, const char * diff_var);
            void BuildInitialFunction(FILE * file_tree_dump, Node_t * node, const char * diff_var);
            void BuildDiffFunction(FILE * file_tree_dump, Node_t * node_tree_diff, const char * diff_var);
            void WriteTheEndGraph(FILE * file_tree_dump);
        void WriteSubExpressionToTex(FILE * file_tree_dump, Node_t * node);
            void WriteOperator(FILE * file_tree_dump, Node_t * node);
                void WriteAdd(FILE * file_tree_dump, Node_t * node);
                void WriteSub(FILE * file_tree_dump, Node_t * node);
                void WriteMul(FILE * file_tree_dump, Node_t * node);
                    bool IsLeaf(Node_t * node);
                    bool IsFunc(Node_t * node);
                    bool IsPOW(Node_t * node);
                    bool IsMUL(Node_t * node);
                void WriteDiv(FILE * file_tree_dump, Node_t * node);
                void WritePow(FILE * file_tree_dump, Node_t * node);
            void WriteVariable(FILE * file_tree_dump, Node_t * node);
            void WriteNumber(FILE * file_tree_dump, Node_t * node);
            void WriteFunction(FILE * file_tree_dump, Node_t * node);
                void WriteSqrt(FILE * file_tree_dump, Node_t * node);
                void WriteSin(FILE * file_tree_dump, Node_t * node);
                void WriteCos(FILE * file_tree_dump, Node_t * node);
                void WriteTan(FILE * file_tree_dump, Node_t * node);
                void WriteAsin(FILE * file_tree_dump, Node_t * node);
                void WriteAcos(FILE * file_tree_dump, Node_t * node);
                void WriteAtan(FILE * file_tree_dump, Node_t * node);
                void WriteSinh(FILE * file_tree_dump, Node_t * node);
                void WriteCosh(FILE * file_tree_dump, Node_t * node);
                void WriteTanh(FILE * file_tree_dump, Node_t * node);
                void WriteExp(FILE * file_tree_dump, Node_t * node);
                void WriteLn(FILE * file_tree_dump, Node_t * node);
                void WriteLg(FILE * file_tree_dump, Node_t * node);
            void WriteSubExpression(FILE * file_tree_dump, Node_t * node);
                void WriteOP(FILE * file_tree_dump, Node_t * node);
                void WriteFUNC(FILE * file_tree_dump, Node_t * node);
        void FillEnd(FILE * file_tree_dump);
    void SystemCommandsForTexDump();