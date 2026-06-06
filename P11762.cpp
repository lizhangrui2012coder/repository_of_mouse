#include <bits/stdc++.h>
using namespace std;
const int N=1010;
const int M=N*N;
int n,m,k,s;
bool vis[N];//是否访问过 
bool inTree[M];//记录这条原图上的边是不是树边 
int parent[N];//点的父亲 
int parent_edge[N];//连接到父亲的边
int u[M],v[M];//一条边的两个端点 
int cur[N];//遍历欧拉时到第几条边了
vector< pair<int,int> > ans;//保存最后的答案(first->id,second->0/1)  
struct node{//给原图用的 
	int id;
	int to;
}; 
struct enode{//给欧拉图邻接表节点用的 
	int enode_to;
	int enode_id;
}; 
struct eedge{//欧拉图边实例 
	int eedge_x,eedge_y;//边实例连接的两个点 
	int eedge_id;//对应原图几号边 
	int eedge_tag;//这次经过输出0还是1(0是删掉，1是不删) 
	bool eedge_used;//欧拉时是否用过 
};
vector<enode> eg[N];//欧拉图
vector<eedge> ed;//欧拉边实例 
int extra[M];//记录哪条树边需要额外补一次
vector<node> g[N];//地图
int deg[N];//每个点的度数 
vector <node> tree[N];//记录生成出来的树 
void dfs(int start){//构造从起点出发的树 
	vis[start]=true;
	for(auto e:g[start]){
		int id=e.id;
		int to=e.to;
		if(vis[to])
			continue;
		tree[start].push_back({id,to});//这两步是为了构建一个树 
		tree[to].push_back({id,start});
		inTree[id]=true;
		parent[to]=start;
		parent_edge[to]=id;
		dfs(to);
	}
} 
int dfs_parity(int x,int fa){//在上一步已经构造好了的树上做奇偶修正 
	int res=deg[x]%2;
	for(auto e:tree[x]){
		int to=e.to;
		int id=e.id;
		if(to==fa)
			continue;
		int t=dfs_parity(to,x);
		if(t==1){//如果返回的是1->说明这颗子树奇点数为奇数
				 //所以子树内部消化不了->与父边连接补一次 
			extra[id]=1;
		}
		res^=t;
	}
	return res;
}
void add_edge(int x,int y,int id,int tag){//加欧拉边 
	int e_id=ed.size();
	ed.push_back({x,y,id,tag,false});
	eg[x].push_back({y,e_id});
	eg[y].push_back({x,e_id});
}
void euler(int x){//递归函数 
	while(cur[x]<(int)eg[x].size()){//只要扫描的位置比欧拉图的大小小->继续扫描 
		int to=eg[x][cur[x]].enode_to;//这条边通向哪里 
		int e_id=eg[x][cur[x]].enode_id;//这条边的实例编号是什么 
		cur[x]++;//下一次再到x时,从下一条邻边开始 
		if(ed[e_id].eedge_used)
			continue;
		ed[e_id].eedge_used=true;//标记已经走过 
		euler(to);
		ans.push_back({ed[e_id].eedge_id,ed[e_id].eedge_tag});//回溯 
	}
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k>>s;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		deg[x]++;//预处理每个点的度数 
		deg[y]++;
		u[i]=x;
		v[i]=y;
		g[x].push_back({i,y});
		g[y].push_back({i,x}); 
	}
	dfs(s);
	dfs_parity(s,0);
	for(int i=1;i<=m;i++){//原图加边 
		if(inTree[i]){
			add_edge(u[i],v[i],i,1);
		}
		else{
			add_edge(u[i],v[i],i,0);
		}
	} 
	for(int i=1;i<=m;i++){//要额外加边的再加一次 
		if(extra[i]){
			add_edge(u[i],v[i],i,1);
		}
	}
	euler(s);
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(auto p:ans){
		cout<<p.first<<' '<<p.second<<'\n';
	}
	return 0;
} 
