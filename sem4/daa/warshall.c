// warshall

#include <stdio.h>
int main()
{
    int n, i, j, k, a[50][50];
    printf("enter the number of vertices\n");
    scanf("%d", &n);

    printf("enter the matrix\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            for(k=0; k<n; k++)
            {
                if(a[j][i]==1 && a[i][k]==1)
                {
                    a[j][k] = 1;
                }
            }
        }
    }

    printf("the transitive closure is\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}