#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* item;
    int top;
}stack;

int isFull(stack *s)
{
    return(s->top==9);
}

int isEmpty(stack *s)
{
    return(s->top==-1);
}

stack* create(stack *s)
{
    s = (stack*)calloc(1, sizeof(stack));
    s->item = (int*)calloc(10, sizeof(int));
    s->top =-1;
    return s;
}

void push(stack *s, int x)
{
    if(isFull(s))
        printf("Stack overflow!");
    else
    {
        s->top++;
        s->item[s->top]=x;
       // printf("%d", s->top);
    }
}

void pop(stack *s)
{
    if(isEmpty(s))
        printf("Stack underflow!");
    else{
        s->top--;
    }
}

void display(stack *s)
{
    for(int i=s->top; i>=0; i--)
    //for(int i=0; i<5; i++)
    {
        printf("%d", s->item[i]);
    }
}

int main()
{
    int n, k; stack *s;
    printf("Enter the decimal number\n");
    scanf("%d", &n);

    s = create(s);

    while(n>0)
    {
        k = n%2;
        push(s, k);
        n = n/2;
    }

    printf("The binary number is\n");
    display(s);
}

