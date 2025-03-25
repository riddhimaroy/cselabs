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

int prec(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

void intopost(char h[])
{
    char r[MAX], c;
    int i = 0, j = 0;
    stack *s = creates();

    while(h[i]!='\0')
    {
        c = h[i];

        if(isalnum(c))
        {
            r[j++] = c;
        }

        else if(c == '(')
        {
            push(s, c);
        }

        else if(c == ')')
        {
            while(s->item[s->top]!='(')
            {
                r[j++] = pop(s);
            }
            pop(s);
        }
        else
        {
            while(prec(c) <= prec(s->item[s->top]))
            {
                r[j++] = pop(s);
            }
            push(s, c);
        }
        i++;
    }

    while(!isEmpty(s))
    {
        r[j++] = pop(s);
    }

    printf("The postfix expression is \n");
    puts(r);
}

int main()
{
    char str[MAX];

    printf("Enter an infix expression: \n");
    scanf("%s", str);
    intopost(str);
}