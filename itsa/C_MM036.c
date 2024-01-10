#include <stdio.h>
#include <math.h>

int main(){  
  int a;
  scanf("%d", &a);
  if(a>=3&&a<=5){
    printf("Spring\n");
    return 0; 
  }
  else if(a>=6&&a<=8){
    printf("Summer\n");
    return 0; 
  }
  else if(a>=9&&a<=11){
    printf("Autumn\n");
    return 0; 
  }
  else{
    printf("Winter\n");
    return 0; 
  }

}  