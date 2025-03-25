#include <stdio.h>
#include <string.h>
#define max_size 100
char stack[max_size][max_size];
int top=-1;
void push(char* item)
{
    strcpy(stack[++top],item);
}
int is_op(char symbol)
{
    if(symbol=='+' || symbol=='-' || symbol=='*' || symbol=='/')
        return 1;
    return 0;
}
void PostoIn(char exp[])
{
    char c, n2[100], n1[100], temp[100];
    int i, l=strlen(exp), rInd=-1;
    for(i=0; i<l; i++)
    {
        c=exp[i];
        if(c>='0' && c<='9' || c>='a' && c<='z' || c>='A' && c<='Z')
        {
            char a[] = {c,'\0'};
            push(a);
        }
        else
        {
            strcpy(n2, stack[top--]);
            strcpy(n1, stack[top--]);
            sprintf(temp,"(%s%c%s)", n1, c, n2);
            push(temp);
        }
    }
    strcpy(exp, stack[top]);
}
void brackets(char exp[100])
{
    int i;
    for(i=0; i<strlen(exp); i++)
    {
        if(exp[i]==')')
            exp[i]='(';
        else if (exp[i] == '(')
            exp[i] = ')';
    }
}
void PretoIn(char exp[])
{
    strrev(exp);
    PostoIn(exp);
    strrev(exp);
    brackets(exp);
}
int main()
{
    char exp[100];
    printf("Enter prefix:\n");
    gets(exp);
    PretoIn(exp);
    printf("Infix: %s", exp);
    return 0;
}
