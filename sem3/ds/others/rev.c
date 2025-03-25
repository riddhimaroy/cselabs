#include <stdio.h>
#include <stdlib.h>


void reverse(int* p, int n)
{
    int temp;
    //int* q = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n/2; i++)
    {
        temp = *(p+n-i-1);
        *(p+n-i-1) = *(p+i);
        *(p+i) = temp;
    }
    //return q;
}

int main()
{
    int n; int* p;

    printf("Enter the number of elements");
    scanf("%d", &n);

    p = (int*)calloc(n, sizeof(int));

    printf("Enter the elements into the array");
    for(int i=0; i<n; i++)
        scanf("%d", &p[i]);

    reverse(p, n);

    printf("The reversed array is\n");
    for(int i=0; i<n; i++)
    {
        printf("%d", p[i]);
    }
}