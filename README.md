백준1929 1.Order of if statement 2.else?  3.when to introduce list and inumerative forloops
#include <stdio.h>
#include <stdbool.h>

bool Prim(int i) {
    if(i>=3){
        for(int j=3;j<i;j++){
            if(i%j==0){
                return false;
                break;
            }

            }else{
         return true;
        }
    }
     if(i<=1){
            return false;

        }
     if (i==2){
             return true;
              }
}

int main(){
    int a=0;
    int b=0;
    scanf("%d %d",&a,&b);
    for(int i=a;i<b;i++){
        if(Prim(i)==1){
            printf("%d",i);
        }
        else{
            continue;
        }
    }
    return 0;
}
