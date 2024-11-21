#ifndef TREE
#define TREE

#include <stdio.h>

enum OPERATIONS
{
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
};

enum TYPE
{
    OP  = 1,
    VAR = 2,
    NUM = 3,
};

struct Node
{
    int type;
    int value;
    Node* right;
    Node* left;
};

Node* Tree_ctor(FILE* file);

Node* Create_node(int type, int val);

void Dot_file_compile(int num_pucture);

int find_tree_deep(Node* nd, int start_deep);

void Dot_dump(Node* nd, int num_graph);

void Print_to_file(Node* nd, FILE* file);

size_t count_symbls(FILE* all_file);

void Tree_dtor(Node* nd);

#endif