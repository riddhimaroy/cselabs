// n people are there. every m-1 people skipped, 
//mth person gets killed. at the end who will be left

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
} node;

node* create(int n)
{
    node* head = NULL;
    int i;
    node* p = NULL;

    for(i=1; i<n+1; i++)
    {
        node* new = (node*)malloc(sizeof(node));
        new->data = i;
        new->link = head;
        
        if(head==NULL)
        {
            head = new;
            p = head;
        }
        else{
        p->link = new;
        p = p->link;
        }
        
    }

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

    printf("%d\n", p->data);
    p = p->link;

    while(p != head)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
}

void josephus(int m, node* head)
{
    node* p = head;
    while(head->link != head)
    {
        for(int i=0; i<m-2; i++)
        {
            p = p->link;
        }

        node* t = p->link;
        p->link = t->link;

        if(t==head)
        {
            head = head->link;
        }
       // p= p->link;
    }

    printf("\n%d", head->data);
}

int main()
{
    node* head = create(5);
    josephus(3, head);
}