#include <sys/stat.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "file_read_and_write.h"

struct val_params
{
    int val;
    int type;
};

static val_params read_val_from_buff(char* buff);
static void from_buff_to_tree(Node** nd, char** buff);

Node* read_questions_from_file_to_tree()
{
    FILE* f_data = fopen("diff_data.txt", "r");

    assert(f_data);

    Node* nd = Tree_ctor(f_data);

    fclose(f_data);

    return nd;
}

size_t count_symbls(FILE* all_file)
{
    assert(all_file);

    struct stat st;

    fstat(fileno(all_file), &st);

    return (size_t)st.st_size;
}

void from_file_to_tree(FILE* file, Node** nd)
{
    size_t len_file = count_symbls(file);

    char* akinator_data = (char*) calloc(len_file, 1);

    fread(akinator_data, 1, len_file, file);

    char* buff = akinator_data;
    from_buff_to_tree(nd, &buff);

    free(akinator_data);
}

static void from_buff_to_tree(Node** nd, char** buff)
{
    val_params value = read_val_from_buff(*buff);

    if(**buff == '(')
    {
        from_buff_to_tree(&((*nd) -> left), buff);
    }

    *nd = Create_node(value.type, value.val);

    if(**buff == '(')
    {
        from_buff_to_tree(&((*nd) -> right), buff);
    }

    if(**buff == ')')
    {
        ++(*buff);
        return;
    }
}

static val_params read_val_from_buff(char* buff)
{
    int val = sscanf("%d", buff);

    int type = 0;

    //тут жестко написать парсинг

    return {type, val};
}

void Print_to_file(Node* nd, FILE* file)
{
    if(!nd)   return;

    putc('(', file);

    if(nd -> left)
        Print_to_file(nd -> left, file);

    fprintf(file, "\"%d\"", nd -> value);

    if(nd -> right)
        Print_to_file(nd -> right, file);

    putc(')', file);
}

void write_questions_to_file(Node* nd)
{
    FILE* f_data = fopen("diff_data.txt", "w");

    assert(f_data);
    assert(nd);
    if(ferror(f_data))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    Print_to_file(nd, f_data);

    fclose(f_data);
}

