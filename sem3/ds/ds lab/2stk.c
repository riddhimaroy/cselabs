#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 50

typedef struct
{
    char* item;
    int top1;
    int top2;
    int b1;
    int b2;
    int size;
}stack;

stack* create2s(int n)
{
    stack *s = (stack*)calloc(1, sizeof(stack));
    s->item = (char*)calloc(n*2, sizeof(char));
    s->b1 = -1;
    s->b2 = n -1;
    s->top1 = -1;
    s->top2 = n -1;
    s->size = 2*n;
}

int isEmpty1(stack *s)
{
    return(s->top1==-1);
}

int isFull1(stack *s)
{
    return(s->top1==s->size/2-1);
}

void pop1(stack *s)
{
    if(isEmpty1)
        printf("stack underflow");
    s->top1--;
}

void push1(stack*s, char x)
{
    if(isFull1)
        printf("stack overflow");
    s->top1++;
    s->item[s->top1] = x;
}

void display1(stack*s)
{
    printf("The stack is \n");
    for(int i=0; i<=s->top1; i++)
    {
        printf("%c", s->item[i]);
    }
}

int isEmpty2(stack *s)
{
    return(s->top2==s->b2);
}

int isFull2(stack *s)
{
    return(s->top1==s->size-1);
}

void pop2(stack *s)
{
    if(isEmpty2)
        printf("stack underflow");
    s->top2--;
}

void push2(stack*s, char x)
{
    if(isFull2)
        printf("stack overflow");
    s->top2++;
    s->item[s->top2] = x;
}

void display2(stack*s)
{
    printf("The stack is \n");
    for(int i=s->b2; i<=s->top2; i++)
    {
        printf("%c", s->item[i]);
    }
}

int main()
{
    int n;

    printf("What is the capacity of the stacks");
    scanf("%d", &n);

    stack *s = create2s(n);
    push1(s, 'a');
    push1(s, 'b');
    pop1(s);
    display1(s);
    push2(s, 'n');
    display2(s);

}


