#include <bits/stdc++.h>
using namespace std;
int c1,c2;
string s1,s2;
int main(){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	cin>>c1>>s1>>c2>>s2;
	int pa1,pa2;//ÅÅÊý 
	char zuo1,zuo2;//×ùÎ»ºÅ 
	zuo1=s1[2];
	zuo2=s2[2];
	pa1=(s1[0]-'0')*10+s1[1]-'0';
	pa2=(s2[0]-'0')*10+s2[1]-'0';
	if(c1==c2){
		cout<<1;
	}
	else{
		cout<<0;
	}
	if(c1==c2&&pa1==pa2){
		cout<<1;
	}
	else{
		cout<<0;
	}
	if(c1==c2&&pa1==pa2&&((zuo1<='C'&&zuo2<='C')||(zuo1>='D'&&zuo2>='D'))){	
		cout<<1;
	}
	else{
		cout<<0;
	}
	if(c1==c2&&pa1==pa2&&abs(zuo1-zuo2)==1&&(zuo1<='C'&&zuo2<='C')){
		cout<<1;
	}
	else if(c1==c2&&pa1==pa2&&(zuo1>='D'&&zuo2>='D')){
		cout<<1;
	}
	else{
		cout<<0;
	}
	return 0;
}  
