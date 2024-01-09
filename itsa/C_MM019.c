#include <stdio.h>
#include <math.h>

int main() {

    int a;

    scanf("%d", &a);

    double cost;

    if(a<=800){
        cost = a*0.9;
    }
    else if(a>800&&a<1500){
        cost = a*0.9*0.9;
    }
    else{
        cost = a*0.9*0.79;
    }

    printf("%.1lf\n", cost);
}