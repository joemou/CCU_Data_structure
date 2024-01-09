#include <stdio.h>
#include <math.h>

int main() {

    int long long x,y;

    scanf("%lld %lld", &x,&y);

    if(x<=100&&x>=0&&y<=100&&y>=0){
        printf("inside\n");
    }
    else{
        printf("outside\n");
    }


}