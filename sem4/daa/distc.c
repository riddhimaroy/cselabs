#include <stdio.h>
int main()
{
    int n, arr[50], c[50], o[50], i, j, k, temp, max = 0;
    printf("enter the number of elements\n");
    scanf("%d", &n);

    printf("enter the array\n");
    for(i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
        if(arr[i]>max)
            max = arr[i];
    }

    for(i=0; i<max+1; i++)
    {
        c[i]=0;
    }

    for(i=0; i<n; i++)
    {
        c[arr[i]]++;
    }

    for(i=1; i<max+1; i++)
    {
        c[i] += c[i-1];
    }

    for(i=0; i<max+1; i++)
        printf("%d ", c[i]);

    for(i=n-1; i>=0; i--)
    {
        o[c[arr[i]]] = arr[i];
        c[arr[i]]--;
    }

    printf("the final array is\n");
    for(i=1; i<n+1; i++)
        printf("%d ", o[i]);

}