#include <stdio.h>
#include <math.h>

int main(){
  long long a,b;
  scanf("%lld %lld", &a, &b);

  if(a>b){
    int temp = a;
    a = b;
    b = temp;
  }

  int sum = 0;

  for (int i = a; i <= b;i++){
    sum += i;
  }

  printf("%d\n", sum);
}  