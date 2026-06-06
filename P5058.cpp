#include <bits/stdc++.h>
using namespace std;
const int maxn=500010; 
int dfn[maxn];//初次见面时间 
int low[maxn];//能追溯到的最早祖先
int timer=0;//记录时间 
int cnt[maxn];
struct node{
	int to;
	int id;
};
int n; 
int a,b;
vector<node> g[maxn];
int ans=1e9;
void tarjan(int u,int fa_edge_id){
	dfn[u]=low[u]=++timer;
	cnt[u]=(u==a)+(u==b);
	for(auto &e:g[u]){
		int v=e.to;
		int id=e.id;
		if(id==fa_edge_id)//跳过父边 
			continue;
		if(!dfn[v]){
			tarjan(v,id);
			low[u]=min(low[u],low[v]);
			cnt[u]+=cnt[v];
			if(low[v]>=dfn[u]&&cnt[v]==1){//如果死活回不到非父祖先->割点 
										  //且正好可以把a,b两点分开	
				if(u!=a&&u!=b){
					ans=min(ans,u);
				}
			}
		}
		else if(dfn[v]<dfn[u]){
			low[u]=min(low[u],dfn[v]);
		}	
	}
} 
int main(){ 
 	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
	int x,y;
	int z=0;
	while(cin>>x>>y){
		z++;
		if(x==0&&y==0)
			break;
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}
	cin>>a>>b;
	fill(dfn,dfn+n+1,0);
    fill(low,low+n+1,0);
    timer=0;
	tarjan(a,-1);//从a出发
	if(!dfn[b]){//如果a,b之间本来就是断开的，那么肯定放不了嗅探器->无解 
		cout<<"No solution";
	}
	else if(ans==1e9){
		cout<<"No solution";		
	}
	else{
		cout<<ans<<'\n';
	}
	return 0;
} 
