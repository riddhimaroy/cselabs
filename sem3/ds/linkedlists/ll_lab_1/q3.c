//two lines are given in ascending order. merge them.

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* insert(node* head, int x)
{
    node* p = head;
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = NULL;

    if(head==NULL)
    {
        return new;
    }

    while(p->link != NULL)
    {
        p = p->link;
    }
    p->link = new;

    return head;
}

node* merge(node* h1, node* h2)
{
    node* p1 = h1;
    node* p2 = h2;
    node *mg = NULL;
    node* prev = NULL;

    while(p1 != NULL && p2 != NULL)
    {
        {
            if(p1->data <= p2->data)
            {
                mg = insert(mg, p1->data);
                p1 = p1->link;
            }

            else
            {
                mg = insert(mg, p2->data);
                p2 = p2->link;
            }
        }
    }

    while (p1 != NULL) {
        mg = insert(mg, p1->data);
        p1 = p1->link;
    }

    while (p2 != NULL) {
        mg = insert(mg, p2->data);
        p2 = p2->link;
    }

    return mg;
}

void display(node* head)
{
    node* p = head;
    if(head==NULL)
    {
        printf("no elements to show\n");
        return;
    }

    while(p!= NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
    
}

int main()
{
    node* h1 = NULL;
    node* h2  = NULL;
    int x, n;

    printf("enter what you want to do\n");

    while(1)
    {
        printf("1. enter in list 1\n2. enter in list 2\n3. display union\n4.exit\n\n");
        scanf("%d", &x);

        switch(x)
        {
        case 1: printf("\nenter number to be pushed\n");
                scanf("%d", &n);
                h1 = insert(h1, n);
                break;

        case 2: printf("\nenter number to be pushed\n");
                scanf("%d", &n);
                h2 = insert(h2, n);
                break;

        case 3: node *mg = merge(h1, h2);   
                display(mg);
                break;

        case 4: return 0;
        
        default: printf("invalid tf\n");
        }
    }
}