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

const int MAXN=1E4+10;
const int MAXD=1E6+10;

bool ban[MAXN];

namespace Linked_List{
	int fnt[MAXN],nxt[MAXN],head,tail;
	void erase(int x)
	{
		ban[x]=1;
		if(x==head) return head=nxt[x],void();
		if(x==tail) return tail=fnt[x],void();
		fnt[nxt[x]]=fnt[x];nxt[fnt[x]]=nxt[x];
	}
	void insert(int x,int L,int R) //insert x into [L,R] L==-1 head R==-1 tail
	{
		if(!head&&!tail) head=tail=x;
		else if(L==-1)
		{
			nxt[x]=head;
			fnt[head]=x;
			head=x;
		}
		else if(R==-1)
		{
			nxt[tail]=x;
			fnt[x]=tail;
			tail=x;
		}
		else
		{
			nxt[L]=fnt[R]=x;
			fnt[x]=L;nxt[x]=R;
		}
	}
}

using namespace Linked_List;

double Ans;
int n,up,dwn=1<<30,sum[MAXD],len,stk[MAXN],top;
struct tri{
	int x,y,d;
	int l,r;
	bool operator < (const tri &rhs) const {return y<rhs.y;}
}t[MAXN];

bool judge(int i,int j) //return j in i
{
	return t[i].l<=t[j].l&&t[j].r<=t[i].r;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&t[i].x,&t[i].y,&t[i].d);
		t[i].l=t[i].x;t[i].r=t[i].x+t[i].d;
		up=max(up,t[i].y+t[i].d);dwn=min(dwn,t[i].y);
	}
	sort(t+1,t+1+n);
	int j=1;
	while(j<=n&&t[j].y==dwn)
	{
		insert(j,-1,0);
		for(int i=t[j].l;i<t[j].r;i++)
			if(!(sum[i]++))
				++len;
		++j;
	}
	for(int i=dwn+1;i<=up;i++)
	{
		int lst=len;top=0;
		for(int x=head;x;x=nxt[x])
		{
			if(ban[x]) continue;
			--t[x].r;
			if(t[x].r<t[x].l) erase(x);
			else
			{
				if(!(--sum[t[x].r]))
				--len;
				stk[++top]=x;
			}
			if(x==tail) break;
		}
		Ans+=(lst+len)/2.0;
		while(j<=n&&t[j].y==i)
		{
			bool f=0;
			for(int l=1;l<=top;l++)
			{
				int x=stk[l];
				if(ban[x]) continue;
				if(judge(x,j)) {f=1;break;}
				if(judge(j,x))
				{
					for(int lala=t[x].l;lala<t[x].r;lala++)
						if(!(--sum[lala]))
							--len;
					erase(x);
				}
			}
			if(!f)
			{
				insert(j,-1,0);
				for(int lala=t[j].l;lala<t[j].r;lala++)
					if(!(sum[lala]++))
						++len;
			}
			++j;
		}
	}
	printf("%.1lf\n",Ans);
}