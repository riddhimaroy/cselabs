#include <stdio.h>

int isPrime(int n)
{
    for(int i=2; i<n; i++)
    {
        if(n%i==0)
            return 0;
    }

    return 1;
}

int gcd(int a, int b)
{
    int min = a>b?a:b;
    int pr = 1;

    for(int i=2; i<a; i++)
    {
        if(a%i==0 && b%i==0 && isPrime(i)==1)
        {
            a/=i;
            b/=i;
            pr = pr*i;
            i--;
        }
    }

    return pr;
}

int main()
{
    int a, b;

    printf("enter the two numbers\n");
    scanf("%d %d", &a, &b);
    
    int x = gcd(a, b);

    printf("gcd is %d", x);
}