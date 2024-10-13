20241013
Problem Formulation
Solution Algorithm Formulatiion
Not 1 to 1 Algorithm with full Implementation
Algorihtm with partial Implemntation

240713
 torch.nn nn.(Conv2d, BatchNorm2d,ReLU,Flattern,Linear)    in .cpp
Glitch package.json apt-get install nodejs enable-npm. unixcommand=>npm init      npm install      npm start     
const=[]  


240711
By multiplying matrix, changing innerproducts's Caucality(Conditinal probability) and RMS prop.cpp(und RMS prop API)'s relation (und ARIMA, GARCH)
Hyperbolic space code representation to apply on Stock, Bond price & Volatility forecasting

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
