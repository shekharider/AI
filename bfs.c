#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int node;
    int cost;
} Node;

typedef struct {
    Node elements[MAX];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue *pq, int node, int cost) {
    if (pq->size == MAX) {
        printf("Priority Queue is full!\n");
        return;
    }
    pq->elements[pq->size].node = node;
    pq->elements[pq->size].cost = cost;
    pq->size++;

    int i = pq->size - 1;
    while (i != 0 && pq->elements[(i - 1) / 2].cost > pq->elements[i].cost) {
        swap(&pq->elements[i], &pq->elements[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop(PriorityQueue *pq) {
    if (pq->size <= 0) {
        printf("Priority Queue is empty!\n");
        Node emptyNode = {-1, INT_MAX};
        return emptyNode;
    }
    if (pq->size == 1) {
        pq->size--;
        return pq->elements[0];
    }

    Node root = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    int i = 0;
    int smallest = i;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < pq->size && pq->elements[left].cost < pq->elements[smallest].cost) {
            smallest = left;
        }
        if (right < pq->size && pq->elements[right].cost < pq->elements[smallest].cost) {
            smallest = right;
        }
        if (smallest != i) {
            swap(&pq->elements[i], &pq->elements[smallest]);
            i = smallest;
        } else {
            break;
        }
    }

    return root;
}

void bestFirstSearch(int graph[MAX][MAX], int n, int start, int goal) {
    int visited[MAX] = {0};
    PriorityQueue pq;
    initQueue(&pq);

    push(&pq, start, 0);

    while (pq.size > 0) {
        Node current = pop(&pq);

        if (visited[current.node]) {
            continue;
        }
        visited[current.node] = 1;

        printf("Visited Node: %d\n", current.node);

        if (current.node == goal) {
            printf("Goal Node Found!\n");
            return;
        }

        for (int i = 0; i < n; i++) {
            if (graph[current.node][i] && !visited[i]) {
                push(&pq, i, graph[current.node][i]);
            }
        }
    }

    printf("Goal Node Not Found!\n");
}

int main() {
    int graph[MAX][MAX], n, start, goal;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start node: ");
    scanf("%d", &start);

    printf("Enter the goal node: ");
    scanf("%d", &goal);

    bestFirstSearch(graph, n, start, goal);

    return 0;
}
