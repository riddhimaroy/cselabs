//consecutive integer checking

#include <stdio.h>

int gcd(int a, int b)
{
    int t = a>b?b:a;

    for(int i=t; i>0; i--)
    {
        if(a%t==0)
        {
            if(b%t==0)
                return i;
        }

        else
            t--;
    }
}

int main()
{
    int a, b;

    printf("enter the two numbers\n");
    scanf("%d %d", &a, &b);

    int x = gcd(a, b);

    printf("gcd is %d", x);
}