#include <stdio.h>
#include <string.h>
#define max_size 100
int stack[max_size];
int top=-1;
void push(int item)
{
    if(top>=max_size-1)
    {
        printf("Stack Overflow\n");
    }
    stack[++top]=item;
}
int pop()
{
    if(top<0)
    {
        printf("Stack Underflow\n");
    }
    int item = stack[top--];
    return item;
}
int is_op(char symbol)
{
    if(symbol=='+' || symbol=='-' || symbol=='*' || symbol=='/')
        return 1;
    return 0;
}
void evalPre(char exp[])
{
    int i, n1, n2, num, l=strlen(exp), result;
    char symbol;
    for(i=l-1; i>=0; i--)
    {
        symbol=exp[i];
        if(symbol>='0' && symbol<='9')
        {
            num = symbol - '0';
            push(num);
        }
        else if(is_op(symbol))
        {
            n2=pop();
            n1=pop();
            switch(symbol)
            {
                case '+': result = n1+n2;
                break;
                case'-': result = n1-n2;
                break;
                case '*': result = n1*n2;
                break;
                case '/': result = n1/n2;
                break;
            }
            push(result);
        }
    }
    printf("%d", result=pop());
}
int main()
{
    char exp[100];
    printf("Enter prefix:\n");
    gets(exp);
    printf("On evaluation, we get: ");
    evalPre(exp);
    return 0;
}

