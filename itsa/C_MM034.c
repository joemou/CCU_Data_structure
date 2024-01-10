#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);
  int flag = 1;
  for (int i = 1; i <= a;i++){

    if(a%i==0){
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