// implement an ascending priority queue

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct
{
    int data[MAX];
    int f;
    int r;
    int s;
}apq;

apq* create(apq* q)
{
    q = (apq*)calloc(1, sizeof(apq));
    q->f = -1;
    q->r = -1;
    q->s = 0;
    printf("hi");

    return q;
}

int isEmpty(apq* q)
{
    return(q->s==0);
}

int isFull(apq *q)
{
    return(q->s==MAX);
}

void insert(apq* p, int x)
{
    if(isFull(p))
    {
        printf("cannot enter more elements");
        return;
    }

    if(p->f==-1)
		p->f=0;

    p->r = (p->r+1)%MAX;
    p->data[p->r] = x;
    p->s++;
    printf("hi");
}

int delete(apq *q)
{
    int small = q->data[q->f];
    int in = q->f;
    int c = q->f;
    int i;

    for(i = c; i<q->r; i++)
    {
        if(small<q->data[i])
        {
            small = q->data[i];
            in = i;
        }
    }

    for(i= in; i<q->r; i++)
    {
        q->data[i] = q->data[i+1];
    }
    q->r--;
    q->s--;
    return small;
}

void display(apq *q)
{
    int i;

    printf("The elements of queue are\n");

    for(i=0; i<q->s; i++)
    {
        int x = q->f + i;
        printf("%d\n", q->data[i]);
    }
}

int main()
{
    apq* q;
    q = create(q);

    insert(q, 8);
    insert(q, 2);
    insert(q, 3);
    insert(q, 10);
    insert(q, 5);
    delete(q);
    display(q);
}