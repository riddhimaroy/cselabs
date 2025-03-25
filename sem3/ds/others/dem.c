#include <stdio.h>
#include <stdlib.h>
/*
int* func(int* arr, int n)
{
    int *q; int**g;

    q = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n; i++)
    {
        *(q+i) = *(arr+i)+1;
    }

    g = &q;

    printf("The first element is %d\n", **g);
    return q;
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

    int *q = func(arr, n);

    for(i=0; i<n; i++)
        printf("%d\n", q[i]);
}
*/
#include<stdio.h>

void change(int *b)

{
int i;
for(i=0;i<=4;i++)
{
*b=*b+1;
b++;
}
}

int main() 
{
    int a[5]={2,3,4,5,6}; int i;

change(a);

for(i=4;i>=0;i--)

printf("%d \t",a[i]);

return 0;
}