#include <stdio.h>
#include <stdlib.h>

int smallest(int* arr, int n)
{
    int *s;
    s = arr;

    for(int i=0; i<n; i++)
    {
        if(*(arr+i)<*s)
            *s =*(arr+i);
    }
    return *s;
}

int main()
{
    int n, i, c; int* arr;

    printf("Enter the limit of array");
    scanf("%d", &n);

    arr = (int*)calloc(n, sizeof(int));
    
    printf("Enter element into array");
    for(i=0; i<n; i++)
        scanf("%d", &arr[i]);
    
    c = smallest(arr, n);

    printf("The smallest element is %d", c);
}