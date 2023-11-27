#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int V=5;

// Structure to represent a node in the network
struct Node {
    int nodeID;       // Node identifier
    int weight;       // Weight of the node
};

// Structure to represent a network
struct Network {
    int numNodes;         // Number of nodes in the network
    struct Node** nodes;  // Array of pointers to nodes
    int** connections;    // 2D array to represent connections between nodes
};

// Function to create a new node with the given ID and weight
struct Node* createNode(int nodeID, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->nodeID = nodeID;
    newNode->weight = weight;
    return newNode;
}

// Function to create a network with a given number of nodes
struct Network* createNetwork(int numNodes) {
    struct Network* network = (struct Network*)malloc(sizeof(struct Network));
    network->numNodes = numNodes;

    // Allocate memory for nodes and connections
    network->nodes = (struct Node**)malloc(numNodes * sizeof(struct Node*));
    network->connections = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; ++i) {
        network->nodes[i] = NULL;
        network->connections[i] = (int*)calloc(numNodes, sizeof(int));
    }

    return network;
}

// Function to add a connection between two nodes with a given weight
void addConnection(struct Network* network, int node1, int node2, int weight) {
    network->connections[node1][node2] = weight;
    network->connections[node2][node1] = weight;
}

// Function to find the vertex with the minimum distance value,
// from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf(" -> %d", j);
        return;
    }

    printPath(parent, parent[j]);

    printf(" -> %d", j);
}
// Function to print the results of Dijkstra's algorithm for minimum total path node weight
void printSolution(int totalWeight[], int parent[], int src, int dest) {
    printf("Minimum Total Path Node Weight from Node %d to Node %d:\n", src, dest);
    printf("Total Weight: %d | Path: %d", totalWeight[dest], dest);
    printPath(parent, dest);
    printf("\n");
}
// Function to implement Dijkstra's algorithm to find minimum total path node weight
void dijkstra(struct Network* network, int src, int dest) {
    int* totalWeight = (int*)malloc(V * sizeof(int));  // Array to store the minimum total path node weight from src to i
    int* parent = (int*)malloc(V * sizeof(int));       // Array to store the parent node in the shortest path from src to i
    int* sptSet = (int*)malloc(V * sizeof(int));        // Array to track the inclusion of vertices in the shortest path tree

    // Initialize all total weights as INFINITE, parent array as -1, and sptSet as 0
    for (int i = 0; i < V; i++) {
        totalWeight[i] = INT_MAX;
        parent[i] = -1;
        sptSet[i] = 0;
    }

    // Total weight from source to itself is always the weight of the source node
    totalWeight[src] = network->nodes[src]->weight;

    // Find minimum total path node weight for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum total path node weight vertex from the set of vertices not yet processed
        int u = minDistance(totalWeight, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update totalWeight value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && network->connections[u][v] && totalWeight[u] != INT_MAX &&
                totalWeight[u] + network->nodes[v]->weight < totalWeight[v]) {
                totalWeight[v] = totalWeight[u] + network->nodes[v]->weight;
                parent[v] = u;
            }
        }
    }

    // Print the results
    printSolution(totalWeight, parent, src, dest);

    // Free allocated memory
    free(totalWeight);
    free(parent);
    free(sptSet);
}





int main() {
    // Create a network with 4 nodes
    struct Network* network = createNetwork(5);
    V = 5;

    // Create nodes and assign weights
    network->nodes[0] = createNode(0, 10);
    network->nodes[1] = createNode(1, 20);
    network->nodes[2] = createNode(2, 19);
    network->nodes[3] = createNode(3, 25);
    network->nodes[4] = createNode(4, 17);

    // Add connections with weights
    addConnection(network, 0, 1, 5);
    addConnection(network, 0, 2, 8);
    addConnection(network, 1, 2, 1);
    addConnection(network, 1, 3, 7);
    addConnection(network, 2, 3, 10);
    addConnection(network, 3, 4, 10);
    addConnection(network, 2, 4, 999);


    // Choose start and end points
    int startNode, endNode;
    printf("Enter the start node: ");
    scanf("%d", &startNode);
    printf("Enter the end node: ");
    scanf("%d", &endNode);

    // Run Dijkstra's algorithm
    dijkstra(network, startNode, endNode);

    // ... (existing code)

    return 0;
}

