#include <bits/stdc++.h>
using namespace std;
struct Edge{//每条边的属性
    int to;//这条边终点编号
    int rev;//这条边对应的反向边，在对方邻接表中的位置
    long long cap;//变得剩余容量
};
const int maxn=1000010;
vector <Edge> g[maxn];// 邻接表，g[u] 存储从 u 出发的所有边
bool vis[maxn];//是否访问过
int preNode[maxn];// 前驱点
int preEdge[maxn];// 从前驱点的第几条边走到当前点
void addEdge(int u,int v,long long cap){// 添加一条容量为 cap 的边 u→v，并自动建立反向边
    int uIndex=g[u].size();// 正向边加入后在 g[u] 中的位置
    int vIndex=g[v].size();// 反向边加入后在 g[v] 中的位置
    // rev 存储的是"对方邻接表中的下标"，因此要记录对方即将插入的位置
    Edge forward={v,vIndex,cap};// 正向边的反向边，将放在 g[v][vIndex]
    Edge backward={u,uIndex,0};// 反向边的反向边，就是 g[u][uIndex]
    g[u].push_back(forward);
    g[v].push_back(backward);
}
bool bfs(int s,int t){//s是起点，t是终点
    queue <int> q;//BFS队列
    memset(vis,0,sizeof vis);
    vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<(int)g[u].size();i++){
            Edge &e=g[u][i];
            if(!vis[e.to]&&e.cap>0){
                vis[e.to]=1;
                preNode[e.to]=u;
                preEdge[e.to]=i;
                if(e.to==t)
                    return true;
                q.push(e.to);
            }
        }
    }
    return false;
} 
long long EK(int s,int t){
    long long ans=0;
    while(bfs(s,t)){
        long long flow=4e18;
        long long v=t;
        while(v!=s){
            flow=min(flow,g[preNode[v]][preEdge[v]].cap);
            v=preNode[v];
        }
        v=t;
        while(v!=s){
            Edge &e=g[preNode[v]][preEdge[v]];
            e.cap-=flow;
            g[v][e.rev].cap+=flow;
            v=preNode[v];
        }
        ans+=flow;
    }
    return ans;
}
int main(){
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        int u,v;
        long long cap;
        cin>>u>>v>>cap;
        addEdge(u,v,cap);
    }
    cout<<EK(s,t);
    return 0;
}