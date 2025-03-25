// Perform UNION and INTERSECTION set operations on 
// singly linked lists with
// and without header node.

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
}node;

node* insert(node* head, int x)
{
    node*p = head;
    node *new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = NULL;

    if(head == NULL)
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

node* unions(node* h1, node* h2)
{
    node *uh = NULL;

    node* p1 = h1;
    node* p2 = h2;
    int f;

    while(p1 != NULL)
    {
        p2 = h2;
        f=0;
        while(p2 != NULL)
        {
            if(p1->data == p2->data)
            {
                f=1;
                break;
            }
            
            p2 = p2->link;
        }

        if(f==0)
        {
            uh = insert(uh, p1->data);
        }
        
        p1 = p1->link;
    }

    p2 = h2;

    while(p2 != NULL)
    {
        uh = insert(uh, p2->data);
        //remember to put uh = insert always bc the head needs to
        //be kept updating
        p2 = p2->link;
    }

    return uh;
}

node* intersection(node* h1, node* h2)
{
    node* p1 = h1;
    node* p2 = h2;
    node* is = NULL;

    while(p1 != NULL)
    {
        p2 = h2;
        int f = 0;

        while(p2 != NULL)
        {
            if(p1->data == p2->data)
            {
                is = insert(is, p1->data);
            }
            p2 = p2->link;
        }
        p1 = p1 -> link;
    }
    return is;
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

        case 3: node *uh = unions(h1, h2);
                node *is = intersection(h1, h2);   
                display(is);
                break;

        case 4: return 0;
        
        default: printf("invalid tf\n");
        }
    }
}