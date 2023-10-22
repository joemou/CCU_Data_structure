#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000

//for queue
typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
} IntQueue;

void initializeIntQueue(IntQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isIntQueueEmpty(IntQueue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

int isIntQueueFull(IntQueue* queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void enqueueInt(IntQueue* queue, int value) {
    if (isIntQueueFull(queue)) {
        printf("Error: Queue is full\n");
        return;
    } else if (isIntQueueEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }

    queue->arr[queue->rear] = value;
}

int dequeueInt(IntQueue* queue) {
    int dequeuedValue;

    if (isIntQueueEmpty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    } else if (queue->front == queue->rear) {
        dequeuedValue = queue->arr[queue->front];
        queue->front = queue->rear = -1;
    } else {
        dequeuedValue = queue->arr[queue->front];
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    return dequeuedValue;
}

int frontInt(IntQueue* queue) {
    if (isIntQueueEmpty(queue)) {
        printf("Error: Queue is empty\n");
        return -1;
    }

    return queue->arr[queue->front];
}



// Structure for dynamic vector
typedef struct {
    int* arr;
    int capacity;
    int size;
} Vector;

// Initialize a dynamic vector
Vector* initVector() {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->arr = (int*)malloc(sizeof(int) * 2); // Initial capacity of 2
    v->capacity = 2;
    v->size = 0;
    return v;
}

// Function to find an element in the dynamic vector
int findElement(Vector* v, int key) {
    for (int i = 0; i < v->size; i++) {
        if (v->arr[i] == key)
            return i;
    }
    return -1; // Element not found
}

// Function to push an element into the dynamic vector
void pushElement(Vector* v, int element) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->arr = (int*)realloc(v->arr, sizeof(int) * v->capacity);
    }
    v->arr[v->size++] = element;
}

// Function to pop an element from the dynamic vector
void popElement(Vector* v) {
    if (v->size > 0) {
        v->size--;
    }
}

// Structure for linked list node
typedef struct Node {
    Vector* vec;
    struct Node* next;
} Node;

// Function to create a new node with an empty dynamic vector
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vec = initVector();
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the bottom of the linked list
void insertAtBottom(Node** head) {
    Node* newNode = createNode();
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete the nth node from the linked list
void deleteNodeAtN(Node** head, int n) {
    if (*head == NULL)
        return;
    if (n == 0) {
        Node* temp = *head;
        *head = temp->next;
        free(temp);
        return;
    }
    Node* temp = *head;
    for (int i = 0; i < n - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
        return;
    Node* nextNode = temp->next->next;
    free(temp->next);
    temp->next = nextNode;
}

// Function to peek at the first element
int peekFirstElement(Node* head) {
    if (head != NULL && head->vec->size > 0) {
        return head->vec->arr[0];
    }
    return -1; // Return -1 if the list is empty or vector is empty
}

// Function to print the dynamic vector of a node
void printVector(Vector* vec) {
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", vec->arr[i]);
    }
    printf("\n");
}

// Function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printVector(temp->vec);
        temp = temp->next;
    }
}

// Function to free memory allocated for the linked list
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp->vec->arr);
        free(temp->vec);
        free(temp);
    }
}



//func for update step
void updateRound(int oldPath[], int newPath[], int numNodes) {  

    //Iniatilize the first node of the route
    Node *head_route = createNode();
    insertAtBottom(&head_route);
    pushElement(head_route->vec, oldPath[0]);

    //Initailze route
    Node *temp = head_route;
    while(temp!=NULL){
        if(peekFirstElement(temp)!=-1){
            insertAtBottom(&head_route);
            pushElement(temp->next->vec, oldPath[peekFirstElement(temp)]);       
        }
        temp = temp->next;
    }
    //Record solitude node which is connected in new path
    IntQueue solitude_node;
    initializeIntQueue(&solitude_node);
    for (int i = 0; i < numNodes;i++){
        if(oldPath[i]==-1&&newPath[i]!=-1){
            enqueueInt(&solitude_node, i);
        }
    }
    //Link it to route linked list
    while(!isIntQueueEmpty(&solitude_node)){    
        int target = frontInt(&solitude_node);
        temp = head_route;
        int flag = 0;
        while (temp != NULL)
        {   
            //Find every route node vector which is same with newpath[target]. If there is, enqueue it .
            if (findElement(temp->vec, newPath[target])!=-1)
            {
                pushElement(temp->vec, target);
                dequeueInt(&solitude_node);
                flag = 1;
            }
            temp = temp->next;
        }
        //Cannont find it put it to the queue and do again
        if(flag==0){
            enqueueInt(&solitude_node,dequeueInt(&solitude_node));
        }
    }

    //Initialize the ans queue
    //Input the first Ans
    //Prune the route
    //Shortcut the route


    printList(head_route);


}

int main() {
    int oldPath[] = {7, 2, 9, 10, -1, -1, -1, 8, 1, 3, 11, -1};
    int newPath[] = {4, 6, 1, 2, 5, 3, 11, -1, -1, -1, -1, -1};
    int numNodes = 12;


    updateRound(oldPath, newPath, numNodes);
    
    return 0;
}
