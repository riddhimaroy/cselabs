#include <stdio.h>
#include <limits.h>

#define N 4

int jobs[N][N] = {
    {9, 2, 7, 8},
    {6, 4, 3, 7},
    {5, 8, 1, 8},
    {7, 6, 9, 4}
}; // Cost matrix

int min_cost = INT_MAX; // Store the minimum cost

// Function to calculate the minimum cost using backtracking
void findMinCost(int assigned[], int used[], int person, int curr_cost) {
    if (person == N) { // If all people are assigned
        if (curr_cost < min_cost) {
            min_cost = curr_cost; // Update min cost
        }
        return;
    }

    for (int job = 0; job < N; job++) {
        if (!used[job]) { // If job is not assigned
            used[job] = 1; // Mark job as assigned
            assigned[person] = job;
            findMinCost(assigned, used, person + 1, curr_cos
            used[job] = 0; // Backtrack
        }
    }
}

int main() {
    int assigned[N] = {0}; // Stores which job is assigned to which person
    int used[N] = {0}; // Used to track assigned jobs

    findMinCost(assigned, used, 0, 0);

    printf("Minimum cost assignment: %d\n", min_cost);
    return 0;
}
t + jobs[person][job]);