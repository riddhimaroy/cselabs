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
        printf("kys im taken\n");
    else
    {
        s->top++;
        s->item[s->top] = c;
    }
}

char pop(stack *s)
{
    if(isEmpty(s))
        printf("kys im single\n");
    char c = s->item[s->top];
    s->top--;
    return c;
}

char* rev(char h[])
{
    int n, i; 

    n = strlen(h); 
    
    char* r = (char*)calloc(MAX, sizeof(char));

    for (i=0; i<n; i++)
    {
        r[n-1-i] = h[i];
    }

    for(i=0; i<n; i++)
    {
        if(r[i]=='(')
            r[i] = ')';
        else if(r[i] == ')')
            r[i] = '(';
    }
    r[n] ='\0';
    return r;
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

char* intopost(char h[])
{
    char c;
    int i = 0, j = 0;
    stack *s = creates();

    char* r = (char*) calloc(MAX, sizeof(char));

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

    return r;
}

void intopre(char str[])
{
    char res[MAX];

    strcpy(res, rev(str));
    strcpy(res, intopost(res));
    strcpy(res, rev(res));
    puts(res);
}

int main()
{
    char str[MAX];

    printf("Enter an infix expression: \n");
    scanf("%s", str);
    intopre(str);
}
