#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int V;
int path[1000][1000];
int path_end[1000];



// Structure to represent a node in the network
struct Node {
    int nodeID; // Node identifier
    int weight; // Weight limit of the node
    int now_weight; // The weight the node has
    int capacity_remained; // Difference between limit and now_weight
};

// Structure to represent a network
struct Network {
    int numNodes;         // Number of nodes in the network
    struct Node** nodes;  // Array of pointers to nodes
    int** connections;    // 2D array to represent connections between nodes
};

// Structure to represent a queue for BFS
struct Queue {
    int front, rear;
    int* array;
};

// Function to create a new node with the given ID and weight
struct Node* createNode(int nodeID, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->nodeID = nodeID;
    newNode->weight = weight;
    newNode->now_weight = 0;
    newNode->capacity_remained = 0; // Capacity remained in t sec
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

// Function to initialize a queue for BFS
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to enqueue an element to the queue
void enqueue(struct Queue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = item;
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    int item = queue->array[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return item;
}
// Function to print the path using BFS
void printPath(struct Network* network, int parent[], int j, int index, int ans_num) {
    if (parent[j] == -1) {
        index += 1;
        printf(" start-> %d(%d)", network->nodes[j]->nodeID, index);
        path_end[ans_num] = index;
        printf("[%d]", ans_num);
        return;
    }
    index += 1;
    printPath(network, parent, parent[j], index, ans_num);
    path[ans_num][index - 1] = network->nodes[j]->nodeID;
    printf(" -> %d(%d)", network->nodes[j]->nodeID, index);
}

// Function to perform BFS and find the minimum total path node weight
void bfs(struct Network* network, int src, int dest, int ans_num) {
    int* visited = (int*)malloc(network->numNodes * sizeof(int));
    int* parent = (int*)malloc(network->numNodes * sizeof(int));
    int path_index = 0;

    for (int i = 0; i < network->numNodes; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    struct Queue* queue = createQueue(network->numNodes);

    visited[src] = 1;
    enqueue(queue, src);

    while (!isEmpty(queue)) {
        int u = dequeue(queue);

        for (int v = 0; v < network->numNodes; v++) {
            if (!visited[v] && network->connections[u][v]) {
                visited[v] = 1;
                parent[v] = u;
                enqueue(queue, v);
            }
        }
    }

    // Print the results
    printf("Minimum Total Path Node Weight from Node %d to Node %d:\n", src, dest);
    printPath(network, parent, dest, path_index, ans_num);
    printf("\n");

    // Free allocated memory
    free(visited);
    free(parent);
    free(queue->array);
    free(queue);
}



int main() {
    // Create a network with 4 nodes
    int nodes = INT_MIN, links = INT_MIN, timeslot = INT_MIN, req = INT_MIN;
    scanf("%d %d %d %d", &nodes, &links, &timeslot, &req);
    struct Network* network = createNetwork(nodes);

    // Create nodes and assign weights
    for (int i = 0; i < nodes; i++) {
        int id, weight;
        scanf("%d %d", &id, &weight);
        network->nodes[i] = createNode(id, weight);
    }

    // Add connections with weights
    for (int i = 0; i < links; i++) {
        int uselessID, ID1, ID2;
        scanf("%d %d %d", &uselessID, &ID1, &ID2);

        // Convert nodeID to node list num in network
        int node_link1, node_link2;
        for (int k = 0; k < nodes; k++) {
            if (network->nodes[k]->nodeID == ID1) {
                node_link1 = k;
            }
            if (network->nodes[k]->nodeID == ID2) {
                node_link2 = k;
            }
        }

        addConnection(network, node_link1, node_link2, 1);
    }

    // Choose start and end points
    for (int i = 0; i < req; i++) {
        int startNodeID, endNodeID;
        int reqid;
        scanf("%d", &reqid);
        printf("Enter the start node: ");
        scanf("%d", &startNodeID);
        printf("Enter the end node: ");
        scanf("%d", &endNodeID);

        // Convert nodeID to node list num in network
        // and calc remain capacity
        int startNode;
        int endNode;
        for (int k = 0; k < nodes; k++) {
            if (network->nodes[k]->nodeID == startNodeID) {
                startNode = k;
            }
            if (network->nodes[k]->nodeID == endNodeID) {
                endNode = k;
            }
            network->nodes[k]->capacity_remained = (network->nodes[k]->weight) * timeslot - network->nodes[k]->now_weight;
        }

        // Run BFS algorithm
        bfs(network, startNode, endNode, i);
    }

    printf("\n\n\n");
    printf("\n");

    for (int k = 0; k < req; k++) {
        int pathid[path_end[k]];
        for (int i = 1; i <= path_end[k]; i++) {
            printf("%d ", path[k][path_end[k] - i]);
            pathid[i - 1] = path[k][path_end[k] - i];
        }
        printf("\n");
        for (int i = 0; i < path_end[k]; i++) {
            path[k][i] = pathid[i];
        }
        for (int i = 0; i < path_end[k]; i++) {
            printf("%d ", path[k][i]);
        }
    }

    return 0;
}
