// Implement a queue using singly linked list without header node

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

int isEmpty(node *first)
{
    return(first->data==-1);
}

void enqueue(node *first, int x)
{
    node* p = first;

    if(isEmpty(first))
    {
        first->data = x;
        return;
    }

    while(p->link != NULL)
    {
        p = p->link;
    }

    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    p->link = new;
    new->link = NULL;
    //printf("hi\n");
}

void dequeue(node *first)
{
    if(isEmpty(first))
    {
        printf("No elements to dequeue\n");
        return;
    }
    node* p = first;
    // p = first->link;
    // first->link = p->link;
    first = first->link;
    free(p);
}

node* reverse(node* first)
{
    node*q = first;
    node* next = (node*)malloc(sizeof(node));
    node* prev = (node*)malloc(sizeof(node));

    while(q!=NULL)
        {
            next = q->link;
            q->link = prev;
            prev = q;
            q = next;
        }
    q = prev;
    return q;
}

void display(node* first)
{
    //node* p = first;
    node* p = reverse(first);

    printf("The elements of the queue are:\n");

    
    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
}

int main()
{
    int n;
    printf("Enter numbers to push");

    node* first = (node*)malloc(sizeof(node));

    first->data = -1;
    first->link = NULL;

    while(n!=-1)
    {

        scanf("%d", &n);
        if(n!=-1)
            enqueue(first, n);
    }

    display(first);
}