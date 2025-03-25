#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 50

typedef struct
{
    char* item;
    int top;
}stack;

stack* creates()
{
    stack *s = (stack*)calloc(1, sizeof(stack));
    s->item = (char*)calloc(MAX, sizeof(char));
    s->top = -1;
    return s;
}

int isEmpty(stack *s)
{
    return(s->top==-1);
}

int isFull(stack *s)
{
    return(s->top==MAX-1);
}

void push(stack* s, char c)
{
    if(isFull(s))
        printf("kys im taken");
    else
    {
        s->top++;
        s->item[s->top] = c;
    }
}

char pop(stack *s)
{
    if(isEmpty(s))
        printf("kys im single");
    char c = s->item[s->top];
    s->top--;
    return c;
}

int isOper(char c)
{
    if(c == '+')
        return 1;
    if(c == '-')
        return 1;
    if(c == '*')
        return 1;
    if(c == '/')
        return 1;
    if(c == '^')
        return 1;
    return 0;
}

int operate(int x1, int x2, char c)
{
    if(c == '+')
    {
        return (x1 + x2);
    }
    if(c == '-')
    {
        return (x1 - x2);
    }
    if(c == '*')
    {
        return (x1 * x2);
    }
    if(c == '/')
    {
        return (x1 / x2);
    }
    if(c == '^')
    {
        return (x1 ^ x2);
    }
}

void prefeval (char h[])
{
    int i=0;
    stack *s = creates();
    int n = strlen(h);

    //while(h[i] != '\0')
    for(i=n-1; i>=0; i--)
    {
        char c = h[i];

        if(isdigit(c))
        {
            c = (int) c - 48;
            push(s, c);
        }

        else if(isOper(c))
        {
            int x2 = pop(s);
            int x1 = pop(s);
            int y = operate(x1, x2, c);
            push(s, y); 
        }
        else("hey");
    }

    printf("The evaluated expression is %d", s->item[s->top]);
}

int main()
{
    char str[MAX];

    printf("Enter a prefix expression: \n");
    scanf("%s", str);

    prefeval(str);
}
