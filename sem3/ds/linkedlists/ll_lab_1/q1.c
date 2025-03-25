// Implement a queue using singly linked list without header node

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* enq(node* head, int x)
{
    node *p = head;
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = NULL;

    if(head==NULL)
    {
        return new;
    }

    else
    {
        while(p->link != NULL)
        {
            p = p->link;
        }
        p->link = new;
        return head;
    }
}

node* dq(node* head)
{
    node*p = head;
    if(head==NULL)
    {
        printf("queue is empty\n");
        return head;
    }
    else if(head->link == NULL)
    {
        head = NULL;
    }
    else
    {
        node* new = head;
        head = head->link;
        return head;
    }
}

void display(node* head)
{
    node* p = head;

    if(head==NULL)
    {
        printf("no elements\n");
    }

    else
    {
        printf("the elements of the queue are: \n");

        while(p != NULL)
        {
            printf("%d\n", p->data);
            p = p->link;
        }
    }
}

int main()
{
    node* head = NULL;
    int x, n;

    printf("enter what you want to do\n");

    while(1)
    {
        printf("1. enqueue\n2. dequeue\n3. display\n4.exit\n\n");
        scanf("%d", &x);

        switch(x)
        {
        case 1: printf("\nenter number to be pushed\n");
                scanf("%d", &n);
                head = enq(head, n);
                break;

        case 2: head = dq(head);
                break;

        case 3: display(head);
                break;

        case 4: return 0;
        
        default: printf("invalid tf\n");
        }
    }
}