#include <bits/stdc++.h>
using namespace std;
int a[150];
int s[20][20];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	freopen("seat.in","r",stdin);
	freopen("seat.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n*m;i++){
		cin>>a[i];
		if(a[i]==i){
			cout<<m<<' '<<n;
			return 0;
		}
		else if(a[i]==m*n-i+1){
			cout<<1<<' '<<1;
			return 0;
		}
	}
	int x=a[1];
	sort(a+1,a+m*n+1,cmp);
	int cmp=1;
	for(int i=1;i<=m;i++){
		if(i%2==1){
			for(int j=1;j<=n;j++){
				s[i][j]=a[cmp++];
			}
		}
		else if(i%2==0){
			for(int j=n;j>=1;j--){
				s[i][j]=a[cmp++];
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(s[i][j]==x){
				cout<<i<<' '<<j;
				return 0;
			}
		}
	}
	return 0;
} 
