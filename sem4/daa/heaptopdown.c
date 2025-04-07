#include <stdio.h>
int main()
{
    int n, arr[50], i, x;

    printf("enter the number of elemetns\n");
    scanf("%d", &n);

    printf("enter the heap\n");
    for(i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("enter element to be entered\n");
    scanf("%d", &x);

    arr[n] = x;
    i = n;

    while(i>0)
    {
        if(arr[i]>arr[(i-1)/2])
        {
            x = arr[i];
            arr[i] = arr[(i-1)/2];
            arr[(i-1)/2]=x;

            i = (i-1)/2;
        }

        else
            break;
    }

    printf("the heap is\n");

    for(i=0; i<=n; i++)
    {
        printf("%d ", arr[i]);
    }
}