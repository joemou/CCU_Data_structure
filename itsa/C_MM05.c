#include <stdio.h>
#include <math.h>

int main() {

    double sideLength, area;

    scanf("%lf", &sideLength);

    area = round((sideLength * sideLength)*10)/10;


    printf("%.1lf\n", area);

    return 0;
}
