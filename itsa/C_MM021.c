#include <stdio.h>
#include <math.h>

int main(){
  int n;
  scanf("%d", &n);
  long long sum = 1;
  while(n!=0){
    sum *= n;
    n -= 1;
  }
  printf("%lld\n",sum);
}  