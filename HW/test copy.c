#include <stdio.h>

//func for vector
typedef struct {
    int* data;
    size_t size;
} IntVector;

typedef struct {
    IntVector** data;
    size_t size;
} VectorOfVectors;

void initIntVector(IntVector* vec, size_t capacity) {
    vec->data = (int*)malloc(capacity * sizeof(int));
    vec->size = 0;
}

void pushBackInt(IntVector* vec, int value) {
    vec->data[vec->size++] = value;
}

void initVectorOfVectors(VectorOfVectors* vec, size_t capacity) {
    vec->data = (IntVector**)malloc(capacity * sizeof(IntVector*));
    vec->size = 0;
}

void pushBackVector(VectorOfVectors* vec, IntVector* value) {
    vec->data[vec->size++] = value;
}

void freeIntVector(IntVector* vec) {
    free(vec->data);
    vec->size = 0;
}

void freeVectorOfVectors(VectorOfVectors* vec) {
    free(vec->data);
    vec->size = 0;
}


//func for update step
void updateRound(int oldPath[], int newPath[], int numNodes) {  
    int route[numNodes];
    int update[numNodes];
    int flag = 0;


    //initial update
    for (int i = 0; i < numNodes;i++){
        if(oldPath[i]!=-1){
            update[i] = oldPath[i];
        }
        else{
            update[i] = newPath[i];
        }
    }

    


    //initial update path
    route[0] = oldPath[0];

    for (int i = 0; i < numNodes - 1; i++){
        route[i + 1] = oldPath[route[i]];
    }

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
    
    updateRound(oldPath, newPath, numNodes);
    
    return 0;
}
