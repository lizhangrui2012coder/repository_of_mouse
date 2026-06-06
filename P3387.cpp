#include <bits/stdc++.h>
using namespace std;
//找到整个图中每一个强连通分量
//将其看作一个点->可以取到所有点权
//最后重新见图->dp出最大点权和 
//强连通分量+拓扑排序+DP 
int n,m;
const int maxn=10010;
int a[maxn];//每个点的点权 

vector<int> g[maxn]; //原图
int dfn[maxn];//表示节点u第几个被访问到
int low[maxn];//最早能追溯到的祖先 
int if_stack[maxn];//dfs过程中,把还没确定属于哪个强连通分量的点放进栈里
				//当发现一个强连通分量时，就从栈顶不断弹出点
int top=0;//指针 
bool in_stack[maxn];//表示u现在是否还在栈里
				   //如果某个点已经被弹出栈 
				   //说明它已经属于某个强连通分量了,就不再拿它更新 low
int timer;//时间戳
int scc_cnt=0;//强连通分量的数量
int belong[maxn];//表示u属于哪个强连通分量
int sum[maxn];//表示第i个强连通分量的点权和 
vector<int> new_g[maxn];//缩点后的图
int indeg[maxn];//缩点后的图入度 
int dp[maxn];//最终答案 
			 //dp[i]=走到强连通分量i时,最多能获得多少点权和
void tarjan(int u){
	dfn[u]=low[u]=++timer;//编号 
	if_stack[++top]=u;//将u放进栈里
	in_stack[u]=true;//标记一下 
	for(auto v:g[u]){
		if(!dfn[v]){
			tarjan(v);//继续往深处走
			low[u]=min(low[u],low[v]);
			//如果u->v							  }
			//并且v或者v的后代能绕回到一个很早的点}
			//那么u也能通过v绕回去  			  }->非常合理的逻辑 
			//∴v能追溯到哪里,u也可能能追溯到哪里 }	 与后面的dfn区分 
			//关键:新儿子v:我可以继承它整棵子树的"最早回溯能力"
		} 
		else if(in_stack[v]){//说明v现在还在栈里 
			low[u]=min(low[u],dfn[v]);
			//这里的v不是u刚刚递归下去的子节点,而是一个已经在栈里的旧点
			//可以得出结论:u至少可以到达v->所以用dfn[v]更新
			//关键:旧点v:我只是直接连到了v,只能确认我能到v本身
		}
	}
	if(dfn[u]==low[u]){//如果u最早只能追溯到自己
	                  //那么u就是一个强连通分量的"根"。
		scc_cnt++;//新加一个强连通分量 
		while (true){//开始弹栈 
			int x=if_stack[top--];//x = 当前栈顶点
								  //top 减 1，相当于把 x 弹出栈
			in_stack[x]=false;//说明x点已经从临时名单中删去
			belong[x]=scc_cnt;//点x属于scc_cnt这个分量里
			sum[scc_cnt]+=a[x];//加上每个点的权值
			if(x==u)
				break;//说明已经没有了,弹到头了 
		}			
	} 
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);//有向图 
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])
			tarjan(i);//调用 
	}
	//把原图里的u->v转化为"强连通分量之间的边" 
	for(int u=1;u<=n;u++){
		for(auto v:g[u]){
			int x=belong[u];
			int y=belong[v];
			if(x!=y){//说明这条边连接了两个强连通分量 
				new_g[x].push_back(y);
				indeg[y]++;
			}
		}
	}
	return 0;
} 
