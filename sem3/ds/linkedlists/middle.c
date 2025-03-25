// Find Middle of the Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

int main()
{
    int x, n=0, i;
    node* head = (node*)malloc(sizeof(node));
    //head = NULL;

    printf("keep entering in the next node until pressing -1");
    node *p = head;
    x=0;

    while(1)
    {
        scanf("%d", &x);
        if(x==-1)
        {
            p->link = NULL;
            break;
        }
        p->data = x;
        p->link = (node*)malloc(sizeof(node));
        p = p->link;
    }
    // p->link = NULL;
    printf("h");

    //to count
    p = head;
    while(p->link != NULL)
    {
        n++;
        p = p->link;
    }
    printf("%d", n);

    p = head;

    if(n%2==1)
    {
        printf("the middle node has the data -");
        for (i=0; i<n/2; i++)
        {
            p = p->link;
        }
        printf(" %d", p->data);
    }

    if(n%2==0)
    {
        printf("there are even number of nodes so the two middle nodes are - ");
        for (i=0; i<n/2-1; i++)
        {
            p = p->link;
        }
        printf(" %d and %d", p->data, p->link->data);
    }

}