#include <string.h>
#include<stdlib.h>
#include "hash.h"

int identity_hash(int number, int N)
{
    return number%N;
}
Node* empty_array(int N)
{
    Node* new_array = (Node*)malloc(sizeof (Node)*N);
    return new_array;
}
void Initialize_to_zero(Node* array, int size)
{
    for (int x=0;x<size;x++)
    {
        array[x].data = -1;
        array[x].next = NULL;
        array[x].prev = NULL;
    }
}
void add_element_sc(Node* array, int key, int number)
{
    Node* new_array = create_node(number);
    if (array[key].prev == NULL)
    {
        array[key].next = new_array;
        array[key].prev = new_array;
        return;
    }
    array[key].prev->next = new_array;
    array[key].prev = new_array;

}
int find_element_sc(Node* array, int key, int number)
{
    Node* start = array[key].next;
    int counter =0;
    while(start!=NULL)
    {
        if (start->data == number)
            return counter;
        start = start->next;
        counter++;
    }
    return -1;
}
Node* create_node(int data)
{
    Node* new_array = (Node*) malloc( sizeof (Node));
    new_array->data = data;
    new_array->next =NULL;
    new_array->prev =NULL;
    return new_array;
}
void free_array_sc(Node* array, int size)
{
    for(int x=0;x<size;x++)
    {
        while(array[x].next!=NULL)
        {
            Node* temp = array[x].next->next;
            free(array[x].next);
            array[x].next = temp;
        }

    }
    free(array);
}
void add_element_lp(int* array, int key, int number, int size)
{
    while(array[key]!=-1)
        key = (key+1)%size;
    array[key] = number;
}
int find_element_lp(int* array, int key, int number,int size)
{
    int index = -1;
    while(array[key] != -1)
    {
        if (array[key] == number)
        {
            index = key;
            break;
        }
        else
            key = (key+1)%size;
    }
    return index;
}
void add_element_qp(int* array, int key, int number,int size)
{
    int counter =0;
    while(array[(key+counter*counter)%size]!=-1)
        counter++;

    array[(key+counter*counter)%size] = number;
}
int find_element_qp(int* array, int key, int number,int size)
{
    int counter =0;
    int index = -1;
    while(array[(key+counter*counter)%size] != -1)
    {
        if (array[(key+counter*counter)%size] == number)
        {
            index = (key+counter*counter)%size;
            break;
        }
        else
            counter++;
    }
    return index;

}


string_node* empty_array_str(int N)
{
    string_node* new_array = (string_node*)malloc(sizeof(string_node)*N);
    return new_array;
}
int horner_hash (char word[],int length, int size)
{
    int key=0;
    int p =32;
    for(int x=0;x<length;x++)
    {
        int convert;
        convert = (int)(word[x]);
        key = (key*p+ convert)%size;
    }
    return key;
}
void add_element_sc_str(string_node* array, int key, char word[], int length)
{
    string_node* new_array = create_node_str(word);
    if (array[key].prev == NULL)
    {
        array[key].next = new_array;
        array[key].prev = new_array;
        return;
    }
    array[key].prev->next = new_array;
    array[key].prev = new_array;
}
int find_element_sc_str(string_node* array, int key, char word[])
{
    string_node* start = array[key].next;
    while(start!=NULL)
    {
        if (strcmp(word, start->data)==0)
            return 1;
        start = start->next;
    }
    return 0;
}
string_node* create_node_str(char word[])
{
    string_node* new_array = (string_node*) malloc( sizeof (string_node));
    strcpy(new_array->data, word);
    new_array->next = NULL;
    new_array->prev = NULL;
    return new_array;
}
void free_array_sc_str(string_node* array, int size)
{
    for(int x=0;x<size;x++)
    {
        string_node* next_node = array[x].next;
        while(next_node!=NULL)
        {
            free(next_node->prev);
            next_node = next_node->next;
            // string_node* temp = array[x].next;
            // array[x].next = array[x].next->next;
            // if(array[x].next!=NULL)
            //     array[x].next->prev = NULL;

            // free(temp);
        }
    }
    free(array);
}

string_node_3* empty_array_str_3(int N)
{
    string_node_3* new_array = (string_node_3*)malloc(sizeof(string_node_3)*N);
    return new_array;
}
int horner_hash_3 (char word[],int length, int size)
{
    int key=0;
    int p =32;
    for(int x=0;x<length;x++)
    {
        int convert;
        convert = (int)(word[x]);
        key = (key*p+ convert)%size;
    }
    return key;
}
void add_element_sc_str_3(string_node_3* array, int key, char word[], int length)
{
    string_node_3* new_array = create_node_str_3(word);
    if (array[key].prev == NULL)
    {
        array[key].next = new_array;
        array[key].prev = new_array;
        return;
    }
    array[key].prev->next = new_array;
    array[key].prev = new_array;
}
int find_element_sc_str_3(string_node_3* array, int key, char word[])
{
    string_node_3* start = array[key].next;
    while(start!=NULL)
    {
        if (strcmp(word, start->data)==0)
            return 1;
        start = start->next;
    }
    return 0;
}
string_node_3* create_node_str_3(char word[])
{
    string_node_3* new_array = (string_node_3*) malloc( sizeof (string_node_3));
    strcpy(new_array->data, word);
    new_array->next = NULL;
    new_array->prev = NULL;
    return new_array;
}
void free_array_sc_str_3(string_node_3* array, int size)
{
    for(int x=0;x<size;x++)
    {
        while(array[x].next!=NULL)
        {
            string_node_3* temp = array[x].next->next;
            free(array[x].next);
            array[x].next = temp;
        }
    }
    free(array);
}
void get_substring(char string[], char* substring, int length)
{
    for (int x=0;x<length;x++)
    {
        substring[x] = string[x];
    }
}
int check_repeat(char string[], int length_string, char substring[], int length_substring)
{
    int min_count = length_string/length_substring;
    int count = 0;
    for(int x=0;x<min_count;x++)
    {
        int sum=0;
        for(int y=0;y<length_substring;y++)
        {
            if (substring[y] == string[x*length_substring +y])
                sum++;
        }
        if (sum == length_substring)
            count++;
    }
    if (count == min_count)
        return 1;
    else
        return 0;
}

