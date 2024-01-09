#include <stdio.h>
#include <math.h>

int main() {


    int c=0, d=0;

    scanf("%d %d", &c, &d);

    printf("%d+%d=%d\n",c,d,c+d);
    printf("%d*%d=%d\n",c,d,c*d);
    printf("%d-%d=%d\n",c,d,c-d);
    if(c%d<0){
        printf("%d/%d=%d...%d\n",c,d,c/d-1,c-(d*(c/d-1)));
    }
    else{
        printf("%d/%d=%d...%d\n",c,d,c/d,c%d);
    }
    
    return 0;
}