//you're given a singly sorted list. delete nodes so
//that there are no duplicates
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* insert(node* head, int x)
{
    node*p = head;
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = NULL;

    if(head==NULL)
        return new;

    while(p->link != NULL)
    {
        p = p->link;
    }
    p->link = new;
    return head;
}

void display(node* head)
{
    node *p = head;

    if(head==NULL)
    {
        printf("\nno elements to show\n");
        return;
    }

    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
}

node* deldup (node *head)
{
    node*p = head;
    

    if(head == NULL)
        return NULL;

    while(p->link != NULL)
    {
        if(p->data == p->link->data)
        {
            node*x = p->link;
            p->link =x->link;
        }
        else
        {
        p = p->link;
        }
    }

    return head;
}

int main()
{
    node* head = NULL;
    int x, n;

    printf("enter what you want to do\n");

    while(1)
    {
        printf("1. insert\n\n3. display\n4.exit\n\n");
        scanf("%d", &x);

        switch(x)
        {
        case 1: printf("\nenter number to be pushed\n");
                scanf("%d", &n);
                head = insert(head, n);
                break;

        // case 2: head = dq(head);
        //         break;

        case 3: node* del = deldup(head);
                display(head);
                break;

        case 4: return 0;
        
        default: printf("invalid tf\n");
        }
    }
}