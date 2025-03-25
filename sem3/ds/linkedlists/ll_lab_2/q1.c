//write a menu driven program to implement
// doubly linked list without header node 
// to insert into and delete from both the sides.

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
    struct node* prev;
}node;

node* insertbeg(node* head, int x)
{
    node* p = head;
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->next = NULL;
    new->prev = NULL;

    if(head==NULL)
    {
        return new;
    }

    new->next = head;
    head->prev = new;
    head = new;
    return head;
}

node* insertend(node* head, int x)
{
    node* p =  head;
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->prev = NULL;
    new->next = NULL;

    if(head==NULL)
        return new;

    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = new;
    new->prev = p;
    return head;
}

node* deletebeg(node* head)
{
    node* x = head->next;
    x->prev = NULL;
    head = x;
    return head;
}

node *deleteend(node *head)
{
    node* p = head;

    while(p->next->next != NULL)
    {
        p = p->next;
    }

    node* x = p->next;
    free(x);

    p->next = NULL;
    return head;
}

void display(node* head)
{
    if(head==NULL)
    {
        printf("nothing to show\n");
        return;
    }

    node*p = head;

    while(p!=NULL)
    {
        printf("%d\n", p->data);
        p = p->next;
    }
}

int main()
{
    node* head  = NULL;
    head = insertend(head, 5);
    head = insertend(head, 6);
    head = insertbeg(head, 2);

    head = deletebeg(head);
    head = deleteend(head);
    display(head);
}