// to implement selection sort using recursion

#include <stdio.h>

void selrec(int arr[], int n, int i)
{
    int small, j, x=i;
    if(i==n-1)
    {
        printf("The sorted array is \n");
        for(j=0; j<n; j++)
        {
            printf("%d\n", arr[j]);
        }
    }


    small = arr[i];

    for (j = i; j < n ; j++)
    {
        if(arr[j]<small)
        {
            small = arr[j];
            x = j;
        }
    }

    int temp = arr[i];
    arr[i] = arr[x];
    arr[x] = temp;

    return selrec(arr, n, i+1);
}

int main()
{
    int n, i, arr[50];
    printf("Enter the limit of array\n");
    scanf("%d", &n);

    for(i=0; i<n; i++)
    {
        printf("Enter elements into array\n");
        scanf("%d", &arr[i]);
    }

    selrec(arr, n, 0);
}