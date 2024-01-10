#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);

  int flag = 1;
  for (int j = 2; j < a ;j++){
    if(a%j==0){
      flag = 0;
      break;
    }
  }
  if(flag){
    printf("YES\n");
  }
  else{
    printf("NO\n");
  }
  return 0; 
}  