#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 50

typedef struct 
{
    char* item[MAX];
    int top;
}stack;

stack* creates()
{
    stack *s = (stack *)calloc(1, sizeof(stack));
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

void push(stack *s, char* c)
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

char* pop(stack *s)
{
    if(isEmpty(s))
    {
        printf("Stack underflow!!");
    }
    else{
        char* c = s->item[s->top];
        (s->top)--;
        return c;
    }
}

char* rev(char c[])
{
    int n = strlen(c);
    char *r = (char*)calloc(MAX, sizeof(char));
    int i;

    for(i=0;  i<n; i++)
    {
        r[n-i-1] = c[i];
    }
    for(int i=0;  i<n; i++)
    {
        if(r[i]=='(')
        r[i] = ')';
        else if(r[i]==')')
        r[i] = '(';
    }
    r[n] ='\0';

    return r;
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

char* posttoin(char str[])
{
    int n, i;
    stack *s = creates();
    n = strlen(str);

    for (i=0; i<n; i++)
    {
        char c = str[i];
        if(isalnum(c))
        {
            char* w = (char*)calloc(2, sizeof(char));
            w[0] = c;
            w[1] = '\0';
            push(s, w);
        }

        if(isOper(c))
        {
            int l;

            char* x2 = pop(s);

            char* x1 = pop(s);

            l = strlen(x1) + strlen(x2) + 5;
            char* res = (char*)calloc(l, sizeof(char));
            
            res[0] = '(';
            strcat(res,x1);
            res[strlen(x1)+1] = c;
            strcat(res, x2);
            strcat(res, ")");
            push(s, res);

        }
    }
    return s->item[s->top];
}

void pretoin(char str[])
{
    str = rev(str);
    str = posttoin(str);
    str = rev(str);

    printf("The prefix form of the expression is: \n");
    puts(str);
}

int main()
{
    char str[MAX];
    printf("Enter a prefix expression: \n");
    scanf("%s", str);
    pretoin(str);
} 