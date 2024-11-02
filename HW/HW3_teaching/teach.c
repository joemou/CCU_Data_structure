#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int queueSize(struct queue* q) {
  if (isEmpty(q)) {
    return 0;
  } else {
    return q->rear - q->front + 1;
  }
}

void construct(int TimeSlots,int size,int **temp,int height,int **temp_carry,int Nodes,int **carry,int *carry_index,int *flag,int *move,int **carry_capacity){
  // temp歸零 用來畫路徑樹的圖 
  //temp carry 是用來儲存carry的值以便加上依temp這動作值看已沒有超過carry_capacity
  for (int p = 0; p < TimeSlots; p++)
    {
        for (int k = 0; k < size; k++)
        {
            temp[p][k] = 0;
        }
    }

    //create the tree in matrix 
    for (int j = 0; j < height; j++)
    {   temp[TimeSlots-j-1][0] = 1; 
        if(j<2){
            for (int z = 1; z < size-1;z++){
                temp[TimeSlots-j-1][z] = 2;
            }    
        }
        else{
            for (int z = 1; z < size-1;z++){
                if(z%((int)pow(2,j-1))==0){
                    temp[TimeSlots-j-1][z] = 2;
                }
            } 
        }
        temp[TimeSlots-j-1][size - 1] = 1;
    }

    //intial temp carry
    for (int y = 0; y < TimeSlots; y++) {
        for (int k = 0; k < Nodes; k++) {
            temp_carry[y][k]=carry[y][k];
        }
    }
    //put the tree to tempcarry to put into the real index matrix
    //將temp轉換成真正INDEEX放在TEMP CARRY裡看會部會超過
    for (int p = 0; p < TimeSlots; p++)
    {
        for (int k = 0; k < size; k++)
        { 
          if(temp[p][k]!=0){
            temp_carry[p-(*move)][carry_index[k]] += temp[p][k];
          }
        }
    }
    //檢查有沒有超過
    for (int p = 0; p < TimeSlots;p++){
      for (int k = 0; k < Nodes;k++){
        if(temp_carry[p][k]>carry_capacity[p][k]-1){
          *flag = 1;
          break;
        }
      }
    }


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
    int index_1=-1,index_2=-1;
    for (int k = 0; k < Nodes;k++){
      if(LinkEnd1==NodeID[k]){
        index_1 = k;
      }
      if(LinkEnd2==NodeID[k]){
        index_2 = k;
      }
    }
    addEdge(graph, index_1, index_2);
  }

  int ReqId[Req], ReqSrc_index[Req], ReqDst_index[Req];
  for (int i = 0; i < Req; i++) {
    int start, end;
    scanf("%d %d %d", &ReqId[i], &start, &end);


    for (int k = 0; k < Nodes;k++){
      if(start==NodeID[k]){
        ReqSrc_index[i] = k;
      }
      if(end==NodeID[k]){
        ReqDst_index[i] = k;
      }
    }
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
    bfs(graph, ReqSrc_index[i], ReqDst_index[i], &paths, &pathSizes);
  }

  // Display stored paths
  int size[Nodes];//path size
  for (int i = 0; i < pathSizes; i++) {
    size[i] = 0;
  
    for (int j = 0; j < Nodes; j++)
    {
        if (paths[i][j] == -1)
        {
            break; // Terminate the loop when encountering -1 in the path
        }
        size[i]++;
    }
  }

  int ans[Nodes];
  int ans_index = 0;
  int ans_matrix[pathSizes][TimeSlots][Nodes];
  for (int i = 0; i < pathSizes; i++) {
    height = 0;

    for (int y = 0; y < 100;y++){
        if(pow(2,y)>size[i]-2){
            height = y+2;
            break;
        }
    }

    if(height>TimeSlots){
        continue;
    }

    int *nowpath = paths[i];
    int** temp = (int**)malloc(TimeSlots * sizeof(int*));
    for (int j = 0; j < TimeSlots; j++) {
      temp[j] = (int*)malloc(size[j] * sizeof(int));
    }

    int carry_index[size[i]];

    //find true index on carry
    for (int k = 0; k < size[i];k++){
      int flag = 1;
      for (int l = 0; l < Nodes;l++){
        if(NodeID[l]==nowpath[k]){
          carry_index[k] = l;
          flag = 0;
          break;
        }
      }
      if(flag==1){
        printf("Not found");
      }
    }

    /*
    for (int k = 0; k < size[i];k++){
      printf("%d ", carry_index[k]);
    }
    printf("\n");
    */

    for (int p = 0; p < TimeSlots; p++)
    {
        for (int k = 0; k < size[i]; k++)
        {
            temp[p][k] = 0;
        }
    }

    //create the tree in matrix 
    for (int j = 0; j < height; j++)
    {   temp[TimeSlots-j-1][0] = 1; 
        if(j<2){
            for (int z = 1; z < size[i]-1;z++){
                temp[TimeSlots-j-1][z] = 2;
            }    
        }
        else{
            for (int z = 1; z < size[i]-1;z++){
                if(z%((int)pow(2,j-1))==0){
                    temp[TimeSlots-j-1][z] = 2;
                }
            } 
        }
        temp[TimeSlots-j-1][size[i] - 1] = 1;
    }

    //intial temp carry
    for (int y = 0; y < TimeSlots; y++) {
        for (int k = 0; k < Nodes; k++) {
            temp_carry[y][k]=carry[y][k];
        }
    }
    
  
    //put the tree to tempcarry to put into the real index matrix
    for (int p = 0; p < TimeSlots; p++)
    {
        for (int k = 0; k < size[i]; k++)
        { 
          if(temp[p][k]!=0){
            
            //printf("org%d x:%d y:%d plus value:%d",temp_carry[p][carry_index[k]],carry_index[k],p,temp[p][k]);
            temp_carry[p][carry_index[k]] += temp[p][k];
            //printf("after%d \n",temp_carry[p][carry_index[k]]);
            
          }
        }
    }
    
    /*
    printf("*\n");
    for (int p = 0; p < TimeSlots;p++){
        for (int k = 0; k < Nodes;k++){
            printf("%d ", temp_carry[p][k]);
        }
        printf("\n");
    }
    */
    
    


    //examine overload
    int flag = 0;

    for (int p = 0; p < TimeSlots;p++){
      for (int k = 0; k < Nodes;k++){
        if(temp_carry[p][k]>carry_capacity[p][k]){
          flag = 1;
          break;
        }
      }
    }

    //not over
    if(flag==0){
      for (int i = 0; i < TimeSlots; i++) {
        for (int k = 0; k < Nodes; k++) {
          carry[i][k]=temp_carry[i][k];
        }
      }

      
      //ans index is num of ans
      ans[ans_index] = i;//store path index
      for (int l = 0; l < TimeSlots; l++) {
        for (int k = 0; k < Nodes; k++) {
          ans_matrix[ans_index][l][k] = temp[l][k]; //bound Nodes is size[i]
        }
      }
      ans_index++;
    }

    for (int i = 0; i < TimeSlots; i++) {
      free(temp[i]);
    }
    free(temp);



  }

  printf("%d\n", ans_index);

  for (int k = 0; k < ans_index;k++){
    
    printf("%d ", ans[k]);
    for (int p = 0; p < size[ans[k]];p++){
      printf("%d ", paths[ans[k]][p]);
    }

    for (int t = 0; t < ans_index; t++) {
        struct queue* ansq = createQueue(); // Create a new queue for each iteration
        for (int p = 1; p < TimeSlots; p++) { // Start at level
            for (int g = 0; g < size[ans[t]]; g++) {
                if (ans_matrix[t][p][g] == 1) {
                    enqueue(ansq, paths[ans[t]][g]);
                } else if (ans_matrix[t][p][g] == 2) {
                    enqueue(ansq, paths[ans[t]][g]);
                    enqueue(ansq, paths[ans[t]][g]);
                }
            }
            while (!isEmpty(ansq)) {
                printf("%d ", dequeue(ansq));
                printf("%d ", dequeue(ansq));
                printf("%d\n", p + 1);
            }

            printf("\n");
        }
        // Don't forget to free the memory for the current queue
        free(ansq->items);
        free(ansq);
    }




    printf("\n");
  }

  



  return 0;
}
/*
  for (int k = 0; k < ans_index;k++){
    for (int p = 0; p < TimeSlots;p++){
      for (int g = 0; g < size[ans[ans_index]];g++){
        if(ans_matrix[k][p][g]==1){
          printf("%d")
        }
      }
      printf("\n");
    }
    
  }
*/

    /*
    printf("\n************\n");
    for (int p = 0; p < TimeSlots;p++){
        for (int k = 0; k < Nodes;k++){
            printf("%d ", carry[p][k]);
        }
        printf("\n");
    }
    printf("\n************\n");
    for (int p = 0; p < TimeSlots;p++){
        for (int k = 0; k < Nodes;k++){
            printf("%d ", carry_capacity[p][k]);
        }
        printf("\n");
    }
    printf("\n************\n");

    */

    /*

    for (int p = 0; p < TimeSlots;p++){
        for (int k = 0; k < size[i];k++){
            printf("%d ", temp[p][k]);
        }
        printf("\n");
    }

    for (int p = 0; p < TimeSlots;p++){
        for (int k = 0; k < Nodes;k++){
            printf("%d ", temp_carry[p][k]);
        }
        printf("\n");
    }
    */