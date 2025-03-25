#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define N 4  // Number of cities

// Distance matrix
int graph[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

// Swap function for permutation
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate path cost
int calculateCost(int path[]) {
    int cost = 0;
    for (int i = 0; i < N - 1; i++) {
        cost += graph[path[i]][path[i + 1]];
    }
    cost += graph[path[N - 1]][path[0]]; // Return to start city
    return cost;
}

// Function to generate permutations and find the minimum cost
void tspBruteForce(int path[], int start, int *minCost, int bestPath[]) {
    if (start == N) { 
        // Calculate cost of current permutation
        int cost = calculateCost(path);
        if (cost < *minCost) {
            *minCost = cost;
            for (int i = 0; i < N; i++) 
            bestPath[i] = path[i];
        }
        return;
    }
    
    for (int i = start; i < N; i++) {
        swap(&path[start], &path[i]);
        tspBruteForce(path, start + 1, minCost, bestPath);
        swap(&path[start], &path[i]); // Backtrack
    }
}

int main() {
    int path[N] = {0, 1, 2, 3}; // Cities (starting at 0)
    int minCost = INT_MAX;
    int bestPath[N];

    tspBruteForce(path, 1, &minCost, bestPath); // Fix city 0 as the starting point

    // Print result
    printf("Minimum cost: %d\n", minCost);
    printf("Best path: ");
    printf("0 ");
    for (int i = 0; i < N; i++) printf("-> %d ", bestPath[i]);
    printf("-> 0\n");

    return 0;
}
