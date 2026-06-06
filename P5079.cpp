#include <bits/stdc++.h>
using namespace std;
int r,c;//r是行,c是列 
char mp[15][100010];
int vis[15][100010];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
string num[10][5] = {
    {"###","#.#","#.#","#.#","###"}, // 0
    {"#","#","#","#","#"},           // 1
    {"###","..#","###","#..","###"}, // 2
    {"###","..#","###","..#","###"}, // 3
    {"#.#","#.#","###","..#","..#"}, // 4
    {"###","#..","###","..#","###"}, // 5
    {"###","#..","###","#.#","###"}, // 6
    {"###","..#","..#","..#","..#"}, // 7
    {"###","#.#","###","#.#","###"}, // 8
    {"###","#.#","###","..#","###"}  // 9
};
struct node{
	int max_x,max_y,min_x,min_y;
}part_id[100010];//用来记录每一个连通块的数值 
int maxx,maxy,minx,miny;
void dfs(int x,int y){//dfs出四个位置 
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx>0&&nx<=r&&ny>0&&ny<=c&&mp[nx][ny]=='#'&&!vis[nx][ny]){
			vis[nx][ny]=1;
			maxx=max(maxx,nx);
			maxy=max(maxy,ny);
			minx=min(minx,nx);
			miny=min(miny,ny);
			dfs(nx,ny);
		}
	}
}
bool cmp(node x,node y){//自定义的排序函数 
	return x.min_y<y.min_y;
} 
int get_number(node x){
	int maxx=x.max_x;
	int minx=x.min_x;
	int maxy=x.max_y;
	int miny=x.min_y;
	int width=maxy-miny+1;//计算宽度 
	if(width==1){
		return 1;
	}
	for(int k=0;k<=9;k++){
		if(k==1)
			continue;
			bool t=1;
		for(int i=0;i<5;i++){
			for(int j=0;j<3;j++){
				if(mp[minx+i][miny+j]!=num[k][i][j]){
					t=0;
				}
			}
		}
		if(t==1)
			return k;
	}
} 
int main(){
	cin>>r>>c;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>mp[i][j];
		}
	}
	int cnt=0;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(!vis[i][j]&&mp[i][j]=='#'){
				maxx=minx=i;
				maxy=miny=j;
				++cnt;
				vis[i][j]=1;
				dfs(i,j);
				part_id[cnt]={maxx,maxy,minx,miny};
			}
		}
	}
	sort(part_id+1,part_id+cnt+1,cmp);//先排序，再输出 
	for(int i=1;i<=cnt;i++){
		cout<<get_number(part_id[i]);
	}
	return 0;
}
