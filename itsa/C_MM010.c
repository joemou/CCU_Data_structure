#include <stdio.h>
#include <math.h>

int main() {

    double sideLength, area;

    scanf("%lf", &sideLength);

    area = round((sideLength*9/5+32)*10)/10;


    printf("%.1lf\n", area);

    return 0;
}