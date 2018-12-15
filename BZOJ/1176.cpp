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

const int MAXN=4E5+10;
const int MAXW=2E6+10;

struct opt{
	int x,tp,l,r,f,id;//tp=0 edit ,tp=1 query
	opt(){}
	opt(int _x,int _tp,int _l,int _r,int _f,int _id){x=_x;tp=_tp;l=_l;r=_r;f=_f;id=_id;}
}op[MAXN],tp[MAXN];

int n,cnt,cntq;
ll Ans[MAXN],t[MAXW];

void C(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

ll Q(int x)
{
	if(!x) return 0;
	ll ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1,tot=0,L=l,R=mid+1;
	CDQ(l,mid);CDQ(mid+1,r);
	while(L<=mid&&R<=r)
		if(op[L].x<op[R].x||(op[L].x==op[R].x&&!op[L].tp))
		{
			if(!op[L].tp)	C(op[L].l,op[L].f);
			tp[++tot]=op[L++];
		}
		else
		{
			if(op[R].tp)	Ans[op[R].id]+=op[R].f*(Q(op[R].r)-Q(op[R].l-1));
			tp[++tot]=op[R++];
		}
	while(L<=mid)
	{
		if(!op[L].tp)  C(op[L].l,op[L].f);
		tp[++tot]=op[L++];
	}
	while(R<=r)
	{
		if(op[R].tp) Ans[op[R].id]+=op[R].f*(Q(op[R].r)-Q(op[R].l-1));
		tp[++tot]=op[R++];
	}
	for(int i=l;i<=mid;i++) if(!op[i].tp) C(op[i].l,-op[i].f);
	for(int i=1;i<=tot;i++) op[l+i-1]=tp[i];
}

int main()
{
	scanf("%*d%d",&n);
	int optt,x1,x2,y1,y2,v;
	while(1)
	{
		scanf("%d",&optt);
		if(optt==3) break;
		if(optt==1)
		{
			scanf("%d%d%d",&x1,&y1,&v);
			op[++cnt]=opt(x1,0,y1,0,v,0);
		}
		else
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);++cntq;
			op[++cnt]=opt(x1-1,1,y1,y2,-1,cntq);
			op[++cnt]=opt(x2,1,y1,y2,1,cntq);
		}
	}
	CDQ(1,cnt);
	for(int i=1;i<=cntq;i++) printf("%lld\n",Ans[i]);
}