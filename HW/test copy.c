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



// Define the structure for a node in the tree
struct TreeNode {
    int front;
    int mid;
    int rear;
    int height;
    struct TreeNode *left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* TreecreateNode(int front, int mid, int rear, int height) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->front = front;
    newNode->mid = mid;
    newNode->rear = rear;
    newNode->height = height;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to recursively build the tree
struct TreeNode* buildTree(int front, int rear, int height) {
    if (height==-1) {
        return NULL;
    }

    int mid = (front + rear) / 2;
    struct TreeNode* root = TreecreateNode(front, mid, rear, height);//record front rear and mid and invertible height

    if(mid==front){
        root->left = buildTree(front, mid, -1);//leaf node break
        root->right = buildTree(mid, rear, -1);//leaf node break
    }
    else{
        height += 1;
        root->left = buildTree(front, mid, height);
        root->right = buildTree(mid, rear, height);
    }
    return root;
}

// Function to recursively display the tree
void displayTree(struct TreeNode* root, int id[],int time) {
    if (root != NULL) {
       
        if (root->left != NULL) {
            displayTree(root->left,id,time);
        }
        
        if (root->right != NULL) {
            displayTree(root->right,id,time);
        }
        printf("%d %d %d ", id[root->front-1], id[root->rear-1], time-root->height);
        if(root->left!=NULL&&root->right!=NULL){
            printf("%d %d %d %d", id[root->left->front - 1], id[root->left->rear - 1], id[root->right->front - 1], id[root->right->rear - 1]);
        }
        printf("\n");
    }
}

int ExamineTreeload(struct Network* network, struct TreeNode* root, int time, int temp[V][time], int **limit, int id[]) {
    if (root != NULL) {
       
        if (root->left != NULL) {
            ExamineTreeload(network, root->left,time,temp, limit, id);
        }
        if (root->right != NULL) {
            ExamineTreeload(network, root->right,time,temp, limit, id);
        }
        //use path id to search the network order to check if overload
        for (int i = 0; i < V;i++){
            if(network->nodes[i]->nodeID==id[root->front-1]){
                temp[i][time - root->height] += 1;//time - root->height mean put on the top no move down
                if(temp[i][time - root->height]>limit[i][time - root->height]){
                    return 0;
                }
            }
            if(network->nodes[i]->nodeID==id[root->rear-1]){
                temp[i][time - root->height] += 1;//time - root->height mean put on the top no move down
                if(temp[i][time - root->height]>limit[i][time - root->height]){
                    return 0;
                }
            }
        }

    }
    return 1;
}

// Function to find the vertex with the minimum distance value,
// from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index=-1;

    for (int v = 0; v < V; v++){
        if (sptSet[v] == 0 && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void printPath(struct Network* network, int parent[], int j, int index, int ans_num) {
    if (parent[j] == -1) {
        index += 1;
        path[ans_num][index-1] = network->nodes[j]->nodeID;
        path_end[ans_num] = index;
        return;
    }
    index += 1;
    printPath(network, parent, parent[j], index, ans_num);
    path[ans_num][index-1] = network->nodes[j]->nodeID;

}

// Function to print the results of Dijkstra's algorithm for minimum total path node weight
void printSolution(struct Network* network, int totalWeight[], int parent[], int src, int dest, int index, int ans_num) {

    printPath(network, parent, dest, index, ans_num);

}

// Function to implement Dijkstra's algorithm to find minimum total path node weight
int dijkstra(struct Network* network, int src, int dest, int time,int **load,int **limit, int req_time, int reqid){
    int* totalWeight = (int*)malloc(V * sizeof(int)); // Array to store the minimum total path node weight from src to i
    int* parent = (int*)malloc(V * sizeof(int));      // Array to store the parent node in the shortest path from src to i
    int* sptSet = (int*)malloc(V * sizeof(int));       // Array to track the inclusion of vertices in the shortest path tree
    int path_index = 0;


    // Initialize all total weights as INFINITE, parent array as -1, and sptS       et as 0
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
    printSolution(network, totalWeight, parent, src, dest, path_index, req_time);
    //invert path
    int path_id[path_end[req_time]];
    for (int i = 1; i <=path_end[req_time] ; i++) {
        path_id[i - 1] = path[req_time][path_end[req_time] - i];
    }
    for (int i = 0; i < path_end[req_time];i++){
        path[req_time][i] = path_id[i];
    }

    //build tree(by path order 1,2,3,4,5,6)
    struct TreeNode *root = buildTree(1, path_end[req_time], 0);

    int temp[V][time];

    for (int i = 0; i < V;i++){
        for (int k = 0; k < time;k++){
            temp[i][k] = load[i][k];
        }
    }

    // examie the id ans out of limit or not
    // patid order 0,1,2,3,4,5,6 which need to minus one to suit tree node order
    int flag = ExamineTreeload(network, root, time, temp, limit, path_id);

    printf("(%d)\n",reqid);
    //if no prob
    if(flag){
        for (int i = 0; i < V;i++){
            for (int k = 0; k < time;k++){
                load[i][k] = temp[i][k];
            }
        }
        //display
        printf("%d ", reqid);
        for (int i = 0; i < path_end[req_time];i++){
            printf("%d ", path[req_time][i]);
        }
        printf("\n");
        displayTree(root, path_id, time);
        return 1;
    }



    // Free allocated memory
    free(totalWeight);
    free(parent);
    free(sptSet);
    return 0;
}





int main() {
    // Create a network with 4 nodes
    int nodes = INT_MIN, links = INT_MIN, time = INT_MIN, req = INT_MIN;
    scanf("%d %d %d %d", &nodes, &links, &time, &req);
    struct Network* network = createNetwork(nodes);
    V = nodes;

    // Create nodes and assign weights
    for (int i = 0; i < V;i++){
        int id, weight;
        scanf("%d %d",&id,&weight);
        network->nodes[i] = createNode(id, weight);
    }

    //create matrix store weight and limit
    int **load = (int **)malloc(nodes * sizeof(int *));
    for (int i = 0; i < time; i++) {
        load[i] = (int *)malloc(time * sizeof(int));
    }
    int **limit = (int **)malloc(nodes * sizeof(int *));
    for (int i = 0; i < time; i++) {
        limit[i] = (int *)malloc(time * sizeof(int));
    }
    for(int i=0;i<nodes;i++){
        for (int k = 0; k < time;k++){
            load[i][k] = 0;
        }
    }
    for(int i=0;i<nodes;i++){
        for (int k = 0; k < time;k++){
            limit[i][k] = network->nodes[i]->weight;
        }
    }

    // Add connections with weights
    for (int i = 0; i < links;i++){
        int uselessID, ID1, ID2;
        scanf("%d %d %d",&uselessID,&ID1,&ID2);
        
        //convert nodeID to node list num in network
        int node_link1=-1, node_link2=-1;
        for (int k = 0; k < V; k++){
            if(network->nodes[k]->nodeID==ID1){
                node_link1 = k;
            }
            if(network->nodes[k]->nodeID==ID2){
                node_link2 = k;
            }
        }
        
        addConnection(network, node_link1, node_link2, 1);
    }
    
    // Choose start and end points
    for (int i = 0; i < req;i++){
        int startNodeID, endNodeID;
        int reqid;
        scanf("%d", &reqid);
        scanf("%d", &startNodeID);
        scanf("%d", &endNodeID);

        //convert nodeID to node list num in network
        //and calc remain capacity
        int startNode=-1;
        int endNode=-1;
        for (int k = 0; k < V; k++){
            if(network->nodes[k]->nodeID==startNodeID){
                startNode = k;
            }
            if(network->nodes[k]->nodeID==endNodeID){
                endNode = k;
            }
            network->nodes[k]->capacity_remained = (network->nodes[i]->weight)*time - network->nodes[i]->now_weight;
        }
        // Run Dijkstra's algorithm
        dijkstra(network, startNode, endNode, time, load, limit, i, reqid);
              
    }

    return 0;
}
