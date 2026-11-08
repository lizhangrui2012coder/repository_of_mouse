#include <bits/stdc++.h>
using namespace std;
int t,m;
int dp[1010];
struct Node{
    int v,c;
}a[1010];
int main(){
    cin>>t>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i].c>>a[i].v;
    }
    for(int i=1;i<=m;i++){
        for(int j=t;j>=a[i].c;j--){
            dp[j]=max(dp[j],dp[j-a[i].c]+a[i].v);
        }
    }
    cout<<dp[t];
    return 0;
}