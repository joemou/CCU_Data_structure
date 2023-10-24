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

int main() {
    IntQueue myIntQueue;
    initializeIntQueue(&myIntQueue);
    enqueueInt(&myIntQueue, 10);
    enqueueInt(&myIntQueue, 20);
    enqueueInt(&myIntQueue, 30);

    printf("Front element: %d\n", frontInt(&myIntQueue));

    printf("Dequeued element: %d\n", dequeueInt(&myIntQueue));
    printf("Dequeued element: %d\n", dequeueInt(&myIntQueue));
    printf("Dequeued element: %d\n", dequeueInt(&myIntQueue));

    printf("Is queue empty? %s\n", isIntQueueEmpty(&myIntQueue) ? "Yes" : "No");

    return 0;
}
