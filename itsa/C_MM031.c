#include <stdio.h>
#include <math.h>

int main(){
  long long b;
  scanf("%lld", &b);



  long long sum = 0;

  for (long long i = 1; i <= b;i++){
    if(i%2==0&&i%3==0&&i%12!=0){
      sum += i;
    }
  }


  printf("%lld\n", sum);
}  