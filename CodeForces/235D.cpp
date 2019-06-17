#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3010;

int n,inR[MAXN],dep[MAXN],jmp[13][MAXN];
int top,stk[MAXN],ins[MAXN],bl[MAXN],rt,ringo[MAXN];
vector<int> T[MAXN],Ring;

void dfs(int x,int fa)
{
	ins[stk[++top]=x]=1;
	for(int v:T[x])
		if(v!=fa)
		{
			if(ins[v])
				throw v;
			dfs(v,x);
		}
	ins[stk[top--]]=0;
}

void dfst(int x,int fa)
{
	bl[x]=rt;
	dep[x]=dep[fa]+1;
	jmp[0][x]=fa;
	for(int v:T[x])
		if(v!=fa&&!inR[v])
			dfst(v,x);
}

int dis(int x,int y) //point distance
{
	assert(bl[x]==bl[y]);
	int _x=x,_y=y;
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=12;~j;j--)
		if(dep[jmp[j][x]]>=dep[y])
			x=jmp[j][x];
	if(x==y)
		return dep[_x]+dep[_y]-2*dep[x]+1;
	for(int j=12;~j;j--)
		if(jmp[j][x]!=jmp[j][y])
			x=jmp[j][x],y=jmp[j][y];
	return dep[_x]+dep[_y]-2*(dep[x]-1)+1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<=n;i++)
		scanf("%d%d",&u,&v),
		++u,++v,
		T[u].push_back(v),
		T[v].push_back(u);
	try {dfs(1,0);}
	catch(int t)
	{
		for(int i=1,f=0;i<=top;i++)
		{
			f|=stk[i]==t;
			if(f)
				ringo[stk[i]]=Ring.size(),Ring.push_back(stk[i]),inR[stk[i]]=1;
		}
	}
	for(int p:Ring)
		rt=p,dfst(p,0);
	for(int j=1;j<=12;j++)
		for(int i=1;i<=n;i++)
			jmp[j][i]=jmp[j-1][jmp[j-1][i]];
	double Ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(bl[i]==bl[j])
				Ans+=1.0/dis(i,j);
			else
			{
				int L=ringo[bl[i]],R=ringo[bl[j]];
				if(L>R)
					swap(L,R);
				int x=dep[i]+dep[j],y=R-L-1,z=Ring.size()-(R-L+1);
				Ans+=1.0/(x+y)+1.0/(x+z)-1.0/(x+y+z);
			}
		}
	printf("%.15lf\n",Ans);
}
