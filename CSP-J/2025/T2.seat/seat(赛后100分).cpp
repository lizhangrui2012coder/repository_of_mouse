#include <bits/stdc++.h>
using namespace std;
int n,m,cnt=0;
int a[110];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n>>m;
	cin>>a[1];
	for(int i=2;i<=n*m;i++){
		cin>>a[i];
		if(a[i]>a[1])
			cnt++;
	}
	sort(a+1,a+m*n+1,cmp);
	if(n==1){
		cout<<cnt+1<<" "<<1;
		return 0;
	} 
	int x=1,y=0;
	int num=0;
	for(int i=1;i<=cnt+1;i++){
		if(i%n==1){
			num++;
			y++;
		}
		else{
			if(num%2==1){
				x++;
			}
			else if(num%2==0){
				x--;
			}
		}
		
		
			
		
	}
	cout<<y<<' '<<x;
	return 0;
} 