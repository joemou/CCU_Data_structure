#include <stdio.h>
#include <math.h>

int main(){
  int hour, wage;
  double sum = 0;
  scanf("%d %d", &hour, &wage);

  if(hour<=60){
    sum += wage * hour;
  }
  else if(hour>60&&hour<=120){
    sum += wage * 60 + (hour - 60) * wage*1.33;
  }
  else{
    sum += wage * 60 + (hour - 120) * wage * 1.66 +60*wage*1.33;
  }

  printf("%.1lf\n", sum);
}