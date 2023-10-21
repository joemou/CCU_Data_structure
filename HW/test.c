#include <stdio.h>



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
