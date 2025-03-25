#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct 
{
    char* ele[MAX];
    int f;
    int r;
    int s;
}cq;

cq* createcq(cq* q)
{
    q = (cq*)malloc(sizeof(cq));
    q->f = 0;
    q->r = 0;
    q->s = 0;
}

int isFull(cq *q)
{
    return (q->s==MAX-1);
}

int isEmpty(cq *q)
{
    return (q->s==0);
}

void enq(cq* q, char x[])
{
    q->ele[q->r] = (char*)calloc(strlen(x)+1, sizeof(char));
    strcpy(q->ele[q->r], x);
    q->r = (q->r + 1) % MAX;
    q->s++;
}

char* dq(cq *q)
{
    if(isEmpty(q))
    {
        printf("nothing\n");
        return "no";
    }

    char w[20];
    strcpy(w, q->ele[q->f]);
    q->f = (q->f+1) % MAX;
    q->s--;
    return w;
}

void display(cq* q)
{
    int i, c = q->f;

    for(i = 0; i<q->s; i++, c++)
    {
        printf("%s\n", q->ele[c]);
    }
}

int main()
{
    cq *q = createcq(q);
    dq(q);
    enq(q, "ṇhey");
    enq(q, "baby");
    enq(q, "girl");
    //printf("%s", dq(q));
    display(q);
}