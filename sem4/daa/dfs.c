#include <stdio.h>
#define M 100

int g[M][M], vis[M], push[M], pop[M], pi=0, po=0;

void dfs(int v, int n)
{
    vis[v] = 1;
    push[pi++] = v;

    for(int i=0; i<n; i++)
    {
        if(g[v][i]==1 && vis[i]==0)
        {
            dfs(i, n);
        }
    }

    pop[po++] = v;
}

int g[5][5], vis[5], push[5], pop[5], pi=0, po=0;

void dfs(int v, int n)
{
    vis[v] = 1;
    push[pi++] = v;
    
    for(int i=0; i<n; i++)
    {
        if(g[v][i] == 1 && vis[i]==0)
        {
            dfs(i, n);
        }
    }

    pop[po++] = v;
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
    }

    printf("enter the edges\n");
    for(int i=0; i<e; i++)
    {
        scanf("%d %d", &n1, &n2);

        g[n1][n2] = 1;
        g[n2][n1] = 1;
    } 

    dfs(0, v);

    printf("push order: \n");  
    for (int i = 0; i < pi; i++)
        printf("%d ", push[i]);
    
    printf("\npop order: \n");
    for (int i = 0; i < po; i++)
        printf("%d ", pop[i]);

    return 0;
 
}