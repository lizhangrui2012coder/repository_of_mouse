#include <bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=5005;
const int md=80112002;
vector <int> g[maxn];//记录食物链
int out_deg[maxn];//出度数
int in_deg[maxn];//入度数
int dp[maxn];//dp的数组,维护从所有生产者出发,走到生物i的食物链条数
queue <int> q;//把生产者i放进队列,等会儿处理它
int ans=0;//统计最终的结果数
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        out_deg[x]++;//统计出度
        in_deg[y]++;//统计入度
    }
    for(int i=1;i<=n;i++){
        if(in_deg[i]==0){//如果in_deg为0，说明为生产者，从这里入手
            dp[i]=1;
            q.push(i);
        }
    }
    //处理 u：
    //u 能到 v
    //那么所有到 u 的食物链，都可以接到 v
    //所以 dp[v] += dp[u]
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:g[u]){
            dp[v]=(dp[v]+dp[u])%md;
            //当我们处理完 u 之后，就相当于:
            //u 这个前驱已经处理完了
            //u->v这条边也用完了
            //所以v还没处理的前驱少了一个:
            in_deg[v]--;
            if(in_deg[v]==0)
            //说明v的所有前驱都已经处理完了
            //也就是说,所有能给v贡献食物链数量的点,都已经把dp传给它了
            //dp[v] 已经完整
            //v可以被处理了
                q.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        if(out_deg[i]==0){//要求抵达最高阶的消费者
            ans=(ans+dp[i])%md;
        }
    }
    cout<<ans;
    return 0;
}