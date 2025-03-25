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

void posttoin(char str[])
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
            // puts(w);
            // printf("Push1\n");
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

    printf("The infix expression is: \n");
    puts(s->item[s->top]);
}

int main()
{
    char str[MAX], x[10];
    printf("Enter a postfix expression: \n");
    scanf("%s", str);
    posttoin(str);

}