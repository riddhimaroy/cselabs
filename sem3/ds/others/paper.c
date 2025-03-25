#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct
{
    int ele[MAX];
    int f;
    int r;
}q;

void insert(q* qq, int x)
{
    if(isFull(qq))
        return;
    
    qq->r++;
    qq->ele[qq->r] = x;
}

int del(q* qq)
{
    if(isEmpty(qq))
        return;

    int x = qq->ele[qq->f];
    qq->f++;
    return x;
}