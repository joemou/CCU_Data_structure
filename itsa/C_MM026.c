#include <stdio.h>
#include <math.h>

int main(){
  long long a;
  scanf("%lld", &a);


  for (long long i = 1; i <= a;i++){
    printf("%lld*%lld=%lld\n", i, i, i * i);
  }
}  