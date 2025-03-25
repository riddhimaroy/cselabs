#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct 
{
    int data[MAX];
    int f;
    int r;
}dq;

void initialise(dq* q)
{
    q->f = -1; 
    q->r = -1;
}

int isEmpty(dq* q)
{
    return(q->r == -1);
}

int isFull(dq *q)
{
    return(q->r + 1)%MAX == q->f;
}

void enqR(dq *q, int x)
{
    if(isFull(q))
    {
        printf("nah");
        return;
    }

    if(isEmpty(q))
    {
        q->r = 0;
        q->f = 0;
        q->data[0] = x;
    }

    else
    {
        q->r = (q->r+1) % MAX;
        q->data[q->r] = x;
    }
}

void enqF(dq *q, int x)
{
    if(isFull(q))
    {
        printf("no");
        return;
    }

    if(isEmpty(q))
    {
        q->r = 0;
        q->f = 0;
        q->data[0] = x;
    }

    else
    {
        q->f = (q->f-1+MAX) % MAX;
        q->data[q->f] = x;
    }
}

int dqqF(dq *q)
{
    if(isEmpty(q))
    {
        printf("no");
        return;
    }

    int x = q->data[q->f];

    if(q->r == q->f)
    {
        initialise(q);
    }
    else
    {
        q->f = (q->f + 1)%MAX;
    }

    return x;
}

int dqqR(dq *q)
{
    if(isEmpty(q))
    {
        printf("no");
        return;
    }

    int x = q->data[q->r];

    if(q->r == q->f)
    {
        initialise(q);
    }

    else
    {
        q->r = (q->r+MAX-1) % MAX;
    }

    return x;
}