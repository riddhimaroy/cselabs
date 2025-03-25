#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* link;
}node; 

void insertwprev(node* prev, int x)
{
    node* new = (node*)malloc(sizeof(node));
    new->data = x;
    new->link = prev->link;
    prev->link = new;
}

void insertnode(node* prev, node* x)
{
    //node* new = (node*)malloc(sizeof(node));
    //new->data = x;
    x->link = prev->link;
    prev->link = x;
    printf("hey");
}

node* deletefromend(node *first)
{
    if (first == NULL || first->link == NULL)
    {
        printf("List is too short to delete from end\n");
        return NULL;
    }

    node* p = first;
    node* q = NULL;

    while(p->link != NULL)
    {
        q = p;
        p = p->link;
    }
    
    node* y = q;

    p = NULL;
    printf("hi");
    return p;
}

void sort(node *first)
{
    node* p = first;
    node* q = first;
    node* small = first;
    node *temp = first;

    for(p = first; p!= NULL; p=p->link)
    {
        small = p;
        for(q = p; q!= NULL; q=q->link)
        {
            if(q->data<p->data)
            small = q;
        }
        temp = q;
        q = p;
        p = temp;
    }
}

void display(node *front)
{
    printf("The contents of the linked list are: \n");
    node* p = front->link;
    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
}

void input(node *front, int n)
{
    node*p = front;
    int x;
    for(int i = 0; i<n; i++)
    {
        scanf("%d", &x);
        insertwprev(p, x);
        p = p->link;
    }
}

int main()
{
    int n1, n2, i;
    node *one = (node*)malloc(sizeof(node));
    node *two = (node*)malloc(sizeof(node));
    node *three = (node*)malloc(sizeof(node));
    one->link = NULL;
    two->link = NULL;
    three->link = NULL;
    printf("Enter number of elements in first linked list:\n");
    scanf("%d", &n1);
    input(one, n1);
    printf("Enter number of elements in second linked list:\n");
    scanf("%d", &n2);
    input(two, n2);

    sort(two);

    display(two);
    
    for(i=0; i<n1; i++)
    {
        node* w = deletefromend(one);
        insertnode(one, w);
    }

    // sort(two);

    // display(two);
}