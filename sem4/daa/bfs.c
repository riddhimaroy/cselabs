 #include <stdio.h>
#define M 100

int g[M][M], vis[M], queue[M], front = 0, rear = 0;

void bfs(int start, int v)
{
    vis[start] = 1;         // Mark start node as visited
    queue[rear++] = start;  // Enqueue start node

    while (front < rear)    // While queue is not empty
    {
        int node = queue[front++];  // Dequeue front node
        printf("%d ", node);        // Print the node (BFS order)

        // Visit all adjacent nodes
        for (int i = 0; i < v; i++)
        {
            if (g[node][i] == 1 && vis[i] == 0)
            {
                vis[i] = 1;         // Mark as visited
                queue[rear++] = i;  // Enqueue the node
            }
        }
    }
}

int main()
{
    int v, e, n1, n2;

    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &v, &e);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
            g[i][j] = 0;  // No edges initially
        vis[i] = 0;       // Mark all nodes as unvisited
    }

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d", &n1, &n2);
        g[n1][n2] = 1;
        g[n2][n1] = 1; // Since it's an undirected graph
    }

    printf("BFS traversal starting from node 0:\n");
    bfs(0, v);

    return 0;
}


void bfs(int start, int v)
{
    vis[start] = 1;
    queue[rear++]=start;

    while(front<rear)
    {
        int node = queue[front++];
        printf("%d", node);

        for(int i=0; i<v; i++)
        {
            if(vis[i]==0 && g[node][i]==0)
                vis[i] = 1;
                queue[rear++] = 1;
        }
    }
}