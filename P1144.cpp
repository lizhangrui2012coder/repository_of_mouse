#include <bits/stdc++.h>
using namespace std;
int m,n;
vector<vector<int> > mp;
int dist[1000010];
int ans[1000010];
bool vis[1000010];
const int md=100003;
void bfs(){
    queue<int> q;
    q.push(1);
    vis[1]=1;
    ans[1]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:mp[u]){
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
                dist[v]=dist[u]+1;
                ans[v]=ans[u];
            }
            else if(dist[v]==dist[u]+1){
                ans[v]=(ans[u]+ans[v])%md;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    mp.resize(n+1);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        mp[x].push_back(y);
        mp[y].push_back(x);
    }
    bfs();
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}