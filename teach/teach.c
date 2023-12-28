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

// Define a structure to represent a path
struct Path {
    int* nodes;
    int length;
};

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    q->items = malloc(SIZE * sizeof(int)); // Allocate memory for items array
    return q;
}

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

int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

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

void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void bfs(struct Graph* graph, int startVertex, int endVertex, struct Path*** paths, int* pathSizes) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->parent[i] = -1;
    }

    struct queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);

        if (currentVertex == endVertex) {
            int v = endVertex;
            while (v != startVertex) {
                v = graph->parent[v];
            }

            (*paths) = realloc(*paths, (*pathSizes + 1) * sizeof(struct Path*));
            (*paths)[*pathSizes] = malloc(sizeof(struct Path));

            int index = 0;
            v = endVertex;
            while (v != -1) {
                (*paths)[*pathSizes]->nodes = realloc((*paths)[*pathSizes]->nodes, (index + 1) * sizeof(int));
                (*paths)[*pathSizes]->nodes[index++] = v;
                v = graph->parent[v];
            }

            (*paths)[*pathSizes]->length = index;

            int start = 0, end = index - 1;
            while (start < end) {
                int temp = (*paths)[*pathSizes]->nodes[start];
                (*paths)[*pathSizes]->nodes[start] = (*paths)[*pathSizes]->nodes[end];
                (*paths)[*pathSizes]->nodes[end] = temp;
                start++;
                end--;
            }

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

int comparePaths(const void* a, const void* b) {
    return (*(struct Path**)a)->length - (*(struct Path**)b)->length;
}

int main() {
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
    int QuantumMemories[Nodes];
    for (int i = 0; i < Nodes; i++) {
        scanf("%d %d", &NodeID[i], &QuantumMemories[i]);
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
        int index_1 = -1, index_2 = -1;
        for (int k = 0; k < Nodes; k++) {
            if (LinkEnd1 == NodeID[k]) {
                index_1 = k;
            }
            if (LinkEnd2 == NodeID[k]) {
                index_2 = k;
            }
        }
        addEdge(graph, index_1, index_2);
    }

    int ReqId[Req], ReqSrc_index[Req], ReqDst_index[Req];
    for (int i = 0; i < Req; i++) {
        int start, end;
        scanf("%d %d %d", &ReqId[i], &start, &end);

        for (int k = 0; k < Nodes; k++) {
            if (start == NodeID[k]) {
                ReqSrc_index[i] = k;
            }
            if (end == NodeID[k]) {
                ReqDst_index[i] = k;
            }
        }
    }

    struct Path** paths = NULL;
    int pathSizes = 0;

    for (int i = 0; i < Req; i++) {
        for (int v = 0; v < Nodes; v++) {
            graph->visited[v] = 0;
            graph->parent[v] = -1;
        }
        bfs(graph, ReqSrc_index[i], ReqDst_index[i], &paths, &pathSizes);
    }

    qsort(paths, pathSizes, sizeof(struct Path*), comparePaths);

    printf("Sorted Paths:\n");
    for (int i = 0; i < pathSizes; i++) {
        printf("Path %d (Length %d): ", i, paths[i]->length);
        for (int j = 0; j < paths[i]->length; j++) {
            printf("%d ", NodeID[paths[i]->nodes[j]]);
        }
        printf("\n");
        free(paths[i]->nodes);
        free(paths[i]);
    }

    // Free memory for the paths array
    free(paths);

    return 0;
}
