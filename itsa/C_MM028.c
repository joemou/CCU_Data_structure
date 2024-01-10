#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);
  int flag = 1;

  for (int i = 1; i <= a;i++){
    if(i%5==0&&i%7==0){
      if(flag==1){
        printf("%d", i);
        flag = 0;
      }
      else{
        printf(" %d", i);
      }
      
    }
  }
  printf("\n");
}  