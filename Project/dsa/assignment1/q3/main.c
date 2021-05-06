#include <stdio.h>
#include "../hash.h"
#include <string.h>


int main(void)
{
        char stringA[100005];
        char stringB[100005];
        scanf("%s", &stringA[0]);
        scanf("%s", &stringB[0]);
        int lengthA = (int)strlen(stringA);
        int lengthB = (int)strlen(stringB);
        int friend_index =0;
        int size = 100;
        string_node_3* array = empty_array_str_3(size);
        for (int x=1;x<=lengthA/2;x++)
        {
            if (lengthA%x == 0)
            {
                char substring[51000] = {'\000'};
                get_substring(stringA, &substring[0], x);
                int flag = check_repeat(stringA, lengthA, substring, x);
                if (flag == 1)
                {
                    int len_substring = (int)strlen(substring);
                    int key = horner_hash_3(substring,len_substring , size);
                    add_element_sc_str_3(array,key,substring,len_substring);
                }
            }
        }
        for (int x=1;x<=lengthB/2;x++)
        {
            if (lengthB%x == 0)
            {
                char substring[51000] = {'\000'};
                get_substring(stringB, &substring[0], x);
                int flag = check_repeat(stringB, lengthB,substring, x);
                if (flag == 1)
                {
                    int len_substring = (int)strlen(substring);
                    int key = horner_hash_3(substring, len_substring, size);
                    int flag2 = find_element_sc_str_3(array, key,substring);
                    if (flag2==1)
                        friend_index++;
                }
            }
        }
        if (lengthA%lengthB == 0 || lengthB%lengthA == 0)
        {
            if (lengthA>lengthB)
            {
                int flag = check_repeat(stringA, lengthA, stringB, lengthB);
                if (flag == 1)
                    friend_index++;
            }
            else
            {
                int flag = check_repeat(stringB, lengthB, stringA, lengthA);
                if (flag == 1)
                    friend_index++;
            }
        }


        printf("%d\n", friend_index);
        free_array_sc_str_3(array, size);
}
