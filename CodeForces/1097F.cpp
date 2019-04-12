#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXV=7010;

bitset<MAXV> a[MAXN],b[MAXV],mub[MAXV];
int mu[MAXV],n,q,pr[MAXV],pc,vis[MAXV];

void sieve()
{
	mu[1]=1;
	for(int i=2;i<MAXV;i++)
	{
		if(!vis[i]) pr[++pc]=i,vis[i]=1,mu[i]=-1;
		for(int j=1;j<=pc&&i*pr[j]<MAXV;j++)
		{
			vis[i*pr[j]]=1;
			if(!(i%pr[j])) {mu[i*pr[j]]=0;break;}
			else mu[i*pr[j]]=-mu[i];
		}
	}
}

int main()
{
	scanf("%d%d",&n,&q);sieve();
	for(int i=1;i<=7000;i++)
		for(int j=i;j<=7000;j+=i)
		{
			b[j][i]=1;
			mub[i][j]=mu[j/i]!=0;
		}
	for(int i=1,op,x,y,z;i<=q;i++)
	{
		scanf("%d%d%d",&op,&x,&y);
		if(op==1) a[x]=b[y];
		else if(op==2) scanf("%d",&z),a[x]=a[y]^a[z];
		else if(op==3) scanf("%d",&z),a[x]=a[y]&a[z];
		else if(op==4) putchar('0'+((a[x]&mub[y]).count()&1));
	}
	puts("");
}
