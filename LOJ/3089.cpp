#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1510;
const double EPS=1E-8;

char s[MAXN],str[MAXN],Ans[MAXN];
int n,m,son[MAXN][10],fail[MAXN],cnt,pre[MAXN][MAXN],prec[MAXN][MAXN];
vector<int> ed[MAXN];
double f[MAXN][MAXN],val[MAXN],tval[MAXN],nval[MAXN];

void insert(int id)
{
	int x=0;
	for(int i=1;s[i];i++)
	{
		if(!son[x][s[i]-'0'])
			son[x][s[i]-'0']=++cnt;
		x=son[x][s[i]-'0'];
	}
	ed[x].push_back(id);
}

void build()
{
	queue<int> q;
	for(int i=0;i<10;i++)
		if(son[0][i])
			q.push(son[0][i]);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int id:ed[fail[x]])
			ed[x].push_back(id);
		for(int i=0;i<10;i++)
			if(son[x][i])
				fail[son[x][i]]=son[fail[x]][i],q.push(son[x][i]);
			else
				son[x][i]=son[fail[x]][i];
	}
}

void Update(int i,int j,double val,int p,int pc)
{
	if(val>f[i][j])
	{
		f[i][j]=val;
		pre[i][j]=p;
		prec[i][j]=pc;
	}
}

bool chk(double Mid)
{
	memset(f,0xc2,sizeof f);
	for(int i=1;i<=m;i++)
		val[i]=tval[i]-Mid;
	for(int i=0;i<=cnt;i++)
	{
		nval[i]=0;
		for(int id:ed[i])
			nval[i]+=val[id];
	}
	f[0][0]=0;
	for(int i=0;i<n;i++)
	{
		if(str[i+1]=='.')
		{
			for(int j=0;j<=cnt;j++)
				if(f[i][j]>=-1E5)
				{
					for(int k=0;k<10;k++)
					{
						int nxt=son[j][k];
						if(ed[nxt].size())
						{
							double nf=f[i][j]+nval[nxt];
							Update(i+1,nxt,nf,j,k);
						}
						else 
							Update(i+1,nxt,f[i][j],j,k);
					}
				}
		}
		else
		{
			
			for(int j=0;j<=cnt;j++)
				if(f[i][j]>=-1E5)
				{
					int nxt=son[j][str[i+1]-'0'];
					if(ed[nxt].size())
					{
						double nf=f[i][j]+nval[nxt];
						Update(i+1,nxt,nf,j,str[i+1]-'0');
					}
					else 
						Update(i+1,nxt,f[i][j],j,str[i+1]-'0');
				}
		}
	}
	double Ans=-1E8;
	for(int i=0;i<=cnt;i++)
		Ans=max(Ans,f[n][i]);
	return Ans>EPS;
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	for(int i=1,v;i<=m;i++)
	{
		scanf("%s%d",s+1,&v);
		tval[i]=std::log(v);
		insert(i);
	}
	build();
	double L=0,R=100;
	for(int T=45;T--;)
	{
		double Mid=(L+R)/2;
		if(chk(Mid)) L=Mid;
		else R=Mid;
	}
	int p=0;
	for(int i=0;i<=cnt;i++)
		if(f[n][i]>f[n][p])
			p=i;
	for(int i=n;i;i--)
	{
		Ans[i]=prec[i][p]+'0';
		p=pre[i][p];
	}
	puts(Ans+1);
}
