#include <bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=210;
int match[maxn*maxn];//匹配
int vis[maxn*maxn];//dfs访问的记录
int id[maxn][maxn];//二维坐标映射编号
vector <int> g[maxn*maxn];//左部点 u 能连到哪些右部点
bool block[maxn][maxn];//记录是否障碍
int dx[8]={-2,-1,1,2,2,1,-1,-2};//像dfs
int dy[8]={-1,-2,-2,-1,1,2,2,1};
int timer;//时间戳
bool find(int u){
	for(int v:g[u]){
		//本轮已经访问过v,避免重复搜索
		if(vis[v]==timer)
			continue;
		//标记本轮已经访问
		vis[v]=timer;
		//情况1:v没有匹配对象
		//情况2:v原来的主人可以重新找到匹配
		if(match[v]==0||find(match[v])){
			//当前u占据v
			match[v]=u;
			return true;
		}
	}
	//所有能够连接的点都尝试失败
	return false;
}
int main(){
    cin>>n>>m;
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
            if(block[i][j])//不用有障碍的
                continue;
            if((i+j)%2!=0)//只从左部点出发
                continue;
            for(int k=0;k<8;k++){
                int nx=i+dx[k];
                int ny=j+dy[k];    
                if(nx>0 && nx<=n && ny>0 && ny<=n && !block[nx][ny]){
                    //加入进二分图
                    g[id[i][j]].push_back(id[nx][ny]);
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(block[i][j])//障碍格不要
                continue;
            if((i+j)%2!=0)//只要左部点
                continue;
            timer++;
            if(find(id[i][j]))
                ans++;
        }
    }
    cout<<n*n-m-ans;
    return 0;
} 