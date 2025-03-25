#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* insertbyprev(node* prev, int x)
{
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = prev->link;
    prev->link = new;

    return new;
}

void insertbyindex(node* first,int n, int x)
{
    int i;
    node* p = first;

    for(i=0; i<n-1; i++)
    {
        p = p->link;
    }

    node* new =(node*)malloc(sizeof(node));
    new->data = x;
    new->link = p->link;
    p->link = new;
}

void deletebyprev(node* prev)
{
    node* new = prev->link;
    prev->link = new->link;
}

void deletebyele(node* first, node* x)
{
    node* p = first;

    while(p->link!= x)
    {
        if(p->link==NULL)
        {
            printf("Element not found");
            return;
        }

        p = p->link;
    }

    p->link = x->link;
    free(x);
}

void deletebyindex(node *first, int x)
{
    int i;
    node* p = first;

    for(i=0; i<x-1; i++)
    {
        p = p->link;
    }

    node* q = p->link;
    p->link = q->link;
}

void display(node* first)
{
    node* p = first;
    p=p->link;

    printf("The elements of the linked list are:\n");

    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
}

int main()
{
    node* head = (node*)malloc(sizeof(node));
    node *new = insertbyprev(head, 36);
    
    insertbyindex(head, 2, 9);
    //deletebyele(head, new);
    //deletebyindex(head, 2);
    deletebyprev(head);
    display(head);
}

node* reverse(node* head)
{
    node* prev, *next;

    while(head!=NULL)
    {
        next = head->link;
        head->link = prev;
        prev = head;
        head = next;
    }
    head = prev;
    return head;
}

