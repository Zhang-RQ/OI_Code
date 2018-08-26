#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E5+10;

struct __node{
	int v,pos;
	__node(){}
	__node(int _,int __) {v=_;pos=__;}
}f[MAXN][31];

int n,a[MAXN],m;

int read(){
	int ans=0;
	char ch=getchar();
	while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	return ans;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=n;i>=1;i--)
	{
		memcpy(f[i],f[i+1],sizeof f[i]);
		__node now(a[i],i);
		for(int j=30;~j;j--)
		{
			if(!((now.v>>j)&1)) continue;
			if(!f[i][j].v) {f[i][j]=now;break;}
			else
			{
				if(f[i][j].pos>now.pos) swap(f[i][j],now);
				now.v^=f[i][j].v;
			}
		}
	}
	m=read();
	for(int i=1,l,r,k,Res;i<=m;i++)
	{
		l=read();r=read();k=read();
		Res=1;
		for(int j=30;~j;j--)
		{
			if(!((k>>j)&1)) continue;
			if(f[l][j].v==0||f[l][j].pos>r) {Res=0;break;}
			k^=f[l][j].v;
		}
		puts(Res?"YES":"NO");
	}
}