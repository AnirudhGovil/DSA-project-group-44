#include"../hash.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int main (void)
{
    char choice[25];
    scanf("%s", &choice[0]);
    int N,Q;
    scanf("%d", &N);
    scanf("%d", &Q);

    if (strcmp(choice, "separate-chaining")==0)
    {
        Node* array = empty_array(N);
        Initialize_to_zero(array, N);
        for(int x=0;x<Q;x++)
        {
            char operation;
            int number;
            scanf("\n%c %d", &operation, &number);
            int key = identity_hash(number,N);
            if (operation == '+')
                add_element_sc(array,key,number);
            if (operation == '?')
            {
                int index = find_element_sc(array, key,number);
                printf("%d\n", index);
            }

        }
        free_array_sc(array, N);
    }

    else if (strcmp(choice, "linear-probing")==0)
    {
        int* array = (int*) malloc(sizeof (int)*N);
        for(int x=0;x<N;x++)
            array[x] = -1;
        for(int x=0;x<Q;x++)
        {
            char operation;
            int number;
            scanf("\n%c %d", &operation, &number);
            int key = identity_hash(number,N);
            if (operation == '+')
                add_element_lp(array,key,number,N);
            if (operation == '?')
            {
                int index = find_element_lp(array, key,number,N);
                printf("%d\n", index);
            }
        }
        free(array);
    }
    else if (strcmp(choice, "quadratic-probing")==0)
    {
        int* array = (int*) malloc(sizeof (int)*N);
        for(int x=0;x<N;x++)
            array[x] = -1;
        for(int x=0;x<Q;x++)
        {
            char operation;
            int number;
            scanf("\n%c %d", &operation, &number);
            int key = identity_hash(number,N);
            if (operation == '+')
                add_element_qp(array,key,number,N);
            if (operation == '?')
            {
                int index = find_element_qp(array, key,number,N);
                printf("%d\n", index);
            }
        }
        free(array);
    }

}
