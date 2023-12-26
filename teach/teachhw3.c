// BFS algorithm in C

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

struct queue {
  int items[SIZE];
  int front;
  int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
  int* visited;
};

// BFS algorithm
void bfs(struct Graph* graph, int startVertex) {
  struct queue* q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) {
    int currentVertex = dequeue(q);
    printf("Visited %d\n", currentVertex);

    struct node* temp = graph->adjLists[currentVertex];

    while (temp) {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
}

// Creating a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Creating a graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));
  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {

    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {

      q->front = q->rear = -1;
    }
  }
  return item;
}


int main() {

  int Nodes=-1, Links=-1, TimeSlots=-1, Req=-1;
  scanf("%d %d %d %d", &Nodes, &Links, &TimeSlots, &Req);
  struct Graph *graph = createGraph(Nodes);

  int **carry = (int **)malloc(TimeSlots * sizeof(int *));
  for (int i = 0; i < TimeSlots; i++) {
    carry[i] = (int *)malloc(Nodes * sizeof(int));
  }

  int **carry_capacity = (int **)malloc(TimeSlots * sizeof(int *));
  for (int i = 0; i < TimeSlots; i++) {
    carry_capacity[i] = (int *)malloc(Nodes * sizeof(int));
  }

  int NodeID[Nodes];
  int QuantumMemories[Nodes];
  for (int i = 0; i < Nodes;i++){
    scanf("%d %d", &NodeID[i], &QuantumMemories[i]);
  }

  for (int i = 0; i < TimeSlots; i++)
  {
    for (int k = 0; k < Nodes; k++)
    {
      carry[i][k] = 0;
    }
  }
  for(int i=0;i<TimeSlots;i++){
    for (int k = 0; k < Nodes;k++){
      carry_capacity[i][k] = QuantumMemories[k];
    }
  }

  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 4);
  addEdge(graph, 1, 3);
  addEdge(graph, 2, 4);
  addEdge(graph, 3, 4);


  bfs(graph, 0);

  return 0;
}