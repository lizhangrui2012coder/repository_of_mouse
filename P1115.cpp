#include <bits/stdc++.h>
using namespace std;
int n;
int dp[200010];
int a[200010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        dp[i]=max(a[i],dp[i-1]+a[i]);
    }
    int ans=-1e9;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans;
    return 0;
}