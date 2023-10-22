#include <stdio.h>
#include <stdlib.h>

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

int main() {
    Node* head = NULL;

    insertAtBottom(&head);
    insertAtBottom(&head);
    insertAtBottom(&head);

    // Push elements into the dynamic vector of the first node
    pushElement(head->vec, 10);
    pushElement(head->vec, 20);
    pushElement(head->vec, 30);

    // Print the linked list
    printf("Linked List:\n");
    printList(head);

    // Delete the second node
    deleteNodeAtN(&head, 1);

    // Print the modified linked list
    printf("\nLinked List after deleting the second node:\n");
    printList(head);

    // Free memory
    freeList(head);

    return 0;
}




