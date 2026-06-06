#include <bits/stdc++.h>
using namespace std;
int n,m,e;
vector<int> g[550];//构图 
bool vis[510]; //标记数组 
int match[510];//记录右点v被哪个左点占着
bool find(int u){
	for(auto v:g[u]){//遍历 
		if(vis[v])
			continue;
		vis[v]=1;
		if(match[v]==0){//如果没有->直接连接 
			match[v]=u;
			return true;
		}
		//如果有人占了->尝试能不能让它换一下位子->即(find(match[v]) 
		else if(find(match[v])){
			match[v]=u;
			return true;
		}
	}
	return false;
}
int main(){
	cin>>n>>m>>e;
	for(int i=1;i<=e;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);//不能双向构图 
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);//清空数组 
		if(find(i))
			ans++;
	}
	cout<<ans;
	return 0;
}
