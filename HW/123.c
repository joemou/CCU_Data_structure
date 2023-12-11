#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 10000

int V;
int path[MAX_NODES][MAX_NODES];
int path_end[MAX_NODES];
int flag;

// Structure to represent a node in the network
struct Node {
    int nodeID;              // Node identifier
    int weight;              // Weight limit of the node
    int now_weight;          // The weight the node currently has
    int capacity_remained;   // Difference between the limit and now_weight
};

// Structure to represent a network
struct Network {
    int numNodes;           // Number of nodes in the network
    struct Node** nodes;    // Array of pointers to nodes
    int** connections;      // 2D array to represent connections between nodes
};

// Structure to represent a BFS queue node
struct QueueNode {
    int vertex;
    struct QueueNode* next;
};

// Structure to represent a BFS queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new node with the given ID and weight
struct Node* createNode(int nodeID, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->nodeID = nodeID;
    newNode->weight = weight;
    newNode->now_weight = 0;
    newNode->capacity_remained = 0;
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

// Function to create a new Queue node
struct QueueNode* createQueueNode(int vertex) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a vertex to the queue
void enqueue(struct Queue* queue, int vertex) {
    struct QueueNode* newNode = createQueueNode(vertex);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a vertex from the queue
int dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return -1;
    int vertex = queue->front->vertex;
    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    return vertex;
}

// Function to perform BFS
int BFS(struct Network* network, int src, int dest, int time, int** load, int** limit, int req_time, int reqid) {
    int visited[V];
    for (int i = 0; i < V; ++i)
        visited[i] = 0;

    struct Queue* queue = createQueue();
    enqueue(queue, src);
    visited[src] = 1;

    while (queue->front != NULL) {
        int u = dequeue(queue);

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && network->connections[u][v]) {
                visited[v] = 1;
                enqueue(queue, v);

                // Update the path and load array
                path[req_time][path_end[req_time]++] = network->nodes[v]->nodeID;
                load[req_time][v]++;

                // Check for load limit
                if (load[req_time][v] > limit[req_time][v]) {
                    free(queue);
                    return 0;  // Load limit exceeded
                }

                // Check if the destination is reached
                if (v == dest) {
                    free(queue);
                    return 1;  // Destination reached
                }
            }
        }
    }

    free(queue);
    return 0;  // Destination not reached
}

int main() {
    // ... (same as before)

    for (int i = 0; i < req; i++) {
        int startNode = -1;
        int endNode = -1;

        for (int k = 0; k < V; k++) {
            if (network->nodes[k]->nodeID == startNodeID[i]) {
                startNode = k;
            }
            if (network->nodes[k]->nodeID == endNodeID[i]) {
                endNode = k;
            }
        }

        // Run BFS
        if (BFS(network, startNode, endNode, time, load, limit, i, reqid[i])) {
            ansnum++;
        }
    }

    // ... (same as before)
}
