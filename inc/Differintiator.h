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