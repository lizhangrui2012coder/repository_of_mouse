#include <bits/stdc++.h>
using namespace std;
int n,m;
int S;
int T;
const int maxn=210;
bool block[maxn][maxn];//记录是否障碍
int id[maxn][maxn];
int dx[8]={-2,-1,1,2,2,1,-1,-2};//像dfs
int dy[8]={-1,-2,-2,-1,1,2,2,1};
struct Edge{//每条边的属性
    int to;//这条边终点编号
    int rev;//这条边对应的反向边，在对方邻接表中的位置
    int cap;//变得剩余容量
};
vector <Edge> g[maxn*maxn];// 邻接表，g[u] 存储从 u 出发的所有边
bool vis[maxn*maxn];//是否访问过
int preNode[maxn*maxn];// 前驱点
int preEdge[maxn*maxn];// 从前驱点的第几条边走到当前点
void addEdge(int u,int v,int cap){// 添加一条容量为 cap 的边 u→v，并自动建立反向边
    int uIndex=g[u].size();// 正向边加入后在 g[u] 中的位置
    int vIndex=g[v].size();// 反向边加入后在 g[v] 中的位置
    // rev 存储的是"对方邻接表中的下标"，因此要记录对方即将插入的位置
    Edge forward={v,vIndex,cap};// 正向边的反向边，将放在 g[v][vIndex]
    Edge backward={u,uIndex,0};// 反向边的反向边，就是 g[u][uIndex]
    g[u].push_back(forward);
    g[v].push_back(backward);
}
//找路径
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
                if(e.to==t)//找到终点了
                    return true;
                q.push(e.to);
            }
        }
    }
    return false;
} 
int EK(int s,int t){
    int ans=0;
    while(bfs(s,t)){
        int flow=1e9;
        int v=t;
        while(v!=s){
            flow=min(flow,g[preNode[v]][preEdge[v]].cap);
            v=preNode[v];
        }
        v=t;
        while(v!=s){
            Edge &e=g[preNode[v]][preEdge[v]];
            e.cap-=flow;//正向边-流量
            g[v][e.rev].cap+=flow;//反向边+流量
            v=preNode[v];//更新v
        }
        ans+=flow;//最后最大流
    }
    return ans;
}
int main(){
    cin>>n>>m;
    S=0;
    T=n*n+1;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        block[x][y]=true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            id[i][j]=(i-1)*n+j;
        }
    }
     for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(block[i][j])
                continue;
            if((i+j)%2==0){
                addEdge(S,id[i][j],1);
                for(int k=0;k<8;k++){
                    int nx=i+dx[k];
                    int ny=j+dy[k];
                    if(nx>0&&nx<=n&&ny>0&&ny<=n&&!block[nx][ny]){
                        addEdge(id[i][j],id[nx][ny],1);
                    }
                }
            }
            else{
                addEdge(id[i][j],T,1);
            }
        }
    }
    cout<<n*n-EK(S,T)-m;
    return 0;
} 