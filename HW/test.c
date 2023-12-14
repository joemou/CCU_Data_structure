#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int path[MAX_ROWS][MAX_COLS];
int path_end[MAX_ROWS];

// Function to compare two paths based on their lengths
int comparePaths(const void *a, const void *b) {
    int *pathA = (int *)a;
    int *pathB = (int *)b;

    // Compare the lengths of paths
    return path_end[*pathA] - path_end[*pathB];
}

int main() {


    // Initialize your matrix and path_end array here

    // Generate an array of indices to represent rows
    int rowIndices[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; ++i) {
        rowIndices[i] = i;
    }

    // Sort the rows based on the length of each path
    qsort(rowIndices, MAX_ROWS, sizeof(int), comparePaths);

    // Output the sorted paths
    printf("Sorted Paths:\n");
    for (int i = 0; i < MAX_ROWS; ++i) {
        int rowIndex = rowIndices[i];
        printf("Path %d, Length: %d\n", rowIndex, path_end[rowIndex]);

        // Optionally, you can print the path elements as well
        // for (int j = 0; j < path_end[rowIndex]; ++j) {
        //     printf("%d ", path[rowIndex][j]);
        // }
        // printf("\n");
    }

    return 0;
}
