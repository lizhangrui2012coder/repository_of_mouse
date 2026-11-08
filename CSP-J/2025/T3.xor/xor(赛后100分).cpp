#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<20;
int best[maxn];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=maxn;i++) best[i]=-1e9;
	best[0]=0;
    int x=0,dp=0;
    for(int i=1,a;i<=n;i++){
		cin>>a;
		x^=a;
		int t=best[x^k];
		int nd=dp;
		if(t>-1e9) nd=max(nd,t+1);
		dp=nd;
		if(best[x]<dp) best[x]=dp;
	}
	cout<<dp;
	return 0;
}

