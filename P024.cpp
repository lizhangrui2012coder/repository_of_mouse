#include <bits/stdc++.h>
using namespace std;
double a,b,c,d;
double ac(double x1){
    return a*x1*x1*x1+b*x1*x1+c*x1+d;
}

int main(){
    cin>>a>>b>>c>>d;
    for(double i=-100;i<=100;i++){
        if(ac(i)==0){
            printf("%.2f ",i);
        }
        if(i<i+1&&ac(i)*ac(i+1)<0){
            double x1=i,x2=i+1;

            while(x2-x1>1e-7){
                double mid=(x1+x2)/2;
                if(ac(x1)*ac(mid)<0){
                    x2=mid;
                }
                else{
                    x1=mid;
                }
            }
            printf("%.2f ",x1);
        }
    }
    
    return 0;
} 