#include <bits/stdc++.h>
using namespace std;
const int maxn=500010; 
int dfn[maxn];//初次见面时间 
int low[maxn];//能追溯到的最早祖先
int sizes[maxn];//以u为根的dfs字数大小 
long long ans[maxn]; //删掉与u相连的所有边后，不连通的点对数量 
int timer=0;//记录时间 
int n,m;//数组大小和询问次数
struct node{
	int to;
	int id;
};
vector<node> g[maxn];
void tarjan(int u,int fa_edge_id){
	dfn[u]=low[u]=++timer;
	sizes[u]=1;
	ans[u]=2LL*(n-1);//"LL"表示用"long long"计算 
	int sum=0;//当前已经找到的、删掉点 u 后会被
			  //单独切(零碎的一些点)出来的那些连通块，总共有多少个点。
	for(auto &e:g[u]){
		int v=e.to;
		int id=e.id;
		if(id==fa_edge_id)//跳过父边 
			continue;
		if(!dfn[v]){
			tarjan(v,id);
			sizes[u]+=sizes[v];//儿子子树大小加到父亲身上 
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){//如果死活回不到非父祖先->割点 
				ans[u]+=1LL*sizes[v]*(n-1-sizes[v]);
				//这一坨联通的东西大小为sizes[v]
				//去掉就是n-1-sizes[v](注意v是孤立点，不与任何边相连，要-1) 
				sum+=sizes[v]; //加上剩余点 
			}
		}
		else if(dfn[v]<dfn[u]){//返祖边 
			low[u]=min(low[u],dfn[v]);
		}	
	}
	//所有连通块都没有了，只剩剩余块->大小为n-1-sum 
	ans[u]+=1LL*(n-1-sum)*sum;
} 
int main(){ 
 	ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back({y,i});
		g[y].push_back({x,i});
	} 
	fill(dfn,dfn+n+1,0);
    fill(low,low+n+1,0);
    timer=0;
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			 tarjan(i,-1);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
} 
