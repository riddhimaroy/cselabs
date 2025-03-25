// To check whether a given String is Palindrome or not, using Recursion

#include <stdio.h>
#include <string.h>

void ispalin(char str[], char rev[], int i)
{
    int n = strlen(str);

    rev[i] = str[n-i-1];

    if(i==n)
    {
        if(strcmp(rev, str)==0)
            printf("It is a palindrome");
        else
            printf("no");
    }
    else
        return ispalin(str, rev, i+1);
}

int main()
{
    char str[20], rev[20];

    printf("Enter a string: \n");
    scanf("%s", str);
    ispalin(str, rev, 0);
}