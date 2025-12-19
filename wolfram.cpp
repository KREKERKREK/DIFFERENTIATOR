#include "differentiator.h"
#include "optimizing_tree.h"
#include "reader_expression.h"
#include "tree_dumps.h"



int main() {
    printf("We're started\n");
    Tree_t * tree = InitTree();
    Tree_t * tree_diff = InitTree();

    char str[] = "3*tanh(x^3-4)+3$";
    tree->fict_node->right = ReadExpression(str);
    tree->fict_node->right->parent = tree->fict_node;
    OptimizingSubTree(tree->fict_node);

    tree_diff = BuildTreeDiff(tree, "x");
    OptimizingSubTree(tree_diff->fict_node);

    TreeGraphDump(tree_diff);
    TexDump(tree, tree_diff, "x");

    DestroyTree(tree);
    DestroyTree(tree_diff);

}