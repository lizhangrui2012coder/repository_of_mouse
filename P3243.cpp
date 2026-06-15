#include <bits/stdc++.h>
using namespace std;
//反着建图
//找当前可以放到“最后”的菜
//每次选最大编号
//最后反转
int t;//总数据组数
int n,m;
const int maxn=100010;
int in_deg[maxn];//入度
vector <int> g[maxn];//地图
priority_queue <int> q;
vector <int> ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){//不只一组，所以清空
            g[i].clear();
            in_deg[i]=0;//入度初始化
        }
        ans.clear();
        for(int i=1;i<=m;i++){
            int x,y;
            cin>>x>>y;
            g[y].push_back(x);//注意要反着来
            in_deg[x]++;
        }
        for(int i=1;i<=n;i++){
            if(in_deg[i]==0)
                q.push(i);
        }
        while(!q.empty()){//常规的拓扑排序
            int u=q.top();
            q.pop();
            ans.push_back(u);
            for(auto v:g[u]){
                in_deg[v]--;
                if(in_deg[v]==0)
                    q.push(v);
            }
        }
        if((int)ans.size()!=n){//输出
            cout<<"Impossible!\n";
        }
        else{
            reverse(ans.begin(),ans.end());
            for(int i=0;i<n;i++){
            cout<<ans[i]<<" ";
        }
        cout<<"\n";
        }
    }
    return 0;
}