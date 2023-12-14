#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int V;
int path[10000][10000];
int path_end[10000];
int flag;

struct Edge {
    int dest;
    int weight;
    struct Edge* next;
};

// Structure to represent a node in the network
struct Node {
    int nodeID; // Node identifier
    int weight; // Weight limit of the node
    struct Edge* neighbors;
};

struct Network {
    int numNodes;
    struct Node** nodes;
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
    newNode->neighbors = NULL;
    return newNode;
}

// Function to create a network with a given number of nodes
struct Network* createNetwork(int numNodes) {
    struct Network* network = (struct Network*)malloc(sizeof(struct Network));
    network->numNodes = numNodes;

    network->nodes = (struct Node**)malloc(numNodes * sizeof(struct Node*));
    for (int i = 0; i < numNodes; ++i) {
        network->nodes[i] = createNode(-1, 0); // Initialize with invalid ID
    }

    return network;
}

int findNodeIndex(struct Network* network, int nodeID) {
    for (int i = 0; i < network->numNodes; ++i) {
        if (network->nodes[i]->nodeID == nodeID) {
            return i;
        }
    }
    // Return -1 if the node with the given ID is not found
    return -1;
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

// Function to add an edge to the adjacency list
void addEdge(struct Node* src, int dest, int weight) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = src->neighbors;
    src->neighbors = newEdge;
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
        path[ans_num][index - 1] = network->nodes[j]->nodeID;
        path_end[ans_num] = index;
        return;
    }
    index += 1;
    printPath(network, parent, parent[j], index, ans_num);
    path[ans_num][index - 1] = network->nodes[j]->nodeID;

}

void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements at start and end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move the pointers towards the center
        start++;
        end--;
    }
}

// Function to perform BFS and find the minimum total path node weight
int bfs(struct Network* network, int src, int dest, int ans_num) {
    int* visited = (int*)malloc(network->numNodes * sizeof(int));
    int* parent = (int* )malloc(network->numNodes * sizeof(int));
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

        struct Edge* current = network->nodes[u]->neighbors;
        while (current != NULL) {
            int v = current->dest;
            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                enqueue(queue, v);
            }
            
            current = current->next;
        }
    }
    if (parent[dest] == -1) {
        return 0;
    } else {
        // Path found, print the results and free memory
        printPath(network, parent, dest, path_index, ans_num);
        reverseArray(path[ans_num], path_end[ans_num]);
    }


    // Free allocated memory
    free(visited);
    free(parent);
    free(queue->array);
    free(queue);
    return 1;
}




// Function to add a connection between two nodes with a given weight
void addConnection(struct Network* network, int node1, int node2, int weight) {
    addEdge(network->nodes[node1], node2, weight);
    addEdge(network->nodes[node2], node1, weight);
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
struct TreeNode* buildTree(int front, int rear, int height, int *max) {
    if (height==-1) {
        return NULL;
    }

    int mid = (front + rear) / 2;
    struct TreeNode* root = TreecreateNode(front, mid, rear, height);//record front rear and mid and invertible height

    if(mid==front){
        root->left = buildTree(front, mid, -1, max);//leaf node break
        root->right = buildTree(mid, rear, -1,max);//leaf node break
    }
    else{
        height += 1;
        root->left = buildTree(front, mid, height,max);
        root->right = buildTree(mid, rear, height,max);
    }
    if(height>*(max)){
        *max = height;
    }
    return root;
}

// Function to recursively display the tree
void displayTree(struct TreeNode* root, int id[],int time, int roof) {
    if (root != NULL) {
       
        if (root->left != NULL) {
            displayTree(root->left,id,time,roof);
        }
        
        if (root->right != NULL) {
            displayTree(root->right,id,time,roof);
        }
        printf("%d %d ", id[root->front-1], id[root->rear-1]);
        if(root->left!=NULL&&root->right!=NULL){
            printf("%d %d %d %d ", id[root->left->front - 1], id[root->left->rear - 1], id[root->right->front - 1], id[root->right->rear - 1]);
        }
        printf("%d",time-root->height-roof);
        printf("\n");
    }
}

void ExamineTreeload(struct Network* network, struct TreeNode* root, int time, int **temp, int **limit, int id[], int *flag, int roof) {
    if (root != NULL) {
        //check out of bound
        if(root->height>time-2){//-1 because initial entangle
            *flag = 0;
            return;
        }
        if (root->left != NULL) {
            ExamineTreeload(network, root->left,time,temp, limit, id, flag, roof);
        }
        if (root->right != NULL) {
            ExamineTreeload(network, root->right,time,temp, limit, id, flag, roof);
        }


        //use path id to search the network order to check if overload
        for (int i = 0; i < V;i++){
            //for left value
            if(network->nodes[i]->nodeID==id[root->front-1]){
                temp[root->height+roof][i] += 1;
                //deal the leaf
                if(root->right==NULL&&root->left==NULL){
                    temp[root->height+roof+1][i] += 1;
                }
            }
            //for right value
            if(network->nodes[i]->nodeID==id[root->rear-1]){
                temp[root->height+roof][i] += 1;
                //deal the leaf
                if(root->right==NULL&&root->left==NULL){
                    temp[root->height+roof+1][i] += 1;
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
    int roof;

    struct AnsNode* next;
} AnsNode;


struct AnsNode* createAnsNode(struct TreeNode* root, int reqid, int req_time, int time, int roof) {
    struct AnsNode* newNode = (AnsNode*)malloc(sizeof(AnsNode));
    newNode->root = root;
    newNode->reqid = reqid;
    newNode->req_time = req_time;
    newNode->time = time;
    newNode->roof = roof;

    newNode->next = NULL;
    return newNode;
}

// Function to insert a tree node at the end of the linked list
void insertAnsNode(struct AnsNode** head, struct TreeNode* treeNode, int reqid, int req_time, int time, int roof) {
    struct AnsNode* newNode = createAnsNode(treeNode, reqid, req_time, time, roof);
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
        displayTree(head->root, path[head->req_time], head->time, head->roof);
        head = head->next;
    }
}

// Function to perform BFS



// Function to implement Dijkstra's algorithm to find minimum total path node weight
int findans(struct Network* network, int src, int dest, int time,int **load,int **limit, int req_time, int reqid, struct AnsNode **head){



    int heightmax=0;
    //build tree(by path order 1,2,3,4,5,6)
    struct TreeNode *root = buildTree(1, path_end[req_time], 0, &heightmax);

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
    int rf = 0;
    int flag = 1;
    for (int roof = 0; roof <= (time - heightmax - 2);roof++){
        ExamineTreeload(network, root, time, temp, limit, path[req_time], &flag, roof);
        for (int i = 0; i < time;i++){
            for (int k = 0; k < V;k++){ 
                if(temp[i][k] > limit[i][k]){
                    flag = 0;
                    break;
                }
                else{
                    flag = 1;
                }
            }
            if(flag==0){
                break;
            }
        }
        if(flag==1){
            rf = roof;
            break;
        }
        for (int i = 0; i < time;i++){
            for (int k = 0; k < V;k++){ 
                temp[i][k] = load[i][k];
            }
        }
    }
    
    //if no prob
    if (flag)
    {   
        for (int i = 0; i < time;i++){
            for (int k = 0; k < V;k++){
                load[i][k] = temp[i][k];
            }
        }
        insertAnsNode(head, root, reqid, req_time, time, rf);
    }

 


    for (int i = 0; i < time; i++) {
        free(temp[i]);
    }
    free(temp);



    return flag;
}



void sortpath(int req){
    int temp[req];
    for (int i = 0; i < 19;i++){
        temp[i] = path_end[i];
    }


    

    // Assuming path has been declared like this: int path[10000][10000];
    int new[10000][10000];
    int new_end[10000][10000];

    // Copy values based on temp
    for (int i = 0; i < req; i++) {
        for (int k = 0; k < req; k++) {

                
            printf("%d %d %d\n",k , temp[i], path_end[k]);
                

            /*
            if (temp[i] == path_end[k]) {

                
                for (int j = 0; j < path_end[k]; j++)
                {
                    new[i][j] = path[k][j];
                }
                path_end[k] = -2;
            }
            */
        }
        break;
    }
    // Copy values back to the original arrays

\

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
        int node_link1 = findNodeIndex(network, ID1);
        int node_link2 = findNodeIndex(network, ID2);
        if(node_link1!=-1&&node_link2!=-1){
            addConnection(network, node_link1, node_link2, 1);
        }
    }

    

    int startNodeID[req], endNodeID[req];
    int reqid[req];

    for (int i = 0; i < req;i++){

        scanf("%d", &reqid[i]);
        scanf("%d", &startNodeID[i]);
        scanf("%d", &endNodeID[i]);
    }

    for (int i = 0; i < req;i++){
        bfs(network, startNodeID[i], endNodeID[i], i);
    }


    sortpath(req);

    struct AnsNode *head = NULL;
    int ansnum = 0; 

 

    for (int i = 0; i < req;i++){

        //convert nodeID to node list num in network
        //and calc remain capacity
        int startNode=findNodeIndex(network, startNodeID[i]);
        int endNode=findNodeIndex(network, endNodeID[i]);
        if(startNode!=-1&&endNode!=-1){
                
            if(findans(network, startNode, endNode, time, load, limit, i, reqid[i], &head)){
                ansnum++;
            }
        }

    }
    
    printf("%d\n", ansnum);


    printans(head);

    return 0;
}
