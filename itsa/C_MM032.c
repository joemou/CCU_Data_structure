#include <stdio.h>
#include <math.h>

int main(){
  long long b;
  scanf("%lld", &b);

  int x = b / 100;
  int y = b / 10-(10*x);
  int z = b % 10;

  if(b==(pow(x,3)+pow(y,3)+pow(z,3))){
    printf("Yes\n");
  }
  else{
    printf("No\n");
  }



}  