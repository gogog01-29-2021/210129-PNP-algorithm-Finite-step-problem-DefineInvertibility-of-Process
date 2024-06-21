#include <stdio.h>

bool Prim(int i){
    if(i>=2){
        if(i%2==1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
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