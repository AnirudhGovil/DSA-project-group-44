
#ifndef __HASH_H
#define __HASH_H

typedef struct string_node string_node;
typedef struct string_node_3 string_node_3;
typedef struct Node Node;
struct string_node_3
{
    char data[51000];
    string_node_3* next;
    string_node_3* prev;
};

struct string_node
{
    char data[1000];
    string_node* next;
    string_node* prev;
};
struct Node
{
    int data;
    Node* next;
    Node* prev;
};

Node* empty_array(int N);
int identity_hash(int number, int N);
void Initialize_to_zero(Node* array, int size);
void add_element_sc(Node* array, int key, int number);
int find_element_sc(Node* array, int key, int number);
Node* create_node(int data);
void free_array_sc(Node* array, int size);
void add_element_lp(int* array, int key, int number,int size);
int find_element_lp(int* array, int key, int number,int size);
void add_element_qp(int* array, int key, int number,int size);
int find_element_qp(int* array, int key, int number,int size);


string_node * empty_array_str(int N);
int horner_hash (char word[], int length,int size);
void add_element_sc_str(string_node* array, int key, char word[], int length);
int find_element_sc_str(string_node* array, int key, char word[]);
string_node* create_node_str(char word[]);
void free_array_sc_str(string_node* array, int size);


string_node_3 * empty_array_str_3(int N);
int horner_hash_3 (char word[], int length,int size);
void add_element_sc_str_3(string_node_3* array, int key, char word[], int length);
int find_element_sc_str_3(string_node_3* array, int key, char word[]);
string_node_3* create_node_str_3(char word[]);
void free_array_sc_str_3(string_node_3* array, int size);
void get_substring(char string[], char* substring, int length);
int check_repeat(char string[], int length_string, char substring[], int length_substring);



#endif
