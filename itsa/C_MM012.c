#include <stdio.h>
#include <math.h>

int main() {

    float m = 0;
    scanf("%f", &m);
    if(m / ((100 - (2.54 * 30))/100)>round(m / ((100 - (2.54 * 30))/100))){
        printf("%.0f\n", m / ((100 - (2.54 * 30))/100)+1);
    }
    else{
        printf("%.0f\n", m / ((100 - (2.54 * 30))/100));
    }
    
    return 0;
}