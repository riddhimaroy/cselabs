#include <stdio.h>
#include <string.h>
int prec(char c)
{
    if(c=='^')
        return 3;
    else if(c=='*'||c=='/')
        return 2;
    else if(c=='+'||c=='-')
        return 1;
    else
        return 0;
}
char assoc(char c)
{
    if(c=='^')
        return 'R';
    return 'L';
}
void getpostfix(char exp[100])
{
    char stack[100];
    int ind=0, stackInd=-1, i, n = strlen(exp);
    for(i=0; i<n; i++)
    {
        char c=exp[i];
        if(c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9')
        {
            exp[ind++]=c;
        }
        else if(c == '(')
        {
            stack[++stackInd]=c;
        }
        else if(c == ')')
        {
            while(stackInd >= 0 && stack[stackInd] != '(')
            {
                exp[ind++] = stack[stackInd--];
            }
            stackInd--;
        }
        else
        {
            while(stackInd>=0 && (prec(c)<prec(stack[stackInd])) || (prec(c)==prec(stack[stackInd])) && assoc(c)=='L')
            {
                exp[ind++] = stack[stackInd--];
            }
            stack[++stackInd]=c;
        }
    }
    while(stackInd>=0)
    {
        exp[ind++]=stack[stackInd--];
    }
    exp[ind]='\0';
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
void infixtoprefix(char exp[100])
{
    strrev(exp);
    brackets(exp);
    getpostfix(exp);
    strrev(exp);
}
int main()
{
    char exp[100];
    printf("Enter infix expression:\n");
    gets(exp);
    infixtoprefix(exp);
    printf("Prefix expression: %s", exp);
    return 0;
}
