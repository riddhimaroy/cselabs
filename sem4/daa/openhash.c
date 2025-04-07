#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int ele;
    struct Node* next;
} Node;

Node* newNode(int key)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->ele = key;
    return n;
}

int main()
{
    int n, i, j, a[50], h, p, max;

    printf("enter the number of elements\n");
    scanf("%d", &n);

    printf("enter the elements in the array\n");
    for(i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        if(a[i]>max)
            max = a[i];
    }

    printf("enter the hash key\n");
    scanf("%d", &h);

    Node* arr[50];

    for(i=0; i<h; i++)
    {
        arr[i] = NULL;
    }

    for(i=0; i<n; i++)
    {
        p = a[i]%h;

        Node* nn = newNode(a[i]);
        nn->next = arr[p];
        arr[p] = nn;
    }

    for(i=0; i<h; i++)
    {
        Node* curr = arr[i];

        printf("%d: ", i);

        while(curr)
        {
            printf("%d ", curr->ele);
            curr = curr->next;
        }

        printf("\n");
    }
}