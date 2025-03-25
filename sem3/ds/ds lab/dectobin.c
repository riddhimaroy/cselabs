// #include <stdio.h>
// #include <stdlib.h>
// #define MAX 20

// typedef struct 
// {
//     int data[MAX];
//     int top;
// }stack;

// stack* creates(stack* s)
// {
//     s = (stack*)malloc(sizeof(stack));
//     s->top = -1;
//     return s;
// }

// int isFull(stack *s)
// {
//     return (s->top == MAX -1);
// }

// int isEmpty(stack *s)
// {
//     return (s->top == -1);
// }

// void push(stack*s, int x)
// {
//     if(isFull(s))
//     {
//         printf("stack overflow !!\n");
//         return;
//     }
//     s->top++;
//     s->data[s->top] = x;
// }

// int pop(stack *s)
// {
//     if(isEmpty(s))
//     {
//         printf("stack underflow !!\n");
//         return 0;
//     }

//     int x = s->data[s->top];
//     s->top--;
//     return x;
// }

// void display(stack *s)
// {
//     while(!isEmpty(s))
//     {
//         printf("%d", pop(s));
//     }
// }

// stack* dectobin(int x)
// {
//     stack *s = creates(s);
//     while(x>0)
//     {
//         push(s, x%2);
//         x = x/2;
//     }
//     return s;
// }

// int main()
// {
//     stack *s = dectobin(10);
//     display(s);
// }










#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct 
{
    int data[MAX];
    int top;
}stack;

stack* creates(stack* s)
{
    s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    return s;
}

int isFull(stack *s)
{
    return (s->top == MAX -1);
}

int isEmpty(stack *s)
{
    return (s->top == -1);
}

void push(stack*s, int x)
{
    if(isFull(s))
    {
        printf("stack overflow !!\n");
        return;
    }
    s->top++;
    s->data[s->top] = x;
}

int pop(stack *s)
{
    if(isEmpty(s))
    {
        printf("stack underflow !!\n");
        return 0;
    }

    int x = s->data[s->top];
    s->top--;
    return x;
}

void display(stack *s)
{
    while(!isEmpty(s))
    {
        printf("%d ", pop(s));
    }
}

stack* kdel(stack *s, int k);

//Given an array arr with n elements and a number k, k<n. The task is to delete k
//elements which are smaller than next element (i.e., we delete arr[i] if arr[i] <
//arr[i+1]) or become smaller than next because next element is deleted. Example:
//Input: arr[] = {20, 10, 25, 30, 40}, k = 2
//Output: 25 30 40

int main()
{
    stack* a = creates(a);

    push(a, 40);
    push(a, 30);
    push(a, 25);
    push(a, 10);
    push(a, 20);

    stack *b = kdel(a, 2);
    display(b);
}

stack* kdel(stack*s, int k)
{
    int x1, x2;
    int n = 0;
    stack *b = creates(b);

    while(n<k)
    {
        x1 = pop(s);
        x2 = pop(s);
        push(s, x2);
        push(s, x1);
        if(x1<x2)
        {
            x1 = pop(s);
            x2 = pop(s);
            push(s, x2);
            n++;
        }

        else
        {
            x1 = pop(s);
            x2 = pop(s);
            push(s, x1);
            x1 = pop(s);
            push(b, x1);
        }
    }

    while(!isEmpty(b))
    {
        push(s, pop(b));
    }

    return s;
}