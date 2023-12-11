#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the tree
struct Node {
    int front;
    int mid;
    int rear;
    int height;
    struct Node *left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int front, int mid, int rear, int height) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->front = front;
    newNode->mid = mid;
    newNode->rear = rear;
    newNode->height = height;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to recursively build the tree
struct Node* buildTree(int front, int rear, int height) {
    if (height==-1) {
        return NULL;
    }

    int mid = (front + rear) / 2;
    struct Node* root = createNode(front, mid, rear, height);//record front rear and mid and invertible height

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
void displayTree(struct Node* root, int id[],int time) {
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

void ExamineTreeload(struct Node* root, int **load,int time) {
    if (root != NULL) {
       
        if (root->left != NULL) {
            ExamineTreeload(root->left,load,time);
        }
        
        if (root->right != NULL) {
            ExamineTreeload(root->right,load,time);
        }

    }
}

int main() {
    int nodes = 2;
    int id[]={0,2};
    int time = 7;


    int **load = (int **)malloc(nodes * sizeof(int *));
    for (int i = 0; i < nodes; i++) {
        load[i] = (int *)malloc(time * sizeof(int));
    }

    // Build the tree
    struct Node *root = buildTree(1, nodes, 0);

    // Display the tree
    displayTree(root,id,time);

    // Free the memory
    // Implement a function to free the allocated memory if needed

    return 0;
}
