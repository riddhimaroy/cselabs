#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct 
{
    int data[MAX];
    int front;
    int rear;
}dq;

void initialise(dq* p)
{
    p->rear = -1;
    p->front = -1;
}

int isEmpty(dq* p)
{
    return(p->rear == -1);
}

int isFull(dq *p)
{
    return((p->rear+1) % MAX == p->front);
}

void enqR(dq* p, int x)
{
    if(isFull(p))
    {
        printf("queue is full");
        return;
    }
    else if(isEmpty(p))
    {
        p->front = 0;
        p->rear = 0;
        p->data[0] = x;
    }
    else
    {
        p->rear = (p->rear+1) % MAX;
        p->data[p->rear] = x;
    }
}

void enqF(dq* p, int x)
{
    if(isFull(p))
    {
        printf("queue is full");
        return;
    }
    else if(isEmpty(p))
    {
        p->front = 0;
        p->rear = 0;
        p->data[0] = x;
    }
    else
    {
        p->front = (p->front - 1 + MAX) % MAX;
        p->data[p->front] = x;
    }
}

int deqF(dq *p)
{
    int x;
    if(isEmpty(p))
    {
        printf("no elements to be deleted");
        return 0;
    }
    else if(p->front==p->rear)
    {
        x = p->data[p->front];
        initialise(p);
    }
    else
    {
        x = p->data[p->front];
        p->front = (p->front + 1)%MAX;
    }
    return x;
}

int deqR(dq *p)
{
    int x;
    if(isEmpty(p))
    {
        printf("no elements to be deleted");
        return 0;
    }
    else if(p->front==p->rear)
    {
        x = p->data[p->front];
        initialise(p);
    }
    else
    {
        x = p->data[p->rear];
        p->rear = (p->front -1 + MAX) % MAX;
    }
    return x;
}
