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
    int now_weight; //The weight the node have
    int capacity_remained; //diff between limit and now_wewight
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
    newNode->now_weight = 0;
    newNode->capacity_remained = 0;//cpacity remained in t sec
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

void printPath(struct Network* network, int parent[], int j, int index, int ans_num) {
    if (parent[j] == -1) {
        index += 1;
        printf(" start-> %d(%d)", network->nodes[j]->nodeID, index);
        path[ans_num][index-1] = network->nodes[j]->nodeID;
        path_end[ans_num] = index-1;
        printf("[%d]", ans_num);
        return;
    }
    index += 1;
    printPath(network, parent, parent[j], index, ans_num);
    path[ans_num][index-1] = network->nodes[j]->nodeID;
    printf(" -> %d(%d)", network->nodes[j]->nodeID, index);
}

// Function to print the results of Dijkstra's algorithm for minimum total path node weight
void printSolution(struct Network* network, int totalWeight[], int parent[], int src, int dest, int index, int ans_num) {
    printf("Minimum Total Path Node Weight from Node %d to Node %d:\n", src, dest);
    printf("Total Weight: %d | Path: ", totalWeight[dest]);
    printPath(network, parent, dest, index, ans_num);
    printf("\n");
}

// Function to implement Dijkstra's algorithm to find minimum total path node weight
void dijkstra(struct Network* network, int src, int dest, int ans_num) {
    int* totalWeight = (int*)malloc(V * sizeof(int)); // Array to store the minimum total path node weight from src to i
    int* parent = (int*)malloc(V * sizeof(int));      // Array to store the parent node in the shortest path from src to i
    int* sptSet = (int*)malloc(V * sizeof(int));       // Array to track the inclusion of vertices in the shortest path tree
    int path_index = 0;

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
            //if the node no visited, connected, with weight and weight larger than new path, update 
            if (!sptSet[v] && network->connections[u][v] && totalWeight[u] != INT_MAX &&totalWeight[u] + network->nodes[v]->weight < totalWeight[v]) {
                totalWeight[v] = totalWeight[u] + network->nodes[v]->weight;
                parent[v] = u;
            }
        }
    }

    // Print the results
    printSolution(network, totalWeight, parent, src, dest, path_index, ans_num);


    // Free allocated memory
    free(totalWeight);
    free(parent);
    free(sptSet);
}

int main() {
    // Create a network with 4 nodes
    int nodes = INT_MIN, links = INT_MIN, timeslot = INT_MIN, req = INT_MIN;
    scanf("%d %d %d %d", &nodes, &links, &timeslot, &req);
    struct Network* network = createNetwork(nodes);
    V = nodes;

    // Create nodes and assign weights
    for (int i = 0; i < V;i++){
        int id, weight;
        scanf("%d %d",&id,&weight);
        network->nodes[i] = createNode(id, weight);
    }

    // Add connections with weights
    for (int i = 0; i < links;i++){
        int uselessID, ID1, ID2;
        scanf("%d %d %d",&uselessID,&ID1,&ID2);
        
        //convert nodeID to node list num in network
        int node_link1, node_link2;
        for (int i = 0; i < V; i++){
            if(network->nodes[i]->nodeID==ID1){
                node_link1 = i;
            }
            if(network->nodes[i]->nodeID==ID2){
                node_link2 = i;
            }
        }
        
        addConnection(network, node_link1, node_link2, 1);
    }
    
    // Choose start and end points
    for (int i = 0; i < req;i++){
        int startNodeID, endNodeID;
        int reqid;
        scanf("%d", &reqid);
        printf("Enter the start node: ");
        scanf("%d", &startNodeID);
        printf("Enter the end node: ");
        scanf("%d", &endNodeID);

        //convert nodeID to node list num in network
        //and calc remain capacity
        int startNode;
        int endNode;
        for (int i = 0; i < V; i++){
            if(network->nodes[i]->nodeID==startNodeID){
                startNode = i;
            }
            if(network->nodes[i]->nodeID==endNodeID){
                endNode = i;
            }
            network->nodes[i]->capacity_remained = (network->nodes[i]->weight)*timeslot - network->nodes[i]->now_weight;
        }

        // Run Dijkstra's algorithm
        dijkstra(network, startNode, endNode, i);


    }
    printf("\n");
    for (int k = 0; k < req;k++){
        for (int i = path_end[k]; i >= 0 ; i--) {
            printf("%d ", path[k][i]);
        }
        printf("\n");
    }


    return 0;
}
