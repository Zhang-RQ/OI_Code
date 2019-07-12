#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=105;
const int MAXM=10010;

int n,m,r,ine[MAXN],vis[MAXN],Ans,cnt;
int U[MAXM],V[MAXM],W[MAXM],id[MAXN],inval[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&U[i],&V[i],&W[i]);
	W[0]=1<<30;
	while(1)
	{
		cnt=0;
		for(int i=1;i<=n;i++)
			ine[i]=vis[i]=id[i]=0,inval[i]=1<<30;
		for(int i=1;i<=m;i++)
			if(U[i]!=V[i]&&inval[V[i]]>W[i])
				ine[V[i]]=i,inval[V[i]]=W[i];
		for(int i=1;i<=n;i++)
			if(i!=r&&!ine[i])
				return puts("-1"),0;
		for(int i=1;i<=n;i++)
		{
			if(i==r)
				continue;
			Ans+=W[ine[i]];
			int x=i;
			while(vis[x]!=i&&!id[x]&&x!=r)
				vis[x]=i,x=U[ine[x]];
			if(!id[x]&&x!=r)
			{
				id[x]=++cnt;
				for(int p=U[ine[x]];p!=x;p=U[ine[p]])
					id[p]=cnt;
			}
		}
		if(!cnt)
			break;
		for(int i=1;i<=n;i++)
			if(!id[i])
				id[i]=++cnt;
		for(int i=1;i<=m;i++)
		{
			int pv=V[i];
			U[i]=id[U[i]];V[i]=id[V[i]];
			if(U[i]!=V[i])
				W[i]-=inval[pv];
		}
		r=id[r];n=cnt;
	}
	printf("%d\n",Ans);
}
