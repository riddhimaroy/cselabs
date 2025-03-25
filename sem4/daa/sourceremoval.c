#include <stdio.h>
#define M 100

int g[M][M], vis[M], indeg[M];

void sr(int v)
{
    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            if(indeg[j]==0)
            {
                printf("%d\n", j);
                vis[j] = 1;
                indeg[j] = -1;

                for(int k = 0; k<v; k++)
                {
                    if(g[j][k]==1)
                        indeg[k]--;
                }
            }
        }
    }
}

int main()
{
    int v, e, n1, n2;

    printf("Enter the number of vertices and edges\n");
    scanf("%d %d", &v, &e);

    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            g[i][j] = 0;
        }
        vis[i] = 0;
        indeg[i] = 0;
    }

    printf("enter the edges\n");
    for(int i=0; i<e; i++)
    {
        scanf("%d %d", &n1, &n2);

        g[n1][n2] = 1;
        indeg[n2]++;
    }

    sr(v);
}