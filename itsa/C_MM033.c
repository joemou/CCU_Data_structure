#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);
  int flag = 1;
  for (int i = 1; i < a;i++){
    int sum = 0;
    for (int j = 1; j < i ;j++){
      if(i%j==0){
        sum += j;
      }
    }
    if(sum==i){
      if(flag){
        printf("%d", i);
        flag = 0;
      }
      else{
        printf(" %d", i);
      }
      
    }
  }

  printf("\n");

  return 0; 
}  