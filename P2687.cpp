#include <bits/stdc++.h>
using namespace std;
//本题本质：求最长下降子序列长度，以及最长下降价格序列数量
//代码用线段树优化 DP 查询过程
//线段树的叶子节点对应一个离散化后的价格编号
//线段树的区间节点维护一段价格区间内的最优解
int n;
vector <long long> a;//表示第i天的股价 
vector<long long> nums; //用来做离散化 
struct node{//表示线段树中一个区间维护的信息 
	int len;//这个价格区间内,能形成最长的下降子序列 
	long double cnt;//达到len这个长度的不同价格序列数量 
}tree[4000005]; 
//接下来的代码实现的主要是合并两个node
//如果一边的len更大->说明这种方案更优秀->选他 
//如果相同->就把方案数相加 
inline node m_d(const node& a,const node& b){
	if(a.len>b.len)
		return a;
	if(a.len<b.len)
		return b;
	if(a.len==0&&b.len==0){
		return {0,0};
	}
	return {a.len,(a.cnt+b.cnt)};
}
//根据两个儿子的信息更新当前节点 
void push_up(int x){
	tree[x]=m_d(tree[x*2],tree[x*2+1]);
}
//查询线段树区间[l,r]的最优解 
node query(int x,int start,int end,int l,int r){
	if(l>r)
		return {0,0};
		//当前区间完全被查询区包含 
	if(l<=start&&end<=r){
		return tree[x];
	}
	int mid=(start+end)/2;
	node res={0,0};
	//如果p的新位置在左边->去左边
	//如果p的新位置在右边->去右边 
	if(l<=mid){
		res=m_d(res,query(x*2,start,mid,l,r));
	}
	if(r>mid){
		res=m_d(res,query(x*2+1,mid+1,end,l,r));
	}
	return res;
}
//更新某个价格编号p对应的状态 
//对于同一个价格，后出现的状况直接覆盖前面的状态
//这是为了避免相同价格序列被重复计算 
void update(int x,int start,int end,int p,int val_len,long double val_cnt){
	if(start==end){
		tree[x]={val_len,val_cnt};
		return;
	}
	//如果p的新位置在左边->去左边
	//如果p的新位置在右边->去右边 
	int mid=(start+end)/2;
	if(p<=mid){
		update(x*2,start,mid,p,val_len,val_cnt);
	}
	if(p>mid){
		update(x*2+1,mid+1,end,p,val_len,val_cnt);
	}
	push_up(x);
}
//股价加入离散化数组 
void add_val(long long x) {
    nums.push_back(x);
}
//离散化初始化
//排序+去重->离散化标准做法 
void init_discrete() {  
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
}
//查询股价x离散化后的编号 
int get_id(long long x) {
	//编号从一开始,方便线段树使用 
    return lower_bound(nums.begin(),nums.end(),x)-nums.begin()+1;
}
int main(){ 
	ios::sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	a.resize(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		add_val(a[i]);
	}
	init_discrete();
	int m=nums.size();
	for(int i=1;i<=n;i++){
		int r=get_id(a[i]);//得到当前价格编号 
		node res=query(1,1,m,r+1,m);//查所有比当且价格更大的价格 
		int cur_len=res.len+1;//把当且价格接上去 
		long double cur_cnt=(res.len==0)?1:res.cnt;
		//如果没有比当前价格更大的前面价格，那当前价格自己单独成为一个序列
		//否则，方案数继承前面查到的方案数
		update(1,1,m,r,cur_len,cur_cnt);//更新当前价格的状态 
	}
	node ans=query(1,1,m,1,m);
	cout<<ans.len<<" "<<fixed<<setprecision(0)<<ans.cnt<<"\n";
	return 0;
} 
