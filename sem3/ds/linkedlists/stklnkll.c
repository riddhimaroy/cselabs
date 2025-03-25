#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* insertNode(node *prev, int x)
{
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = prev->link;
    prev->link = new;
   
    return new;
}

void deleteNode(node *tbd, node *head)
{
    node *p = head;
    if(p==tbd)
    {
        p = p->link;
    }
    else
    {
        while(p->link != tbd)
        {
            p = p->link;
            if (p == NULL) 
            return;
        }

        p->link = tbd->link;
        free(tbd);
    }
}

void display(node* head)
{
    node *p = (node*)malloc(sizeof(node));
    p = head;

    while(p->link!=NULL)
    {
        p = p->link;
        printf("%d\n", p->data);
    }
    printf("\n");
}

void push(node *head, int x)
{
    node *p = head;

    while(p->link!=NULL)
    {
        p=p->link;
    }
    
    insertNode(p, x);
    
}

node* pop(node* head)
{
    node *p = head;

    while(p->link!=NULL)
    {
        p=p->link;
    }

    node* x = p->link;
    //p->link = NULL;
    deleteNode(p, head);
    return x;
}

int main()
{
    node *head = (node*)malloc(sizeof(node));
    head->data = 0;
    head->link = NULL;
    node* a = insertNode(head, 1);
    node *b = insertNode(a, 2);
    node* c = insertNode(b, 3);
    push(head, 6);
    pop(head);

    display(head);
}