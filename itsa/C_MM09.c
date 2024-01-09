    #include <stdio.h>
    #include <math.h>


    int main(){
        int a;

        scanf("%d", &a);

        long long ans=1;

        for (int i = 0; i < a;i++){
            ans = ans * 2;
        }
        if (a > 31)
        {
            printf("Value of more than 31\n");
        }
        else{
            printf("%lld\n", ans);
        }
        
    }