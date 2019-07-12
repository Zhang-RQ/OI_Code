#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MAXD=MAXN*31;

int n,m,a[MAXN],global_tag,rem_tag;
int pre[31][MAXN],lim,rt=1,tot=1,res[31];
int tag[MAXD],son[MAXD][2],cnt[MAXD][31],siz[MAXD];

void apply_tag(int x,int v,int bit)
{
	tag[x]^=v;
	if((v>>bit)&1)
		swap(son[x][0],son[x][1]);
}

void pushdown(int x,int bit)
{
	if(tag[x])
	{
		apply_tag(son[x][0],tag[x],bit-1);
		apply_tag(son[x][1],tag[x],bit-1);
		tag[x]=0;
	}
}

void insert(int v,int nv)
{
	int x=rt;
	for(int b=30;~b;b--)
	{
		pushdown(x,b);
		siz[x]++;
		for(int j=30;~j;j--)
			cnt[x][j]+=(nv>>j)&1;
		if(!son[x][(v>>b)&1])
			son[x][(v>>b&1)]=++tot;
		x=son[x][(v>>b&1)];
	}
	siz[x]++;
	for(int j=30;~j;j--)
		cnt[x][j]+=(nv>>j)&1;
}

ll query(int k)//k big
{
	memset(res,0,sizeof res);
	int x=rt,prek=k;
	for(int b=30;~b;b--)
	{
		pushdown(x,b);
		if(siz[son[x][1]]>=k)
			x=son[x][1];
		else
		{
			for(int j=30;~j;j--)
				res[j]+=cnt[son[x][1]][j];
			k-=siz[son[x][1]];
			x=son[x][0];
		}
	}
	for(int j=30;~j;j--)
		res[j]+=cnt[x][j]/siz[x]*k;
	ll ret=0;
	for(int j=30;~j;j--)
		if((global_tag>>j)&1)
			ret+=1ll*(1<<j)*(prek-res[j]);
		else
			ret+=1ll*(1<<j)*res[j];
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=30;j++)
			pre[j][i]=pre[j][i-1]+((a[i]>>j)&1);
	scanf("%d",&m);
	for(int i=1,opt,x,y;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&x);x^=global_tag;
			a[++n]=x;
			for(int j=0;j<=30;j++)
				pre[j][n]=pre[j][n-1]+((a[n]>>j)&1);
		}
		else if(opt==2)
		{
			scanf("%d%d",&x,&y);
			ll ans=0;
			if(x<=lim)
				ans=query(lim-x+1);
			if(y<lim)
				ans-=query(lim-y);
			x=max(x,lim+1);
			if(x<=y)
			{
				int len=y-x+1;
				for(int j=0;j<=30;j++)
					if((global_tag>>j)&1)
						ans+=1ll*(len-(pre[j][y]-pre[j][x-1]))*(1<<j);
					else
						ans+=1ll*(pre[j][y]-pre[j][x-1])*(1<<j);
			}
			printf("%lld\n",ans);
		}
		else if(opt==3)
		{
			scanf("%d",&x);
			global_tag^=x;
			rem_tag^=x;
		}
		else
		{
			apply_tag(rt,rem_tag,30);rem_tag=0;
			while(lim+1<=n)
				++lim,insert(a[lim]^global_tag,a[lim]);
		}
	}
}
