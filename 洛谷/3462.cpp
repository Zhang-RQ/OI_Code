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

const int MAXN=1E5+10;

int n,m,Ans;
int a[MAXN],cnt[40],p[40],v[MAXN],b[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]),v[i]=b[i];
	sort(v+1,v+1+m);
	int tot=unique(v+1,v+1+m)-v-1;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=tot;j++)
			if(v[j]==b[i])
				{++cnt[j];break;}
	for(int i=1;i<=n;i++)
		for(int j=tot;j;j--)
			p[j]+=a[i]/v[j],a[i]%=v[j];
	for(int i=1;i<=tot;i++)
	{
		bool fafa=1;
		while(cnt[i])
		{
			if(!p[i])
			{
				int pos=i;
				while(pos<=tot&&!p[pos]) pos++;
				if(pos==tot+1) {fafa=0;break;}
				p[pos]--;
				for(int j=i;j<pos;j++)
					p[j]=v[j+1]/v[j]-1;
			}
			else --p[i];
			++Ans;--cnt[i];
		}
		if(!fafa) break;
	}
	printf("%d\n",Ans);
}