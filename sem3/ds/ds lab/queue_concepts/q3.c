#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct 
{
    int ele[MAX];
    int top;
}stack;

stack* creates(stack* s)
{
    s = (stack*)calloc(1, sizeof(stack));
    s->top = -1;
    return s;
}

int isFull(stack *s)
{
    return(s->top == MAX - 1);
}

int isEmpty(stack *s)
{
    return (s->top == -1);
}

void push(stack *s, int x)
{
    if(isFull(s))
    {
        printf("Stack overflow!!");
    }
    else
    {
        s->top++;
        s->ele[s->top] = x;
    }
}

int pop(stack *s)
{
    if(isEmpty(s))
    {
        printf("Stack underflow!!");
    }
    else
    {
        int n = s->ele[s->top];
        s->top--;
        return n;
    }
}

void insert(stack* ins, stack* outs, int x)
{
    push(ins, x);
}

void delete(stack* ins, stack* outs)
{
    while(!isEmpty(ins))
    {
        push(outs, pop(ins));
    }

    int y = pop(outs);

    while(!isEmpty(outs))
    {
        push(ins, pop(outs));
    }
}

void display(stack *s)
{
    printf("The elements of the stack are: \n");

    for(int i=0; i<=s->top; i++)
    {
        printf("%d\n", s->ele[s->top-i]);
    }
}

int main()
{
    stack* ins; stack* outs;
    ins = creates(ins);
    outs = creates(outs);

    insert(ins, outs, 1);
    insert(ins, outs, 2);
    insert(ins, outs, 3);
    insert(ins, outs, 4);
    delete(ins, outs);
    display(ins);
}
