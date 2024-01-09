#include <stdio.h>
#include <math.h>

int main() {

    int a;
    int c=0, d=0;

    scanf("%d", &a);

    while(a/10!=0){
        a = a - 10;
        c++;
    }
    while(a/5!=0){
        a = a - 5;
        d++;
    }

    printf("NT10=%d\nNT5=%d\nNT1=%d\n", c, d, a);
    return 0;
}