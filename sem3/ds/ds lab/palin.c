#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* item;
    int top;
}stack;

int isFull(stack *s)
{
    return(s->top==29);
}

int isEmpty(stack *s)
{
    return(s->top==-1);
}

stack* create(stack *s)
{
    s = (stack*)calloc(1, sizeof(stack));
    s->item = (char*)calloc(30, sizeof(char));
    s->top =-1;
    return s;
}

void push(stack *s, char x)
{
    if(isFull(s))
        printf("Stack overflow!");
    else
    {
        s->top++;
        s->item[s->top]=x;
    }
}

char pop(stack *s)
{
    char t;
    if(isEmpty(s))
        printf("Stack underflow!");
    else{
        t = s->item[s->top];
        s->top--;
    }
    return t;
}

void display(stack *s)
{
    for(int i=s->top; i>=0; i--)
    //for(int i=0; i<5; i++)
    {
        printf("%c", s->item[i]);
    }
}

int isPalin(stack *s)
{
    stack *temp = create(temp);
    stack *rev = create(rev);

    temp = s;
    int m = s->top;
    int i;
    
    for (i=0; i<=m; i++)
    {
        char v = pop(temp);
        push(rev, v);
    }
    
    for (int i = 0; i <= s->top; i++) {
        if (s->item[i] != rev->item[i]) {
            return 0;  
        }
    }

    return 1;
}

stack* strk(char str[])
{
    stack* s = create(s);
    int n = strlen(str);
    for(int i=0; i<n; i++)
    {
        push(s, str[i]);
    }
    printf("\n");
    return s;
}

int main()
{
    char str[20];

    printf("Enter the word\n");
    scanf("%s", str);
    stack *s = strk(str);
if(isPalin)
printf("Word is palindrome");
else
printf("Word is not a palindrome");
}