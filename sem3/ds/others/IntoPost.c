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
void infixtopostfix(char exp[100])
{
    char result[100], stack[100];
    int resultInd=0, stackInd=-1, i, n = strlen(exp);
    for(i=0; i<n; i++)
    {
        char c=exp[i];
        if(c>='a' && c<='z' || c>='A' && c<='Z' || c>='0' && c<='9')
        {
            result[resultInd++]=c;
        }
        else if(c == '(')
        {
            stack[++stackInd]=c;
        }
        else if(c == ')')
        {
            while(stackInd >= 0 && stack[stackInd] != '(')
            {
                result[resultInd++] = stack[stackInd--];
            }
            stackInd--;
        }
        else
        {
            while(stackInd>=0 && (prec(c)<prec(stack[stackInd])) || (prec(c)==prec(stack[stackInd])) && assoc(c)=='L')
            {
                result[resultInd++] = stack[stackInd--];
            }
            stack[++stackInd]=c;
        }
    }
    while(stackInd>=0)
    {
        result[resultInd++]=stack[stackInd--];
    }
    result[resultInd]='\0';
    printf("%s", result);
}
int main()
{
    char exp[100];
    printf("Enter infix expression:\n");
    gets(exp);
    printf("Postfix expression: ");
    infixtopostfix(exp);
    return 0;
}
