#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=50;
const int MAXS=1<<23;
const int P=1E9+7;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ban[MAXN],bans[MAXN],cons[MAXN];
int n,tot,f[MAXS],g[MAXS],cnt[MAXS],fa[MAXN];
char mp[MAXN][MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int calc(int *a,int siz)
{
	int Ans=0;
	for(int s=0;s<=siz;s++)
		if((cnt[s]-cnt[siz])&1)
			Dec(Ans,a[s]);
		else
			Inc(Ans,a[s]);
	return Ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(mp[i][j]=='A')
				fa[find(i)]=find(j);
			else if(mp[i][j]=='X')
				ban[i]|=1ll<<j;
	int Ans=0,fafa1=0,fafa2=0;
	for(int i=1;i<=n;i++)
		if(fa[i]==i)
		{
			vector<int> tmp;
			for(int j=1;j<=n;j++)
				if(find(j)==i)
					tmp.push_back(j);
			if(tmp.size()>1)
			{
				++tot;
				for(int p:tmp)
					bans[tot]|=ban[p],
					cons[tot]|=1ll<<p;
				if(bans[tot]&cons[tot])
					return puts("-1"),0;
			}
			Ans+=tmp.size();
			fafa1+=tmp.size()==1;
			fafa2+=tmp.size()>1;
		}
	if(fafa1&&!fafa2) --Ans;
	for(int s=0;s<1<<tot;s++)
	{
		if(s) cnt[s]=cnt[s-(s&(-s))]+1;
		ll B=0,C=0;
		for(int i=0;i<tot;i++)
			if((s>>i)&1)
				B|=bans[i+1],
				C|=cons[i+1];
		bool ok=1;
		for(int i=0;i<tot;i++)
			if((s>>i)&1)
				ok&=!(B&(C^cons[i+1]));
		if(ok) ++f[s];
	}
	for(int i=0;i<tot;i++)
		for(int s=0;s<1<<tot;s++)
			if((s>>i)&1)
				f[s]+=f[s^(1<<i)];
	for(int s=0;s<1<<tot;s++)
		g[s]=f[s];
	for(int i=0;i<=n;i++)
	{
		if(calc(g,(1<<tot)-1)){Ans+=i;break;}
		for(int s=0;s<1<<tot;s++)
			g[s]=1ll*g[s]*f[s]%P;
	}
	printf("%d\n",Ans);
}
