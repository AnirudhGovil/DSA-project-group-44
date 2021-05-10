
#include <stdio.h>
#include <string.h>
#include "../hash.h"


int main(void)
{
    int N;
    scanf("%d", &N);
    int size = 100000;
    string_node* array = empty_array_str(size);

    for(int x=0;x<N;x++)
    {
        char word[1000];
        scanf("%s", &word[0]);
        int length = strlen(word);
        int key = horner_hash(word,length,size);
        add_element_sc_str(array,key,word, length);
    }
    int m;
    scanf("\n%d", &m);
    int incorrect = 0;
    char storage[5000000];
    int start_index = 0;
    for(int x=0;x<m;x++)
    {
        char word[40];
        scanf("%s", &word[0]);
        int length = strlen(word);
        int key = horner_hash(word,length,size);
        int flag = find_element_sc_str(array, key,word);
        if (flag==0)
        {
            incorrect++;
            strcpy(&storage[start_index], word);
            start_index = start_index+length+1;
            storage[start_index-1] = '\n';
        }
    }
    printf("%d\n", incorrect);
    printf("%s", storage);
    free_array_sc_str(array, size);
}
