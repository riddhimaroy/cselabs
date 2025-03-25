// Implement a circular queue of Strings using structures. Include functions insertcq,
//deletecq and displaycq.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct 
{
    char* data[50];
    int f;
    int r;
    int size;
}cq;

cq* createcq(cq *q)
{
    q = (cq*)calloc(1, sizeof(cq));
    q->f = 0;
    q->r = 0;
    q->size = 0;

    return q;
}

int isFull(cq* q)
{
    return(q->size==MAX-1);
}

int isEmpty(cq* q)
{
    return(q->size==0);
}

void insert(cq *q, char s[])
{
    if(isFull(q))
    {
        printf("stack overflow!");
    }
    else
    {
        q->data[q->r] = (char*)calloc(strlen(s)+1, sizeof(char));
        strcpy(q->data[q->r], s);
        q->r = (q->r + 1) % MAX;
        q->size++;
    }
}

void delete(cq *q)
{
    if(isEmpty(q))
    {
        printf("Stack underflow!");
    }
    else
    {
        free(q->data[q->f]);
        q->f =(q->f + 1)%MAX;
        q->size--;
    }
}

void display(cq *q)
{
    printf("The elements of the queue are: ");

    int i, c = q->f;

    for(i=0; i<q->size; i++)
    {
        printf("%s\n", q->data[c]);
        c = (c+1) % MAX;
    }
}

int main()
{
    cq *q = createcq(q);
    insert(q, "ṇhey");
    insert(q, "baby");
    insert(q, "girl");
    delete(q);
    display(q);
}