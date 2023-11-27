#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 10000

//for int queue
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

int sizeOfIntQueue(IntQueue* queue) {
    if (isIntQueueEmpty(queue)) {
        return 0;
    } else {
        return (queue->rear - queue->front + MAX_SIZE) % MAX_SIZE + 1;
    }
}


//for node queue
typedef struct {
    int x;
    int y;
    int dir;
} Node;

typedef struct QueueNode{
    Node data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode *front, *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, Node val) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = val;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Node dequeue(Queue *q) {
    if (isEmpty(q)) {
        Node emptyNode = {-1, -1, -1};
        return emptyNode;
    }
    QueueNode* temp = q->front;
    Node val = temp->data;
    q->front = q->front->next;
    free(temp);
    return val;
}


typedef struct Stack {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

int isEmptystack(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmptystack(stack)) {
        printf("Stack underflow\n");
        return -1; // Return a sentinel value indicating an error
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack) {
    if (isEmptystack(stack)) {
        printf("Stack is empty\n");
        return -1; // Return a sentinel value indicating an error
    }
    return stack->data[stack->top];
}



int isValid(int x, int y, int n, int** maze) {
    return (x >= 0 && y >= 0 && x < n && y < n && maze[x][y] == 0);
}

void findPath(int** maze, int n, Node start, Node end, Node start2, Node end2, int flag, IntQueue *ans) {
    
    //return if invalid start and end
    if(!isValid(start.x, start.y, n, maze)||!isValid(start2.x, start2.y, n, maze)||!isValid(end.x, end.y, n, maze)||!isValid(end2.x, end2.y, n, maze)){
        return;
    }

    Stack s;
    initialize(&s);
    Queue q;
    initQueue(&q);

    //if same point
    if(start.x==end.x&&start.y==end.y&&flag){
        return findPath(maze, n, start2, end2, start, end, 0,  ans);
    }

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    Node visited[n][n];
    //initial
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j].x = -1;
            visited[i][j].y = -1;
            visited[i][j].dir = -1;
        }
    }


    visited[start.x][start.y] = start;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        Node curr = dequeue(&q);

        if (curr.x == end.x && curr.y == end.y) {
            // Found the end point, reconstruct the path
            while (curr.x != start.x || curr.y != start.y) {
                push(&s, curr.dir);
                curr = visited[curr.x][curr.y];
            }

            while(!isEmptystack(&s)){
                enqueueInt(ans, pop(&s));
            }
            

            if(flag){
                IntQueue temp = *ans;
                while(!isIntQueueEmpty(&temp)){
                    int i = dequeueInt(&temp);
                    if(isValid(start2.x+dx[i], start2.y+dy[i], n, maze)){
                        start2.x+=dx[i];
                        start2.y+=dy[i];

                        if((start2.x==end.x&&start2.y==end.y)||(start2.x==end2.x&&start2.y==end2.y)){
                            while(!isIntQueueEmpty(ans)){
                                dequeueInt(ans);
                            }
                            return;
                        }
                    }
                }
                return findPath(maze, n, start2, end2, start, end, 0, ans);
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            if (isValid(newX, newY, n, maze) && visited[newX][newY].x == -1) {
                if(flag==1 && newX == end2.x && newY == end2.y){
                    return;
                }
                visited[newX][newY] = curr;
                Node nextNode = {newX, newY, i};
                enqueue(&q, nextNode);
            }
        }
    }
    //no path clean ans
    while(!isIntQueueEmpty(ans)){
        dequeueInt(ans);
    }
    return;
}

int main() {
    int n;
    scanf("%d", &n);

    int** maze = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        maze[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[j][n-1-i]);
        }
    }

    Node start1, start2, end1, end2;

    scanf("%d %d %d %d", &start1.x, &start1.y, &start2.x, &start2.y);

    scanf("%d %d %d %d", &end1.x, &end1.y, &end2.x, &end2.y);

 

    IntQueue q[4];

    initializeIntQueue(&q[0]);
    initializeIntQueue(&q[1]);
    initializeIntQueue(&q[2]);
    initializeIntQueue(&q[3]);
    
    if(((start1.x==end1.x&&start1.y==end1.y)&&(start2.x==end2.x&&start2.y==end2.y))||((start1.x==end2.x&&start1.y==end2.y)&&(start2.x==end1.x&&start2.y==end1.y))){
        return 0;
    }
    else if(start1.x==end1.x&&start1.y==end1.y){
        findPath(maze, n, start1, end1, start2, end2, 1, &q[0]);
    }
    else if(start2.x==end2.x&&start2.y==end2.y){
        findPath(maze, n, start2, end2, start1, end1, 1, &q[1]);
    }
    else if(start1.x==end2.x&&start1.y==end2.y){
        findPath(maze, n, start1, end2, start2, end1, 1, &q[2]);
    }
    else if(start2.x==end1.x&&start2.y==end1.y){
        findPath(maze, n, start2, end1, start1, end2, 1, &q[3]);
    }
    else{
        findPath(maze, n, start1, end1, start2, end2, 1, &q[0]);
        findPath(maze, n, start2, end2, start1, end1, 1, &q[1]);
        findPath(maze, n, start1, end2, start2, end1, 1, &q[2]);
        findPath(maze, n, start2, end1, start1, end2, 1, &q[3]);
    }

    
    int min = 999999999;
    int index = -1;
    for(int i = 0; i<4 ; i++){
        if(min > sizeOfIntQueue(&q[i])&&!isIntQueueEmpty(&q[i])){
            min = sizeOfIntQueue(&q[i]);
            index = i;
        }
    }

    while(!isIntQueueEmpty(&q[index])){
        printf("%d",dequeueInt(&q[index]));
    }

    for (int i = 0; i < n; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}