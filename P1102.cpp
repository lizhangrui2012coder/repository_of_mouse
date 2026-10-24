#include <bits/stdc++.h>
using namespace std;
int n;
long long c;
vector<long long> a;
int main(){
    cin>>n;
    cin>>c;
    a.resize(n+10);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a.begin()+1,a.end());
    int j=1,k=2;
    long long cnt=0;
    while(true){
        if(a[k]-a[j]>c){
            j+=1;
        }
        else if(a[k]-a[j]<c){
            k+=1;
            if(k>n){
                break;
            }
        }
        else{
            cnt++;
            k++;
        }
        
    }
    cout<<cnt;
    return 0;
}