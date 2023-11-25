#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int V=4;

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

// Function to print the shortest path from source to target
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf(" -> %d", j);
}

// Function to print the results of Dijkstra's algorithm
void printSolution(int dist[], int parent[], int src) {
    printf("Shortest Path from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("Node %d to Node %d: Distance %d | Path: %d", src, i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Function to implement Dijkstra's algorithm for a given graph
void dijkstra(struct Network* network, int src) {
    int dist[V];     // The output array dist[i] holds the shortest distance from src to i
    int sptSet[V];   // sptSet[i] is true if node i is included in the shortest path tree or the shortest distance from src to i is finalized
    int parent[V];   // parent[i] holds the previous node in the shortest path from src to i

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = network->nodes[src]->weight;

    // Find the shortest path for all nodes
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent nodes of the picked node
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && network->nodes[v] && dist[u] + network->nodes[v]->weight < dist[v]) {
                dist[v] = dist[u] + network->nodes[v]->weight;
                parent[v] = u;
            }
        }
    }

    // Print the constructed distance array and path
    printSolution(dist, parent, src);
}


/*
// Function to implement Dijkstra's algorithm for a given graph
void dijkstra(struct Network* network, int src) {
    int dist[V];     // The output array dist[i] holds the shortest distance from src to i
    int sptSet[V];   // sptSet[i] is true if node i is included in the shortest path tree or the shortest distance from src to i is finalized
    int parent[V];   // parent[i] holds the previous node in the shortest path from src to i

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find the shortest path for all nodes
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && network->connections[u][v] && dist[u] + network->connections[u][v] < dist[v]) {
                dist[v] = dist[u] + network->connections[u][v];
                parent[v] = u;
            }
    }

    // Print the constructed distance array and path
    printSolution(dist, parent, src);
}

*/

int main() {
    // Create a network with 4 nodes
    struct Network* network = createNetwork(4);

    // Create nodes and assign weights
    network->nodes[0] = createNode(0, 10);
    network->nodes[1] = createNode(1, 20);
    network->nodes[2] = createNode(2, 15);
    network->nodes[3] = createNode(3, 25);

    // Add connections with weights
    addConnection(network, 0, 1, 5);
    addConnection(network, 0, 2, 8);
    addConnection(network, 1, 2, 12);
    addConnection(network, 1, 3, 7);
    addConnection(network, 2, 3, 10);

    // Run Dijkstra's algorithm starting from node 0
    dijkstra(network, 0);

    return 0;
}

