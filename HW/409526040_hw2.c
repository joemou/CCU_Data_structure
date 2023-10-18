#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 11

int oldPath[MAX_NODES] = {7, 2, 9, 10, -1, -1, -1, 8, 1, 3, -1};
int newPath[MAX_NODES] = {7, -1, 8, -1, 9, -1, 10, -1, -1, -1, -1};

int min(int a, int b) {
    return (a < b) ? a : b;
}

void generateRules() {
    int distances[MAX_NODES];
    int i, j;

    // Initialize distances to a large value
    for(i = 0; i < MAX_NODES; i++) {
        distances[i] = MAX_NODES;
    }

    // Perform BFS on old path
    int currentNode = 0;
    for(i = 0; i < MAX_NODES; i++) {
        if (oldPath[i] == -1) break;
        distances[oldPath[i]] = min(distances[oldPath[i]], i);
    }

    // Perform BFS on new path
    for(i = 0; i < MAX_NODES; i++) {
        if (newPath[i] == -1) break;
        distances[newPath[i]] = min(distances[newPath[i]], i);
    }

    // Print output
    for(i = 0; i < MAX_NODES; i++) {
        if (oldPath[i] == -1) break;
        for(j = 0; j < MAX_NODES; j++) {
            if (newPath[j] == -1) break;
            printf("%d ", distances[oldPath[i]] + distances[newPath[j]]);
        }
        for(; j < MAX_NODES; j++) {
            printf("-1 ");
        }
        printf("\n");
    }
}

int main() {
    generateRules();
    return 0;
}
