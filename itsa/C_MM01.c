#include <stdio.h>
#include <math.h>


int main(){
    float a, b, c;

    scanf("%f %f %f", &a, &b, &c);

    printf("Trapezoid area:%.1f\n", (a + b) * c / 2);
}