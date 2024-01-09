#include <stdio.h>
#include <math.h>

int main() {

    int long long sec;

    scanf("%lld", &sec);

    printf("%lld days\n", sec/(24*60*60));
    printf("%lld hours\n", (sec % (24*60*60))/3600);
    printf("%lld minutes\n", sec%3600/60);
    printf("%lld seconds\n", sec%60);
}