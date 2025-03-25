#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct 
{
    int data[50];
    int f1;
    int r1;
    int b1;

    int size1;
    int f2;
    int r2;
    int size2;
    int b2;
}cq;

cq* createcq(cq *q, int n)
{
    if(n%2==1)
    {
        printf("not valid\n");
        return q;
    }

    q = (cq*)calloc(1, sizeof(cq));
    q->f1 = 0;
    q->r1 = 0;
    q->size1 = 0;
    q->b1 = n/2;

    q->f2 = n/2;
    q->r2 = n/2;
    q->size2 = 0;
    q->b2 = n;
    return q;
}

int isFull1(cq* q)
{
    return(q->size1==q->b1);
}

int isEmpty1(cq* q)
{
    return(q->size1==0);
}

void insert1(cq *q, int x)
{
    if(isFull1(q))
    {
        printf("stack overflow!");
    }
    else
    {
        q->data[q->r1] = x;
        q->r1 = (q->r1 + 1) % q->b1;
        q->size1++;
    }
}

void delete1(cq *q)
{
    if(isEmpty1(q))
    {
        printf("Stack underflow!");
    }
    else
    {
        q->data[q->f1] = 0;
        q->f1 =(q->f1 + 1)%q->b1;
        q->size1--;
    }
}

void display1(cq *q)
{
    printf("The elements of the first queue are: ");

    int i, c = q->f1;

    for(i=0; i<q->size1; i++)
    {
        printf("%d\n", q->data[c]);
        c = (c+1) % q->b1;
    }
}

int isFull2(cq* q)
{
    return(q->size2==q->b1);
}

int isEmpty2(cq* q)
{
    return(q->size2==0);
}

void insert2(cq *q, int x)
{
    if(isFull2(q))
    {
        printf("stack overflow!");
    }
    else
    {
        q->data[q->r2] = x;
        q->r2 = q->b1 + (q->r2 + 1) % q->b1;
        q->size2++;
    }
}

void delete2(cq *q)
{
    if(isEmpty2(q))
    {
        printf("Stack underflow!");
    }
    else
    {
        q->data[q->f2]=0;
        q->f2 =(q->f2 + 1) % q->b1 + q->b1;
        q->size2--;
    }
}

void display2(cq *q)
{
    printf("The elements of the second queue are: ");

    int i, c = q->f2;

    for(i=0; i<q->size2; i++)
    {
        printf("%d\n", q->data[c]);
        c = (c+1) % q->b1 + q->b1;
    }
}

int main()
{
    int m, n;

    printf("Enter total number of elements in one array\n");
    scanf("%d", &m);
    
    cq *q = createcq(q, m);

    insert1(q, 8);
    insert1(q, 9);
    insert1(q, 5);
    delete1(q);
    display1(q);

    insert2(q, 8);
    insert2(q, 7);
    insert2(q, 6);
    delete2(q);
    display2(q);

}