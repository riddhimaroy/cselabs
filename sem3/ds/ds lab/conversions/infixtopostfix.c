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

stack* creates(stack *s)
{
    s = (stack *)calloc(1, sizeof(stack));
    s->item = (char*)calloc(MAX, sizeof(char));
    s->top = -1;
    return s;
}

int isEmpty(stack *s)
{
    return (s->top==-1);
}

int isFull(stack *s)
{
    return (s->top==MAX-1);
}

void push(stack *s, char c)
{
    if(isFull(s))
    {
        printf("Stack overflow!!");
    }
    else
    {
        (s->top)++;
        s->item[s->top] = c;
    }
}

char pop(stack *s)
{
    if(isEmpty(s))
    {
        printf("Stack underflow!!");
    }
    else{
        char c = s->item[s->top];
        (s->top)--;
        return c;
    }
}

int prec(char c)
{
    if (c=='^')
        return 3;
    if( c == '*' || c == '/')
        return 2;
    if( c=='+' || c =='-')
        return 1;
    return 0;
}

void intopost(char in[])
{
    int n, i=0, j=0; 
    char c, x; 
    stack* s = creates(s);
    n = strlen(in);
    char res[n];

    while (in[i]!='\0')
    {
        c = in[i];

        if(isalnum(c))
        {
            res[j] = c;
            j++;
        }
        else if(c == '(')
        {
            push(s, c);
        }

        else if(c ==')')
        {
            while(s->item[s->top]!='(')
            {
                res[j++]=pop(s);
            }
            x = pop(s);
        }
        else
        {
            while(prec(c)<=prec(s->item[s->top]))
            {
                res[j++] = pop(s);
            }
            push(s,c);
        }
        i++;
    }

    while (!isEmpty(s))
        {
            res[j++] = pop(s);
        }

        res[j] = '\0'; 
        puts(res);
}

int main()
{
    char str[MAX];
    printf("Enter an infix expression: \n");
    scanf("%s", str);
    intopost(str);
}

