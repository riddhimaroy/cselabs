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
   // s->item = (char**)calloc(MAX, sizeof(char*));
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

char* rev(char h[])
{
    int n, i; 

    n = strlen(h); 
    
    char* r = (char*)calloc(MAX, sizeof(char));

    for (i=0; i<n; i++)
    {
        r[n-1-i] = h[i];
    }

    r[n] ='\0';
    return r;
}

void preftopost(char* str)
{
    str = strcpy(str, rev(str));
    int n, i, k;
    stack *s = creates();

    n = strlen(str);

    for (k=0; k<n; k++)
    {
        char c = str[k];
        if(isalnum(c))
        {
            char* w = (char*)calloc(2, sizeof(char));
            w[0] = c;
            w[1] = '\0';
            push(s, w);
            puts(w);
            printf(" Pushed1\n");
        }
        else if(isOper(c))
        {
            int j = 0, l;
            char* x1 = pop(s);
            char* x2 = pop(s);
            l = strlen(x1) + strlen(x2) + 3;
            char* res = (char*)calloc(l, sizeof(char));

            strcpy(res, x1);
            strcat(res, x2);
            res[strlen(x1)+strlen(x2)]=c;
            res[strlen(x1) + strlen(x2) + 1] = '\0';
            push(s, res);
            puts(res);
            printf(" Pushed2\n");
        }
    }

    printf("%s", s->item[s->top]);
}

int main()
{
    char str[MAX];
    printf("Enter a prefix expression: \n");
    scanf("%s", str);
    preftopost(str);
}

