#include <stdio.h>
#include <stdlib.h>

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

int main() {
    VectorOfVectors myVector;
    initVectorOfVectors(&myVector, 5);

    for (int i = 0; i < 5; i++) {
        IntVector* intVec = (IntVector*)malloc(sizeof(IntVector));
        initIntVector(intVec, 5);
        for (int j = 0; j < 5; j++) {
            pushBackInt(intVec, i * 5 + j);
        }
        pushBackVector(&myVector, intVec);
    }

    for (size_t i = 0; i < myVector.size; i++) {
        IntVector* intVec = myVector.data[i];
        for (size_t j = 0; j < intVec->size; j++) {
            printf("%d ", intVec->data[j]);
        }
        freeIntVector(intVec);
        free(intVec);
        printf("\n");
    }

    freeVectorOfVectors(&myVector);

    return 0;
}
