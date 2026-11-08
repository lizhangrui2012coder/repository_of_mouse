#include <bits/stdc++.h>
using namespace std;
int n,m;
long long a[200010];
long long dp[200010];//m为j时的最大按位与
bool cmp(int x,int y){
	return x>y;
} 
int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	cin>>n>>m;
	long long mx=0;
	for(int i=1;i<=n;i++){ 
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	cout<<a[m];
	return 0;
}
