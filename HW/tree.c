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
    struct Node* root = createNode(front, mid, rear, height);

    if(mid==front){
        root->left = buildTree(front, mid, -1);
        root->right = buildTree(mid, rear, -1);
    }
    else{
        root->left = buildTree(front, mid, height);
        root->right = buildTree(mid, rear, height);
    }
    return root;
}

// Function to recursively display the tree
void displayTree(struct Node* root, int id[]) {
    if (root != NULL) {
       
        if (root->left != NULL) {
            displayTree(root->left,id);
        }
        
        if (root->right != NULL) {
            displayTree(root->right,id);
        }
        printf("(%d,%d) ", id[root->front-1], id[root->rear-1]);
    }
}

int main() {
    int nodes = 5;
    int id[]={5,6,7,8,9};

    // Build the tree
    struct Node* root = buildTree(1, nodes, 1);

    // Display the tree
    displayTree(root,id);

    // Free the memory
    // Implement a function to free the allocated memory if needed

    return 0;
}
