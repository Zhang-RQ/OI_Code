#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==(x))

struct node_t{
	int son[2],fa,siz,v,tag;
	ll Ans,sum;
}t[MAXN];

int Rt,cnt,R,C,N,pnt[MAXN];
vector<int> v[MAXN];
ll Ans;

void pushup(int x)
{
	t[x].siz=t[ls(x)].siz+t[rs(x)].siz+1;
	t[x].Ans=t[ls(x)].Ans+t[rs(x)].Ans+1ll*(t[ls(x)].siz+1)*(t[rs(x)].siz+1)*t[x].v;
	t[x].sum=t[ls(x)].sum+t[rs(x)].sum+1ll*(t[ls(x)].siz+1)*(t[rs(x)].siz+1);
}

void apply_tag(int x,int dlt)
{
	if(!x) return;
	t[x].v+=dlt;
	t[x].tag+=dlt;
	t[x].Ans+=1ll*t[x].sum*dlt;
}

void pushdown(int x)
{
	if(t[x].tag)
	{
		apply_tag(ls(x),t[x].tag);
		apply_tag(rs(x),t[x].tag);
		t[x].tag=0;
		pushup(x);
	}
}

void pd(int x){if(fa(x)) pd(fa(x));pushdown(x);}

void Rotate(int x)
{
	int y=fa(x),z=fa(y);
	bool rsx=rson(x),rsy=rson(y);
	if(z) t[z].son[rsy]=x;
	else Rt=x;
	t[y].son[rsx]=t[x].son[!rsx];
	t[x].son[!rsx]=y;
	fa(t[y].son[rsx])=y;
	fa(y)=x;fa(x)=z;
	pushup(y);pushup(x);
}

void RotateUp(int x)
{
	pd(x);
	t[x].v=0,pushup(x); //notice
	while(fa(x)) Rotate(x);
}

void build(int &x,int l,int r)
{
	if(l>r) return;
	int mid=(l+r)>>1;
	x=++cnt;t[x].siz=1;
	pnt[mid]=x;t[x].sum=1;
	if(l<mid) build(ls(x),l,mid-1),fa(ls(x))=x;
	if(mid<r) build(rs(x),mid+1,r),fa(rs(x))=x;
	pushup(x);
}

int main()
{
	scanf("%d%d%d",&R,&C,&N);
	for(int i=1,x,y;i<=N;i++)
	{
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
	}
	build(Rt,1,C);
	Ans=(ll)R*(R+1)/2*(ll)C*(C+1)/2;
	for(int i=1;i<=R;i++)
	{
		apply_tag(Rt,1);
		for(int p:v[i])
			RotateUp(pnt[p]);
		Ans-=t[Rt].Ans;
	}
	printf("%lld\n",Ans);
}
