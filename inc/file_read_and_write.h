#include "tree.h"

Node* read_questions_from_file_to_tree();

void from_file_to_tree(FILE* file, Node** nd);

void write_questions_to_file(Node* nd);
