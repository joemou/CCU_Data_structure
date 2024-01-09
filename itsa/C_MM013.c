#include <stdio.h>
#include <math.h>

int main() {

    int a, b, c, d;

    scanf("%d %d", &a, &b);
    scanf("%d %d", &c, &d);


    int time1 = a * 60 + b;
    int time2 = c * 60 + d;

    int diff = time2 - time1;
    int cost;

    if(diff<=120){
        cost = diff / 30 * 30;
    }
    else if(diff<=120&&diff<=240){
        cost = 120 + (diff - 120) / 30 * 40;
    }
    else{
        cost = 120 + 160 + (diff - 240) / 30 * 60;
    }

    printf("%d\n", cost);
}