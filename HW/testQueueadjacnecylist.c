#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for a neighbor in the adjacency list
struct Neighbor {
    int nodeID; // ID of the neighboring node
    int weight; // Weight of the connection
    struct Neighbor* next; // Pointer to the next neighbor
};

// Modify the Node structure to include a list of neighbors
struct Node {
    int nodeID; // Node identifier
    int weight; // Weight limit of the node
    int now_weight; // The weight the node has
    int capacity_remained; // Difference between limit and now_weight
    
    // Linked list to store neighbors
    struct Neighbor* neighbors;
};

// Modify the Network structure to use an adjacency list
struct Network {
    int numNodes; // Number of nodes in the network
    struct Node* nodes; // Array of nodes
};

// Function to add a connection between two nodes with a given weight
void addConnection(struct Network* network, int node1, int node2, int weight) {
    // Create a new neighbor for node1
    struct Neighbor* newNeighbor1 = (struct Neighbor*)malloc(sizeof(struct Neighbor));
    newNeighbor1->nodeID = node2;
    newNeighbor1->weight = weight;
    newNeighbor1->next = network->nodes[node1].neighbors;
    network->nodes[node1].neighbors = newNeighbor1;

    // Create a new neighbor for node2
    struct Neighbor* newNeighbor2 = (struct Neighbor*)malloc(sizeof(struct Neighbor));
    newNeighbor2->nodeID = node1;
    newNeighbor2->weight = weight;
    newNeighbor2->next = network->nodes[node2].neighbors;
    network->nodes[node2].neighbors = newNeighbor2;
}

// Function to initialize a network with a given number of nodes
struct Network* createNetwork(int numNodes) {
    struct Network* network = (struct Network*)malloc(sizeof(struct Network));
    network->numNodes = numNodes;

    // Allocate memory for nodes
    network->nodes = (struct Node*)malloc(numNodes * sizeof(struct Node));

    // Initialize nodes and their neighbors
    for (int i = 0; i < numNodes; ++i) {
        network->nodes[i].nodeID = i; // Assign unique IDs to nodes
        network->nodes[i].weight = 0; // Initialize weight (you may want to modify this)
        network->nodes[i].now_weight = 0; // Initialize now_weight
        network->nodes[i].capacity_remained = 0; // Initialize capacity_remained
        network->nodes[i].neighbors = NULL; // Initialize neighbors as an empty list
    }

    return network;
}

// ... (rest of the code remains unchanged)

int V;

// ... (rest of the code remains unchanged)


// ... (rest of the code


struct Queue {
    int front, rear;
    int* array;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = item;
}

int dequeue(struct Queue* queue) {
    int item = queue->array[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return item;
}


int path[10000][10000];
int path_end[10000];

void printPath(struct Network* network, int parent[], int j, int index, int ans_num) {
    if (parent[j] == -1) {
        index += 1;
        path[ans_num][index - 1] = network->nodes[j]->nodeID;
        path_end[ans_num] = index;
        return;
    }
    index += 1;
    printPath(network, parent, parent[j], index, ans_num);
    path[ans_num][index - 1] = network->nodes[j]->nodeID;
}

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

        // Traverse the linked list of edges for the current node
        struct Edge* edge = network->nodes[u]->edges;
        while (edge != NULL) {
            int v = edge->destNodeID;
            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                enqueue(queue, v);
            }
            edge = edge->next;
        }
    }

    printPath(network, parent, dest, path_index, ans_num);

    free(visited);
    free(parent);
    free(queue->array);
    free(queue);
}

struct Node* createNode(int nodeID, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->nodeID = nodeID;
    newNode->weight = weight;
    newNode->now_weight = 0;
    newNode->capacity_remained = 0;
    newNode->edges = NULL;
    return newNode;
}

struct Network* createNetwork(int numNodes) {
    struct Network* network = (struct Network*)malloc(sizeof(struct Network));
    network->numNodes = numNodes;
    network->nodes = (struct Node**)malloc(numNodes * sizeof(struct Node*));
    for (int i = 0; i < numNodes; ++i) {
        network->nodes[i] = createNode(i, 0);
    }
    return network;
}

void addEdge(struct Network* network, int srcNodeID, int destNodeID, int weight) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->destNodeID = destNodeID;
    newEdge->weight = weight;
    newEdge->next = network->nodes[srcNodeID]->edges;
    network->nodes[srcNodeID]->edges = newEdge;

    struct Edge* reverseEdge = (struct Edge*)malloc(sizeof(struct Edge));
    reverseEdge->destNodeID = srcNodeID;
    reverseEdge->weight = weight;
    reverseEdge->next = network->nodes[destNodeID]->edges;
    network->nodes[destNodeID]->edges = reverseEdge;
}

void freeNetwork(struct Network* network) {
    for (int i = 0; i < network->numNodes; ++i) {
        struct Edge* current = network->nodes[i]->edges;
        while (current != NULL) {
            struct Edge* next = current->next;
            free(current);
            current = next;
        }
        free(network->nodes[i]);
    }
    free(network->nodes);
    free(network);
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
        printf("%d %d ", id[root->front-1], id[root->rear-1]);
        if(root->left!=NULL&&root->right!=NULL){
            printf("%d %d %d %d ", id[root->left->front - 1], id[root->left->rear - 1], id[root->right->front - 1], id[root->right->rear - 1]);
        }
        printf("%d",time-root->height-1);
        printf("\n");
    }
}

void ExamineTreeload(struct Network* network, struct TreeNode* root, int time, int **temp, int **limit, int id[], int *flag) {
    if (root != NULL) {
        //check out of bound
        if(root->height>time-2){//-1 because initial entangle
            *flag = 0;
           
            return;
        }
        if (root->left != NULL) {
            ExamineTreeload(network, root->left,time,temp, limit, id, flag);
        }
        if (root->right != NULL) {
            ExamineTreeload(network, root->right,time,temp, limit, id, flag);
        }


        //use path id to search the network order to check if overload
        for (int i = 0; i < V;i++){
            //for left value
            if(network->nodes[i]->nodeID==id[root->front-1]){
                //root->height mean put on the top no move down
                /*printf("(%d %d %d)", root->height, i, id[root->front - 1]);*/
                temp[root->height][i] += 1;
                /*
                printf("\n");
                for (int i = 0; i < time;i++){
                    for (int k = 0; k < V;k++){
                        
                        printf("%d ", temp[i][k]);
                    }
                    printf("\n");
                }
                */

                //deal the leaf
                if(root->right==NULL&&root->left==NULL){
                    temp[root->height+1][i] += 1;
                }
                //out of limit
                if(temp[root->height][i]>limit[root->height][i]){
                    *flag = 0;
                   
                    return;
                }
            }
            //for right value
            if(network->nodes[i]->nodeID==id[root->rear-1]){
                //root->height mean put on the top no move down
                /*printf("(%d %d %d)", root->height, i, id[root->front - 1]);*/
                temp[root->height][i] += 1;
                /*
                printf("\n");
                for (int i = 0; i < time;i++){
                    for (int k = 0; k < V;k++){
                        
                        printf("%d ", temp[i][k]);
                    }
                    printf("\n");
                }
                */
                //deal the leaf
                if(root->right==NULL&&root->left==NULL){
                    temp[root->height+1][i] += 1;
                }  
                //out of limit
                if(temp[root->height][i]>limit[root->height][i]){
                    *flag = 0;
                    return;
                }
            }
        }
 

    }

}



typedef struct AnsNode {
    struct TreeNode* root;
    int reqid;
    int req_time;
    int time;

    struct AnsNode* next;
} AnsNode;


struct AnsNode* createAnsNode(struct TreeNode* root, int reqid, int req_time, int time) {
    struct AnsNode* newNode = (AnsNode*)malloc(sizeof(AnsNode));
    newNode->root = root;
    newNode->reqid = reqid;
    newNode->req_time = req_time;
    newNode->time = time;

    newNode->next = NULL;
    return newNode;
}

// Function to insert a tree node at the end of the linked list
// Function to insert a tree node at the end of the linked list
void insertAnsNode(struct AnsNode** head, struct TreeNode* treeNode, int reqid, int req_time, int time) {
    struct AnsNode* newNode = createAnsNode(treeNode, reqid, req_time, time);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct AnsNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


void printans(struct AnsNode *head){
    //display
    while(head!=NULL){
        printf("%d ", head->reqid);
        for (int i = 0; i < path_end[head->req_time];i++){
            printf("%d ", path[head->req_time][i]);
        }
        printf("\n");
        displayTree(head->root, path[head->req_time], head->time);
        head = head->next;
    }
}

// Function to perform BFS



// Function to implement Dijkstra's algorithm to find minimum total path node weight
int dijkstra(struct Network* network, int src, int dest, int time,int **load,int **limit, int req_time, int reqid, struct AnsNode **head){

    bfs(network, src, dest, req_time);

    //build tree(by path order 1,2,3,4,5,6)
    struct TreeNode *root = buildTree(1, path_end[req_time], 0);

    int **temp = (int **)malloc(time * sizeof(int *));
    for (int i = 0; i < time; i++) {
        temp[i] = (int *)malloc(V * sizeof(int));
    }

    for (int i = 0; i < time;i++){
        for (int k = 0; k < V;k++){ 
            temp[i][k] = load[i][k];
        }
    }

    // examie the id ans out of limit or not
    // patid order 0,1,2,3,4,5,6 which need to minus one to suit tree node order
    int flag = 1;

    ExamineTreeload(network, root, time, temp, limit, path[req_time], &flag);



    //printf("[%d]\n",flag);
    
    //if no prob
    if (flag)
    {   
        for (int i = 0; i < time;i++){
            for (int k = 0; k < V;k++){
                load[i][k] = temp[i][k];
            }
        }
        insertAnsNode(head, root, reqid, req_time, time);
    }

 


    for (int i = 0; i < time; i++) {
        free(temp[i]);
    }
    free(temp);



    return flag;
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
    int **load = (int **)malloc(time * sizeof(int *));
    for (int i = 0; i < time; i++) {
        load[i] = (int *)malloc(nodes * sizeof(int));
    }

    int **limit = (int **)malloc(time * sizeof(int *));
    for (int i = 0; i < time; i++) {
        limit[i] = (int *)malloc(nodes * sizeof(int));
    }

    for(int i=0;i<time;i++){
        for (int k = 0; k < nodes;k++){
            load[i][k] = 0;
        }
    }
    for(int i=0;i<time;i++){
        for (int k = 0; k < nodes;k++){
            limit[i][k] = network->nodes[k]->weight;
        }
    }
    
    for (int i = 0; i < links; i++)
    {
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

    int startNodeID[req], endNodeID[req];
    int reqid[req];

    for (int i = 0; i < req;i++){

        scanf("%d", &reqid[i]);
        scanf("%d", &startNodeID[i]);
        scanf("%d", &endNodeID[i]);

    }

    struct AnsNode *head=NULL;
    int ansnum = 0;

    for (int i = 0; i < req;i++){

        //convert nodeID to node list num in network
        //and calc remain capacity
        int startNode=-1;
        int endNode=-1;
        for (int k = 0; k < V; k++){
            if(network->nodes[k]->nodeID==startNodeID[i]){
                startNode = k;
            }
            if(network->nodes[k]->nodeID==endNodeID[i]){
                endNode = k;
            }
            network->nodes[k]->capacity_remained = (network->nodes[k]->weight)*time - network->nodes[k]->now_weight;
        }
        
        // Run Dijkstra's algorithm
        if(dijkstra(network, startNode, endNode, time, load, limit, i, reqid[i], &head)){
            ansnum++;
        }
    }

    printf("%d\n", ansnum);


    printans(head);

    return 0;
}
