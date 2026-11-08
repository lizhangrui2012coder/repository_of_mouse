#include <bits/stdc++.h>
using namespace std;
int n;
long long k;
vector <long long> a;
bool flag1=1,flag2=1,flag3=1; 
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	cin>>n>>k;
	a.resize(n+1,0);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=1)
			flag1=0;
		else if(a[i]>=2)
			flag2=0;
		else if(a[i]>=256)
			flag3=0;
	}
	if(flag1){
		int sum=0;
		int i=2;
		while(n>0){
			sum+=n/i;
			i*=2;
		}
		return 0;
	}
	
		int cnt=0;
		
		for(int i=1;i<=n;i++){
			long long sum=a[i];
			for(int j=i;j<=n;j++){
				if(sum==k){				
					cnt++;
				}
				sum=(sum^a[j]);
			}
		}
		cout<<cnt;
	
	
	
	return 0;
} 
