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
    sort(a.begin()+1,a.begin()+n+1);
    int j=1,k=2;
    long long cnt=0;
    while(j<=n&&k<=n){
        if(a[k]-a[j]>c){
            j+=1;
        }
        else if(a[k]-a[j]<c){
            k+=1;
        }
        else{
            int cnt1=0,cnt2=0;
            while(a[j+cnt1]==a[j]&&j+cnt1<=n){
                cnt1++;
            }
            while(a[k+cnt2]==a[k]&&j+cnt2<=n){
                cnt2++;
            }
            cnt+=1LL*cnt1*cnt2;
            j+=cnt1;
            k+=cnt2;
        }
        
    }
    cout<<cnt;
    return 0;
}