#include <stdio.h>
#include <math.h>

int main() {

    double x,y;

    scanf("%lf %lf", &x,&y);

    

    if(x*x+y*y<=40000){
        printf("inside\n");
    }
    else{
        printf("outside\n");
    }


}