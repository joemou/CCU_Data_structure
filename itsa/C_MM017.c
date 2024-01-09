#include <stdio.h>
#include <math.h>

int main() {

    int a, b;
    scanf("%d %d", &a, &b);
    int max;
    for (int i = 1; i < (a > b ? a : b);i++){
        if(a%i==0&&b%i==0){
            max = i;
        }
    }
    printf("%d\n", max);
}