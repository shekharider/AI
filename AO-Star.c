#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999

int cost[MAX][MAX], n, goal[MAX], heuristic[MAX], solution[MAX];

int minCost(int parent) {
    int min = INF;
    for (int i = 0; i < n; i++) {
        if (cost[parent][i] != INF && heuristic[i] < min) {
            min = heuristic[i];
        }
    }
    return min;
}

void AOStar(int node) {
    if (goal[node]) {
        solution[node] = 1;
        return;
    }

    int minSubCost = minCost(node);
    printf("Expanding node: %d with cost %d\n", node, minSubCost);

    for (int i = 0; i < n; i++) {
        if (cost[node][i] != INF && heuristic[i] == minSubCost) {
            AOStar(i);
            if (solution[i]) {
                solution[node] = 1;
                break;
            }
        }
    }
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &heuristic[i]);
    }

    printf("Enter goal nodes (1 if goal, 0 if not):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &goal[i]);
    }

    int start;
    printf("Enter start node: ");
    scanf("%d", &start);

    AOStar(start);

    if (solution[start])
        printf("Solution found.\n");
    else
        printf("No solution found.\n");

    return 0;
}


/* 5

0  1  9999  9999  3
1  0  4     9999  9999
9999  4  0   2     9999
9999  9999  2   0     1
3  9999  9999  1     0

7
6
2
1
0

0
0
0
0
1
*/