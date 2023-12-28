#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

struct queue {
  int* items;
  int front;
  int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
  int* visited;
  int* parent;
};

// BFS algorithm
void bfs(struct Graph* graph, int startVertex, int endVertex, int*** paths, int* pathSizes) {
  for (int i = 0; i < graph->numVertices; i++) {
    graph->parent[i] = -1; // Initialize parent array to -1
  }

  struct queue* q = createQueue();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) {
    int currentVertex = dequeue(q);

    if (currentVertex == endVertex) {
      // Found the end node, store the path
      int v = endVertex;


      // Traverse the parent pointers to determine the path size
      while (v != startVertex) {
        v = graph->parent[v];
      }

      // Allocate memory for the path
      (*paths) = realloc(*paths, (*pathSizes + 1) * sizeof(int*));
      (*paths)[*pathSizes] = malloc((graph->numVertices + 1) * sizeof(int));  // +1 for the sentinel value -1

      int index = 0;
      v = endVertex;

      // Store the path in forward order
      while (v != -1) {
          (*paths)[*pathSizes][index++] = v;
          v = graph->parent[v];
      }

      // Add sentinel value -1 at the end of the path
      (*paths)[*pathSizes][index] = -1;

      // Reverse the path in-place
      int start = 0, end = index - 1;
      while (start < end) {
          int temp = (*paths)[*pathSizes][start];
          (*paths)[*pathSizes][start] = (*paths)[*pathSizes][end];
          (*paths)[*pathSizes][end] = temp;
          start++;
          end--;
      }


      // Add sentinel value -1 at the end of the path
      (*paths)[*pathSizes][index] = -1;

      // Update pathSizes
      (*pathSizes)++;

    }

    struct node* temp = graph->adjLists[currentVertex];

    while (temp) {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        graph->parent[adjVertex] = currentVertex;
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
  graph->parent = malloc(vertices * sizeof(int));

  for (int i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
    graph->parent[i] = -1;
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

struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  q->items = malloc(SIZE * sizeof(int)); // Allocate memory for items array
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

// Print the contents of the queue (for debugging)
void printQueue(struct queue* q) {
  if (isEmpty(q)) {
    printf("Queue is empty\n");
  } else {
    printf("Queue contains: ");
    for (int i = q->front; i <= q->rear; i++) {
      printf("%d ", q->items[i]);
    }
    printf("\n");
  }
}

void load(int **temp,int x[],int *path){

}

int main()
{
  int Nodes = -1, Links = -1, TimeSlots = -1, Req = -1;
  scanf("%d %d %d %d", &Nodes, &Links, &TimeSlots, &Req);
  struct Graph* graph = createGraph(Nodes);

  int** carry = (int**)malloc(TimeSlots * sizeof(int*));
  for (int i = 0; i < TimeSlots; i++) {
    carry[i] = (int*)malloc(Nodes * sizeof(int));
  }

  int** carry_capacity = (int**)malloc(TimeSlots * sizeof(int*));
  for (int i = 0; i < TimeSlots; i++) {
    carry_capacity[i] = (int*)malloc(Nodes * sizeof(int));
  }

  int NodeID[Nodes];
  int x_coordinate[Nodes];
  int QuantumMemories[Nodes];
  for (int i = 0; i < Nodes; i++) {
    scanf("%d %d", &NodeID[i], &QuantumMemories[i]);
    x_coordinate[i] = NodeID[i];
  }

  for (int i = 0; i < TimeSlots; i++) {
    for (int k = 0; k < Nodes; k++) {
      carry[i][k] = 0;
    }
  }

  for (int i = 0; i < TimeSlots; i++) {
    for (int k = 0; k < Nodes; k++) {
      carry_capacity[i][k] = QuantumMemories[k];
    }
  }

  int LinkEnd1, LinkEnd2, ID;

  for (int i = 0; i < Links; i++) {
    scanf("%d %d %d", &ID, &LinkEnd1, &LinkEnd2);
    addEdge(graph, LinkEnd1, LinkEnd2);
  }

  int ReqId[Req], ReqSrc[Req], ReqDst[Req];
  for (int i = 0; i < Req; i++) {
    scanf("%d %d %d", &ReqId[i], &ReqSrc[i], &ReqDst[i]);
  }

  // Allocate memory for storing paths and their sizes
  int** paths = NULL;
  int pathSizes = 0;
  // Perform BFS for each query and store paths
  for (int i = 0; i < Req; i++) {
    // Reset visited and parent arrays for each query
    for (int v = 0; v < Nodes; v++) {
      graph->visited[v] = 0;
      graph->parent[v] = -1;
    }
    bfs(graph, ReqSrc[i], ReqDst[i], &paths, &pathSizes);
  }

  int** temp = (int**)malloc(TimeSlots * sizeof(int*));
  for (int i = 0; i < TimeSlots; i++) {
    temp[i] = (int*)malloc(Nodes * sizeof(int));
  }

  // Display stored paths
  for (int i = 0; i < pathSizes; i++) {
    printf("Path %d: ", i);
    for (int j = 0; j < Nodes; j++) {
      if (paths[i][j] == -1) {
        break;  // Terminate the loop when encountering -1 in the path
      }
      
      printf("%d ", paths[i][j]);
    }
    printf("\n");
    // Free memory for each individual path
    free(paths[i]);
  }

  
  return 0;
}
