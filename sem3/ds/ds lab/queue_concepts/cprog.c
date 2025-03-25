#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct
{
    int element;
}Q;

Q CQ[MAX];

int IsFull(int front, int rear)
{
    if((rear+1)%MAX==front)
    return 1;
    else
    return 0;
}

void ADDCQ(int *rear, int item)
{
    *rear = (*rear+1) %MAX;
    CQ[*rear ].element = item;
}

int isEmpty(int front, int rear)
{
    if(rear == front)
    return 1;
    else
    return 0;
}

int DELCQ(int* front)
{
    int d;
    *front = (*front +1) % MAX;
}

int main()
{
    int chc, f;
    switch(ch)
    {
        case 1:
            if(f == )
    }
}