#include <bits/stdc++.h>
using namespace std;
int n;
struct Node{
	long long num;
	char cha;
}a[200010];

struct ac{
	long long start,end;
}key[200010];
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin>>n;
	long long sum=0;//表示S的长度 
	key[0].end=0;
	for(int i=1;i<=n;i++){
		cin>>a[i].num>>a[i].cha;
		key[i].start=key[i-1].end+1;
		key[i].end=key[i].start+a[i].num-1;
		sum+=a[i].num;
	}
	long long i=1,j=sum;//坐标
	long long x=1,y=n;//区间号 
	long long ans=0;
	long long midl,midr;
	if(sum%2==0){
		midl=sum/2;
		midr=sum/2+1;
	}
	else{
		midl=midr=sum/2+1;
	}
	while(i<=midl&&j>=midr){
		int l=key[x+1].start-i;
		int r=j-key[y-1].end;
		if(midl-i<l){
			l=midl-i;
		}
		if(j-midr<r){
			r=j-midr;
		}
		if(l<=r&&a[x].cha!=a[y].cha){
			i+=l;
			j-=l;
			x++;
			ans+=l;
		}
		else if(l>r&&a[x].cha!=a[y].cha){
			i+=r;
			j-=r;
			y--;
			ans+=r;
		}
		if(l<=r&&a[x].cha==a[y].cha){
			i+=l;
			j-=l;
			x++;
		}
		else if(l>r&&a[x].cha==a[y].cha){
			i+=r;
			j-=r;
			y--;
		}
	}
	cout<<ans;
	return 0;
}
