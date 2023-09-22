#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1000

//tran ans
int ans[100000]={-1};
int first = 0;
int ans2[100000]={-1};
int first2 = 0;
int flag = 1;


typedef struct {
    int x;
    int y;
    int dir;
} Node;

//for queue
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

void findPath(int** maze, int n, Node start, Node end, Node start2, Node end2) {
    
    
    if(!isValid(start.x, start.y, n, maze)&&!isValid(!start2.x, start2.y, n, maze)&&!isValid(!end.x, !end.y, n, maze)&&!isValid(!end2.x, !end2.y, n, maze)){
        return;
    }
    
    if(start.x==end.x&&start.y==end.y&&flag){
        return findPath(maze, n, start2, end2, start, end);
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
    Queue q;
    initQueue(&q);

    visited[start.x][start.y] = start;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        Node curr = dequeue(&q);

        if (curr.x == end.x && curr.y == end.y) {
            // Found the end point, reconstruct the path
            while (curr.x != start.x || curr.y != start.y) {
                if(flag){
                    ans[first++] = curr.dir;//tran ans
                }
                else{
                    ans2[first2++] = curr.dir;//tran ans
                }
                curr = visited[curr.x][curr.y];
            }

            if(start2.x==end2.x&&start2.y==end2.y){
                for(int i = first-1 ; i>=0 ; i--){
                    printf("%d",ans[i]);
                }
                return;
            }

            if(flag){
                flag=0;
                for(int i = first-1 ; i>=0 ; i--){
                    if(isValid(start2.x+dx[ans[i]], start2.y+dy[ans[i]], n, maze)){
                        start2.x+=dx[ans[i]];
                        start2.y+=dy[ans[i]];
                    }
                }
                return findPath(maze, n, start2, end2, start, end);//strat 1 end 1 no use
            }

            for(int i = first-1 ; i>=0 ; i--){
                printf("%d",ans[i]);
            }
            for(int i = first2-1 ; i>=0 ; i--){
                printf("%d",ans2[i]);
            }
            
            printf("\n***\n");

            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            if (isValid(newX, newY, n, maze) && visited[newX][newY].x == -1) {
                visited[newX][newY] = curr;
                Node nextNode = {newX, newY, i};
                enqueue(&q, nextNode);
            }
        }
    }
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

    //calc distance

    Stack s1,s2,s3,s4;

    findPath(maze, n, start1, end1, start2, end2);
    first = 0;
    first2 = 0;
    flag = 1;
    findPath(maze, n, start2, end2, start1, end1);
    first = 0;
    first2 = 0;
    flag = 1;
    findPath(maze, n, start1, end2, start2, end1);
    first = 0;
    first2 = 0;
    flag = 1;
    findPath(maze, n, start2, end1, start1, end2);
    
    for (int i = 0; i < n; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}