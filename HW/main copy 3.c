#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define debug printf("*");

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

// Function to check if the dynamic vector is empty
int vector_isEmpty(Vector* v) {
    return v->size == 0;
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
    for (int i = 0; temp != NULL && i < n - 1; i++) {
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

int Vector_dequeueElement(Vector* v) {
    if (v->size > 0) {
        int frontElement = v->arr[0];

        // Shift elements to the left to fill the gap
        for (int i = 0; i < v->size - 1; i++) {
            v->arr[i] = v->arr[i+1];
        }

        v->size--;

        // Adjust capacity if necessary (optional)
        if (v->size <= v->capacity / 4 && v->capacity > 2) {
            v->capacity /= 2;
            v->arr = (int*)realloc(v->arr, sizeof(int) * v->capacity);
        }

        return frontElement;
    } else {
        // Handle case when vector is empty
        // For example, you might choose to return a special value or throw an error.
        // Here, I'm returning -1 to indicate an empty vector.
        return -1;
    }
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

void copyVector(Vector* source, Vector* destination) {
    destination->size = source->size;
    destination->capacity = source->capacity;
    destination->arr = (int*)malloc(sizeof(int) * source->capacity);

    for (int i = 0; i < source->size; i++) {
        destination->arr[i] = source->arr[i];
    }
}


Node* copyLinkedList(Node* original) {
    if (original == NULL)
        return NULL;

    Node* newHead = createNode();  // Create a new node for the head
    Node* originalCurrent = original;
    Node* newCurrent = newHead;

    // Copy the vector content of the first node
    copyVector(originalCurrent->vec, newCurrent->vec);

    while (originalCurrent->next != NULL) {
        originalCurrent = originalCurrent->next;  // Move to the next node in the original list
        Node* newNode = createNode();  // Create a new node for the copy
        newCurrent->next = newNode;    // Link the new node to the new list
        newCurrent = newNode;          // Move to the next node in the new list

        copyVector(originalCurrent->vec, newNode->vec); // Copy the vector content
    }

    return newHead;
}




//func for update step
void updateRound(int oldPath[], int newPath[], int numNodes) {  

    //Iniatilize the first node of the route
    Node *head_route = createNode();
    Node *temp = head_route;
    insertAtBottom(&head_route);
    pushElement(head_route->vec, 0);


    //Initailze route
    
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

    int flag_with_isolated_node = 0;
    int ans_index = 0;
    // Initialize the ans queue
    IntQueue ans[numNodes];
    for (int i = 0; i < numNodes;i++){
        initializeIntQueue(&ans[i]);
    }
    for(int i=0;i<numNodes;i++){
        enqueueInt(&ans[ans_index],oldPath[i]);
    }
    ans_index++;

    // If exisits isolated node input the first Ans
    for (int i = 0; i < numNodes;i++){
        if(oldPath[i]==-1&&newPath[i]!=-1){
            flag_with_isolated_node = 1;
            break;
        }
    }
    if(flag_with_isolated_node){
        for (int i = 0; i < numNodes;i++){
            if(oldPath[i]==-1&&newPath[i]!=-1){
                enqueueInt(&ans[ans_index],newPath[i]);
            }
            else{
                enqueueInt(&ans[ans_index],oldPath[i]);
            }
        }
        ans_index++;
    }

    int ans_found = 0;

    //Prune and shortcut
    while(!ans_found){
        
        Node *last_head_route = copyLinkedList(head_route);
        //Prune the route
        //Prune calc distance
        int max_distance=-1;
        int max_distance_index_lowerbound=-1;
        int max_distance_index_upperbound=-1;
        for(int i=0;i<numNodes;i++){
            int lowerbound=i;
            int upperbound=newPath[i];
            int lowerbound_index=-1;
            int upperbound_index=-1;
            
            //Find lowerbound index in route
            int bound_index_count=0;
            temp=head_route;
            if(lowerbound==0){
                lowerbound_index=0;
            }
            else{
                while (temp!=NULL)
                {
                    if(findElement(temp->vec,lowerbound)!=-1){
                        lowerbound_index=bound_index_count;
                        break;
                    }
                    bound_index_count++;
                    temp=temp->next;
                }
            }

            //Find upperbound index in route
            bound_index_count=0;
            temp=head_route;
            while (temp!=NULL)
            {   
                //If newPath point to NULL
                if(upperbound==-1){
                    upperbound_index=lowerbound_index;
                    break;
                }
                else{
                    if(findElement(temp->vec,upperbound)!=-1){
                        upperbound_index=bound_index_count;
                        break;
                    }
                }

                bound_index_count++;
                temp=temp->next;
            }

            //Calc max distance or not
            if((upperbound_index-lowerbound_index)>max_distance){
                max_distance=upperbound_index-lowerbound_index;
                max_distance_index_lowerbound=lowerbound_index;
                max_distance_index_upperbound=upperbound_index;
            }

        }

        //Prune and Shortcut
        
        //Prune if index lowerbound is not the start point
        Node *temp2=head_route;
        temp=head_route;
        

        //move temp to lowerbound
        //start point and route start is same deal with it latter
        for(int i=0;i<max_distance_index_lowerbound;i++){
            temp=temp->next;
        }
        //move temp2 to upperbound
        for(int i=0;i<max_distance_index_upperbound;i++){
            temp2=temp2->next;
        }
        printf("+\n");
        printList(head_route);
        printf("=移動node=");
        printf("\n");
        printVector(temp->vec);
        printVector(temp2->vec);
        printf("\n");
        printf("====\n"); 
        //Prune
        //Temp data to temp2
        while(!vector_isEmpty(temp->vec)){
            pushElement(temp2->vec,Vector_dequeueElement(temp->vec));
        }
    
        //Shortcut
        temp=temp->next;
        while(temp!=temp2){
            

            int move_node=peekFirstElement(temp);
            int find_node=newPath[move_node];

            if(find_node==-1){
                    
            }
            else{
                Node *temp3=head_route;
                
                while(temp3!=NULL){
                        
                    if(findElement(temp3->vec,find_node)!=-1){
                        while(!vector_isEmpty(temp->vec)){
                            pushElement(temp3->vec,Vector_dequeueElement(temp->vec));
                            
                        }
                        break;
                    }
                    temp3=temp3->next;
                }    
            }
            temp=temp->next; 
        }


        //Delete node

        for(int i=0;i<max_distance;i++){
            deleteNodeAtN(&head_route,max_distance_index_lowerbound);
        }
        
        printf("delete\n");
        printList(head_route);
        printf("delete\n");
        
        printList(last_head_route);
        printf("\n");
        printList(head_route);
        

        //Insert ans from route
        temp=last_head_route;
        temp2=last_head_route;
        int arr[numNodes];
        //find_lowerbound
        for(int i=0;i<max_distance_index_lowerbound;i++){
            temp=temp->next;
        }
        for(int i=0;i<max_distance_index_upperbound;i++){
            temp2=temp2->next;
        }

        //intiailize from last ans
        for(int i=0;i<numNodes;i++){
            arr[i]=dequeueInt(&ans[ans_index-1]);//get value
            enqueueInt(&ans[ans_index-1],arr[i]);//put back
        }


        
        //prune
        arr[peekFirstElement(temp)]=newPath[peekFirstElement(temp)];
        for(int i=0;i<numNodes;i++){
            enqueueInt(&ans[ans_index],arr[i]);
        }
        ans_index++;

        printf("%d\n",ans_index);
        
        temp=temp->next;
        //Shortcut
        printVector(temp->vec);
        printVector(temp2->vec);
        
        int shortcut=0;
        while(temp!=temp2){
            shortcut=1;
            arr[peekFirstElement(temp)]=newPath[peekFirstElement(temp)];
            temp=temp->next;
        }
        if(shortcut){
            for(int i=0;i<numNodes;i++){    
                enqueueInt(&ans[ans_index],arr[i]);
            }
            ans_index++;
        }



        IntQueue k=ans[ans_index-1];

        for(int i=0;i<numNodes;i++){
          printf("%d ",dequeueInt(&k));
        }
        ans_found=1;
        IntQueue qtemp=ans[ans_index-1];
        for(int i=0;i<numNodes-1;i++){
            int k = dequeueInt(&qtemp);
            if(newPath[i]!=k){
                ans_found=0;
                break;
            }
        }

        
        
        printf("\n\n");
        
        printf("==%d %d %d==\n",max_distance,max_distance_index_lowerbound,max_distance_index_upperbound);


    }

    printf("%d\n",ans_index);
    for(int i=0;i<ans_index;i++){
        for(int j=0;j<numNodes;j++){
            printf("%d ", dequeueInt(&ans[i]));
        }
        printf("\n");
    }    

}

int main() {
    int numNodes=-1;
    
    scanf("%d",&numNodes);
    int oldPath[numNodes];
    int newPath[numNodes];

    for(int i=0;i<numNodes;i++){
        scanf("%d",&oldPath[i]);
    }
    for(int i=0;i<numNodes;i++){
        scanf("%d",&newPath[i]);
    }



    updateRound(oldPath, newPath, numNodes);
    return 0;
}
