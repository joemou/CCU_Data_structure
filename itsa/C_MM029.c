#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);
  int max = 0;
  for (int i = 1; i < a;i++){
    int flag = 1;
    for (int j = 2; j < i ;j++){
      if(i%j==0){
        flag = 0;
        break;
      }
    }
    if(flag){
      max = i;
    }
  }

  printf("%d\n", max);

  return 0; 
}  