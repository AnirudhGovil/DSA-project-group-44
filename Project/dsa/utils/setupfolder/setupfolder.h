#ifndef SETUPFOLDER_H
#define SETUPFOLDER_H

int setupfolder(char **args);

typedef struct node node;
typedef node* tree;
struct node
{
    char* dir_name;
    int depth;
    node* next_sibling;
    node* first_child;
    node* parent;
};



#endif