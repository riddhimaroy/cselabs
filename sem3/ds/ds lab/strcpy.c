//To copy one string to another using Recursion.

#include <stdio.h>
#include <string.h>

void stcp(char str[], char str1[], int i)
{
    str1[i] = str[i];
    int n = strlen(str);

    if(i==n)
    {
        printf("The copied string is %s", str1);
    }
    else
    return stcp(str, str1, i+1);
}

int main()
{
    char str[20], str1[20];

    strcpy(str1, "");
    printf("Enter a string to be copied \n");
    scanf("%s", str);
    stcp(str, str1, 0);
    //printf("The copied string is %s", str1);
}