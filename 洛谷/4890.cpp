#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4010;

struct Pnt{
	int id,tp,v;

	bool operator < (const Pnt &rhs) const {return v<rhs.v;}
}p[MAXN];

int n,k,tot,val[MAXN],vale[MAXN],nxt[MAXN];
int f[MAXN][MAXN][2],Ans,ord[MAXN],pre[MAXN],cnt;

void dfs(int x)
{
	ord[++cnt]=x;
	if(nxt[x]) dfs(nxt[x]);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,l,r;i<=n;i++)
	{
		scanf("%d%d",&l,&r);
		p[++tot]=(Pnt){i,0,l};
		p[++tot]=(Pnt){i,1,r};
	}
	sort(p+1,p+1+tot);
	for(int i=2;i<=tot;i++)
	{
		if(p[i-1].tp==p[i].tp)
		{
			if(p[i].tp==0) 	val[p[i-1].id]+=p[i].v-p[i-1].v;
			else val[p[i].id]+=p[i].v-p[i-1].v;
		}
		else
		{
			if(p[i].tp==1)
			{
				if(p[i-1].id==p[i].id) val[p[i].id]+=p[i].v-p[i-1].v;
				else nxt[p[i-1].id]=p[i].id,pre[p[i].id]=p[i-1].id,vale[p[i].id]=p[i].v-p[i-1].v;
			}
			else Ans+=p[i].v-p[i-1].v;
		}
	}
	for(int i=1;i<=tot;i++)
		if(!p[i].tp&&!pre[p[i].id]) dfs(p[i].id);
	for(int i=1;i<=n;i++)
	{
		int x=ord[i],y=ord[i-1];
		for(int j=1;j<=k;j++)
		{
			f[x][j][0]=max(f[y][j][0],f[y][j][1]);
			f[x][j][1]=max(f[y][j-1][0],f[y][j-1][1]+vale[x])+val[x];
		}
	}
	int tAns=0;
	for(int i=1;i<=k;i++)
		tAns=max(tAns,max(f[ord[n]][i][0],f[ord[n]][i][1]));
	printf("%d\n",p[tot].v-tAns-Ans-p[1].v);
}
