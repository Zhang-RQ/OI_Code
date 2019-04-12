#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MaxBlk=450;
const int blksiz=420;

int n,q,a[MAXN],b[MAXN],c[MAXN],pos[MAXN],id[MAXN],totp;
int val[MAXN],w[MAXN],tag[MaxBlk],ptr[MaxBlk],totb;
int siz[MaxBlk],L[MaxBlk],R[MaxBlk],bl[MAXN];
pair<int,int> arr[MaxBlk][MaxBlk],tmp[MaxBlk];
ll Ans,tAns[MaxBlk],pre[MaxBlk][MaxBlk];

void pushdown(int x)
{
	if(!tag[x])
		return;
	for(int i=L[x];i<=R[x];i++)
		val[i]+=tag[x];
	tag[x]=0;
}

void build(int x)
{
	Ans-=tAns[x];
	tAns[x]=0;
	siz[x]=R[x]-L[x]+1;
	for(int i=L[x];i<=R[x];i++)
		tmp[i-L[x]+1]=make_pair(val[i],w[i]);
	sort(tmp+1,tmp+1+siz[x]);
	arr[x][siz[x]=1]=tmp[1];
	for(int i=2;i<=R[x]-L[x]+1;i++)
		if(tmp[i].first==tmp[i-1].first)
			arr[x][siz[x]].second+=tmp[i].second;
		else
			arr[x][++siz[x]]=tmp[i];
	for(int i=L[x];i<=R[x];i++)
		tAns[x]+=1ll*abs(val[i])*w[i];
	for(int i=1;i<=siz[x];i++)
		pre[x][i]=pre[x][i-1]+arr[x][i].second;
	ptr[x]=0;
	while(ptr[x]<siz[x]&&arr[x][ptr[x]+1].first<=0)
		++ptr[x];
	Ans+=tAns[x];
}

void change(int l,int r,int v)
{
	if(l>r)
		return;
	int Bl=bl[l],Br=bl[r];
	if(Bl==Br)
	{
		pushdown(Bl);
		for(int i=l;i<=r;i++)
			val[i]+=v;
		build(Bl);
		return;
	}
	pushdown(Bl);pushdown(Br);
	for(int i=l;i<=R[Bl];i++)
		val[i]+=v;
	for(int i=L[Br];i<=r;i++)
		val[i]+=v;
	build(Bl);build(Br);
	for(int i=Bl+1;i<=Br-1;i++)
	{
		tag[i]+=v;
		Ans-=tAns[i];
		if(v>0)
		{
			tAns[i]+=pre[i][siz[i]]-2*pre[i][ptr[i]-(arr[i][ptr[i]].first+tag[i]-1==0&&ptr[i]!=0)];
			if(ptr[i]&&arr[i][ptr[i]].first+tag[i]>0)
				--ptr[i];
		}
		else
		{
			tAns[i]-=pre[i][siz[i]]-2*pre[i][ptr[i]];
			if(ptr[i]<siz[i]&&arr[i][ptr[i]+1].first+tag[i]<=0)
				++ptr[i];
		}
		Ans+=tAns[i];
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),pos[++totp]=a[i];
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]),pos[++totp]=b[i];
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&id[i],&c[i]),pos[++totp]=c[i];
	sort(pos+1,pos+1+totp);
	totp=unique(pos+1,pos+1+totp)-pos-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(pos+1,pos+1+totp,a[i])-pos,
		b[i]=lower_bound(pos+1,pos+1+totp,b[i])-pos;
	for(int i=1;i<=q;i++)
		c[i]=lower_bound(pos+1,pos+1+totp,c[i])-pos;
	for(int i=1;i<=n;i++)
		val[a[i]]++,val[b[i]]--;
	for(int i=1;i<=totp;i++)
	{
		val[i]+=val[i-1];
		if(i<totp) w[i]=pos[i+1]-pos[i];
	}
	for(int i=1;i<=totp;i++)
	{
		bl[i]=(i-1)/blksiz+1;
		if(!L[bl[i]]) L[bl[i]]=i;
		R[bl[i]]=i;
	}
	totb=bl[totp];
	for(int i=1;i<=totb;i++)
		build(i);
	printf("%lld\n",Ans);
	for(int i=1;i<=q;i++)
	{
		if(a[id[i]]<c[i])
			change(a[id[i]],c[i]-1,-1);
		else
			change(c[i],a[id[i]]-1,1);
		a[id[i]]=c[i];
		printf("%lld\n",Ans);
	}
}
