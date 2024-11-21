#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "file_read_and_write.h"

Node* Tree_ctor(FILE* file)
{
    Node* nd = {};

    from_file_to_tree(file, &nd);

    return nd;
}

Node* Create_node(int type, int val)
{
    Node* nd = (Node*) calloc(1, sizeof(Node));

    nd -> type  = type;
    nd -> value = val;
    nd -> left  = NULL;
    nd -> right = NULL;

    return nd;
}

int max_deep = 0;
int find_tree_deep(Node* nd, int start_deep)
{
    if(!nd -> left && !nd -> right)
    {
        if(start_deep > max_deep)
            max_deep = start_deep;
        return 0;
    }

    if(nd -> left)
    {
        find_tree_deep(nd -> left, start_deep + 1);
    }
    if(nd -> right)
    {
        find_tree_deep(nd -> right, start_deep + 1);
    }

    return max_deep;
}

static void Print_tree_to_dot_file(Node* nd, FILE* f_dot)
{
    if(!nd -> left && !nd -> right)
    {
        fprintf(f_dot, "\tnode0 [fillcolor=white, style=filled, shape=record, color=red,"
                  "label=\" NULL LIST ELEMENT | type=%d | value=%c | LEFT | RIGHT \" ];\n",
                   nd -> type, nd -> value);
    }
    else if(true)
    {
        fprintf(f_dot, "\tnode0 [fillcolor=white, style=filled, shape=record, color=red,"
                  "label=\" type=%d | value=%d | LEFT | RIGHT \" ];\n",
                   nd -> type, nd -> value);
    }

    if(nd -> left)
    {
        fprintf(f_dot, "\tnode%p -> node%p[fontcolor=\"red\"];\n", &nd -> value, &nd -> left -> value);
        Print_tree_to_dot_file(nd -> left, f_dot);
    }

    if(nd -> right)
    {
        fprintf(f_dot, "\tnode%p -> node%p[fontcolor=\"red\"];\n", &nd -> value, &nd -> right -> value);
        Print_tree_to_dot_file(nd -> right, f_dot);
    }
}

void Dot_dump(Node* nd, int num_graph)
{
    FILE* f_dot = fopen("output/diff_data.dot", "w");

    assert(f_dot);
    assert(nd);
    if(ferror(f_dot))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    fprintf(f_dot, "digraph Diff%d {\n\trankdir=LR;\n\tbgcolor = \"green:yellow\";\n", num_graph);

    Print_tree_to_dot_file(nd, f_dot);

    fprintf(f_dot, "\tlabel=\"DIFF BY Evgeniy Rogov\";\n\tfontsize=30;\n\tfontname=\"Times-Roman\";\n\tlabelloc=\"t\";\n");

    fprintf(f_dot, "}\n\n");

    fclose(f_dot);

    Dot_file_compile(num_graph);
}

void Dot_file_compile(int num_pucture)
{
    char com1[50] = "dot -Tpng output/diff_data.dot > output/diff_data";
    char com2[5]  = ".png";

    char com[57] = "";

    char num_str[3] = "";

    snprintf(num_str, sizeof(num_str), "%d", num_pucture);

    sprintf(com, "%s%s%s", com1, num_str, com2);

    system(com);
}

void Tree_dtor(Node* nd)
{
    assert(nd);

    if(nd -> right)
        Tree_dtor(nd -> right);

    if(nd -> left)
        Tree_dtor(nd -> left);

    free(nd);
}