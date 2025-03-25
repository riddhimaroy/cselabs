#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct 
{
    int data[MAX];
    int front;
    int rear;
}sq;

sq* createq(sq* q)
{
    q = (sq*)calloc(1, sizeof(sq));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(sq* q)
{
    return(q->front>q->rear);
}

int isFull(sq* q)
{
    return(q->rear == MAX - 1);
}

void insert(sq *q, int x)
{
    if(isFull(q))
    {
        printf("Queue overflow");
        return;
    }
    q->rear++;
    q->data[q->rear] = x;
}

int delete(sq *q)
{
    if(isEmpty(q))
    {
        printf("Queue underflow!!");
        return 0;
    }
    int x = q->front;
    q->front++;

    return x;
}
