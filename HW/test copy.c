#include <stdio.h>

#define MAX_SIZE 100

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

void initialize_route(){

   //initial update path
    route[0] = oldPath[0];

    for (int i = 0; i < numNodes - 1; i++){
        route[i + 1] = oldPath[route[i]];
    }


}

void initialize_ans(int ***ans){

    for (int i = 0; i < numNodes;i++){
        if(oldPath[i]!=-1){
            update[i] = oldPath[i];
        }
        else{
            update[i] = newPath[i];
        }
    }

}

//func for update step
void updateRound(int oldPath[], int newPath[], int numNodes, IntQueue* ans[]) {  
    int route[numNodes][num];
    int update[numNodes];
    int flag = 0;



   

    


 

    while (flag == 0)
    {
        

        for()

        flag = 1;
    }
}

int main() {
    int oldPath[] = {7, 2, 9, 10, -1, -1, -1, 8, 1, 3, 11, -1};
    int newPath[] = {4, 6, 1, 2, 5, 3, 11, -1, -1, -1, -1, -1};
    int numNodes = 12;

    IntQueue ans[numNodes];

    for (int i = 0; i < numNodes;i++){
        initializeIntQueue(&ans[i]);
    }

    updateRound(oldPath, newPath, numNodes, &ans[]);
    
    return 0;
}
