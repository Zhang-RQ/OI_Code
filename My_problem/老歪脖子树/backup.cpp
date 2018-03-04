#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int P=1E9+7;
const int MAXN=5E5+5;
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
#define fa(x) tree[x].fa
struct node{
    int son[2],fa,siz;            //tree struct
    ll mul,sum,lmx,rmx,mx;                  //val
    int val,minn,maxn;          //val
    int edt,mult;          //tags
}tree[MAXN];
int root,cnt;
int arr[MAXN],n,q,opt,L,R,nk,pos,val;
ll ksm(ll base,int b)
{
    ll ret=1;
    while(b)
    {
        if(b&1)  (ret*=base)%=P;
        (base*=base)%=P;
        b>>=1;
    }
    return ret%P;
}
inline void pushup(int x)
{
    if(ls(x)&&rs(x))
    {
        fa(ls(x))=fa(rs(x))=x;
        tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
        (tree[x].sum=(tree[ls(x)].sum+tree[rs(x)].sum)%P+tree[x].val)%=P;
        (tree[x].mul=((tree[ls(x)].mul*tree[rs(x)].mul)%P)*tree[x].val)%=P;
        tree[x].minn=min(tree[x].val,min(tree[ls(x)].minn,tree[rs(x)].minn));
        tree[x].maxn=max(tree[x].val,max(tree[ls(x)].maxn,tree[rs(x)].maxn));
        tree[x].lmx=max(max(tree[ls(x)].lmx,tree[ls(x)].sum+tree[x].val+tree[rs(x)].lmx),0ll);
        tree[x].rmx=max(max(tree[rs(x)].rmx,tree[rs(x)].sum+tree[x].val+tree[ls(x)].rmx),0ll);
        tree[x].mx=max(max(tree[ls(x)].rmx+tree[rs(x)].lmx+tree[x].val,max(max(tree[ls(x)].mx,tree[rs(x)].mx),max(tree[x].lmx,tree[x].rmx))),0ll);
    }
    else if(ls(x))
    {
        fa(ls(x))=x;
        tree[x].siz=tree[ls(x)].siz+1;
        (tree[x].sum=tree[ls(x)].sum%P+tree[x].val)%=P;
        (tree[x].mul=tree[ls(x)].mul*tree[x].val)%=P;
        tree[x].minn=min(tree[x].val,tree[ls(x)].minn);
        tree[x].maxn=max(tree[x].val,tree[ls(x)].maxn);
        tree[x].lmx=max(max(tree[ls(x)].lmx,tree[ls(x)].sum+tree[x].val),0ll);
        tree[x].rmx=max(tree[ls(x)].rmx+tree[x].val,0ll);
        tree[x].mx=max(max(tree[ls(x)].mx,max(tree[ls(x)].rmx+tree[x].val,max(tree[x].lmx,tree[x].rmx))),0ll);
    }
    else if(rs(x))
    {
        fa(rs(x))=x;
        tree[x].siz=tree[rs(x)].siz+1;
        (tree[x].sum=tree[rs(x)].sum%P+tree[x].val)%=P;
        (tree[x].mul=tree[rs(x)].mul*tree[x].val)%=P;
        tree[x].minn=min(tree[x].val,tree[rs(x)].minn);
        tree[x].maxn=max(tree[x].val,tree[rs(x)].maxn);
        tree[x].rmx=max(max(tree[rs(x)].rmx,tree[rs(x)].sum+tree[x].val),0ll);
        tree[x].lmx=max(tree[rs(x)].lmx+tree[x].val,0ll);
        tree[x].mx=max(max(tree[rs(x)].mx,max(tree[rs(x)].lmx+tree[x].val,max(tree[x].lmx,tree[x].rmx))),0ll);
    }
    else
    {
        tree[x].siz=1;
        tree[x].minn=tree[x].maxn=tree[x].mul=tree[x].sum=tree[x].val;
        tree[x].lmx=tree[x].rmx=tree[x].mx=tree[x].val>0?tree[x].val:0;
    }
}
inline void pushdown(int x)
{
    if(tree[x].edt!=0)
    {
        int k=tree[x].edt%P;
        tree[x].edt=0;
        tree[ls(x)].mult=tree[rs(x)].mult=1;
        tree[ls(x)].edt=tree[rs(x)].edt=k;  //tags
        tree[ls(x)].val=tree[rs(x)].val=k;  //val
        tree[ls(x)].sum=tree[ls(x)].val*tree[ls(x)].siz%P;
        tree[rs(x)].sum=tree[rs(x)].val*tree[rs(x)].siz%P;
        tree[ls(x)].mul=ksm(tree[ls(x)].val,tree[ls(x)].siz);
        tree[rs(x)].mul=ksm(tree[rs(x)].val,tree[rs(x)].siz);
        tree[ls(x)].minn=tree[ls(x)].maxn=tree[ls(x)].val;
        tree[rs(x)].minn=tree[rs(x)].maxn=tree[rs(x)].val;
        if(k>0)
        {
            tree[ls(x)].lmx=tree[ls(x)].rmx=tree[ls(x)].mx=tree[ls(x)].siz*k;
            tree[rs(x)].lmx=tree[rs(x)].rmx=tree[rs(x)].mx=tree[rs(x)].siz*k;
        }
        else
        {
            tree[ls(x)].lmx=tree[ls(x)].rmx=tree[ls(x)].mx=0;
            tree[rs(x)].lmx=tree[rs(x)].rmx=tree[rs(x)].mx=0;
        }
    }
    if(tree[x].mult!=1)
    {
        //printf("rs:%d minn:%d maxn:%d\n",rs(x),tree[rs(x)].minn,tree[rs(x)].maxn);
        int k=tree[x].mult;
        tree[x].mult=1;
        (tree[ls(x)].mult*=k)%=P;(tree[rs(x)].mult*=k)%=P;  //tags
        //(tree[ls(x)].edt*=k)%=P;(tree[rs(x)].edt*=k)%=P;    //tags
        (tree[ls(x)].sum*=k)%=P;            //val
        (tree[rs(x)].sum*=k)%=P;
        (tree[ls(x)].val*=k)%=P;
        (tree[rs(x)].val*=k)%=P;
        (tree[ls(x)].maxn*=k)%=P;
        (tree[rs(x)].maxn*=k)%=P;
        (tree[ls(x)].minn*=k)%=P;
        (tree[rs(x)].minn*=k)%=P;
        (tree[ls(x)].mul*=ksm(k,tree[ls(x)].siz))%=P;
        (tree[rs(x)].mul*=ksm(k,tree[rs(x)].siz))%=P;
        tree[ls(x)].lmx*=k;tree[ls(x)].rmx*=k;tree[ls(x)].mx*=k;
        tree[rs(x)].lmx*=k;tree[rs(x)].rmx*=k;tree[rs(x)].mx*=k;
        //printf("rs:%d minn:%d maxn:%d\n",rs(x),tree[rs(x)].minn,tree[ls(x)].maxn);
    }
    pushup(x);
}
inline void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=(rs(y)==x),rsy=(rs(fa(y))==y);
    if(z) tree[z].son[rsy]=x,fa(x)=z;
    else root=x,fa(x)=0;
    tree[y].son[rsx]=tree[x].son[!rsx];
    tree[x].son[!rsx]=y;
    pushup(y);
    pushup(x);
}
void print(int);
inline void splay(int x,int pos)
{
    while(fa(x)!=pos)
    {
        int y=fa(x);
        bool rsx=(rs(y)==x),rsy=(rs(fa(y))==y);
        if(fa(y)!=pos) rotate(rsx^rsy?x:y);
        rotate(x);
    }
}
void build(int &x,int l,int r)
{
	if(l>r) return;
    if(!x) x=++cnt;
    tree[x].mult=1;
    if(l==r) {tree[x].siz=1;tree[x].val=tree[x].minn=tree[x].maxn=tree[x].mul=tree[x].sum=arr[l];tree[x].lmx=tree[x].rmx=tree[x].mx=arr[l]>0?arr[l]:0;return;}
    int mid=(l+r)>>1;
    tree[x].siz=1;
    tree[x].val=tree[x].minn=tree[x].maxn=tree[x].mul=tree[x].sum=arr[mid];
    tree[x].lmx=tree[x].rmx=tree[x].mx=tree[x].val>0?tree[x].val:0;
    build(tree[x].son[0],l,mid-1);
    build(tree[x].son[1],mid+1,r);
    pushup(x);
}
int kth(int x,int rk)
{
    if(x==root&&rk>tree[root].siz) {puts("ERROR_ASKING_NUM_OVER_FLOW");return 0;}
    pushdown(x);
    if(tree[ls(x)].siz+1==rk) return x;
    if(tree[ls(x)].siz+1<rk) return kth(rs(x),rk-1-tree[ls(x)].siz);
    return kth(ls(x),rk);
}
inline int get_range(int l,int r)
{
    int tmp=kth(root,l-1);
    splay(tmp,0);
    splay(kth(root,r+1),tmp);
    return ls(rs(root));
}
inline void edit(int l,int r,int val)
{
	int x=get_range(l,r);
    tree[x].mult=1;
	tree[x].val=tree[x].edt=val;
	tree[x].sum=tree[x].val*tree[x].siz%P;
	tree[x].mul=ksm(tree[x].val,tree[x].siz);
	tree[x].minn=tree[x].maxn=tree[x].val;
    tree[x].lmx=tree[x].rmx=tree[x].mx=tree[x].val>0?(tree[x].val*tree[x].siz):0;
}
inline int query_min(int l,int r)
{
	return tree[get_range(l,r)].minn;
}
inline int query_max(int l,int r)
{
	return tree[get_range(l,r)].maxn;
}
inline void ins(int pos,int tn)
{
	int x=0,tmp;
    //print(root);
    splay(kth(root,pos),0);
    //printf("root=%d pos=%d\n",root,pos);
    build(x,1,tn);
    tmp=x;
    //print(x);
    while(rs(tmp))  tmp=rs(tmp);
    rs(tmp)=rs(root);
    while(fa(tmp))
        pushup(tmp),
        tmp=fa(tmp);
    pushup(tmp);
    rs(root)=tmp;
    pushup(root);
    //puts("23");
    //print(root);
}
inline void del(int l,int r)
{
	int x=get_range(l,r);
	ls(fa(x))=0;
	pushup(fa(x));
	fa(x)=0;
}
inline void mul(int l,int r,int val)
{
	int x=get_range(l,r);
	(tree[x].val*=val)%=P;
	(tree[x].sum*=val)%=P;
	(tree[x].mul*=ksm(val,tree[x].siz))%=P;
	(tree[x].minn*=val)%=P;
	(tree[x].maxn*=val)%=P;
	(tree[x].mult*=val)%=P;
    //(tree[x].edt*=val)%=P;
    tree[x].lmx*=val;tree[x].rmx*=val;tree[x].mx*=val;
}
inline ll query_mul(int l,int r)
{
	return tree[get_range(l,r)].mul;
}
inline ll query_sum(int l,int r)
{
	return tree[get_range(l,r)].sum;
}
inline ll query_max_sub_sum(int l,int r)
{
    return tree[get_range(l,r)].mx%P;
}
void print(int x)
{
	if(ls(x)) print(ls(x));
    pushdown(x);
	//printf("%d ls:%d rs:%d fa:%d val:%d maxn:%d minn:%d siz:%d sum:%lld lx:%lld rx:%lld mx:%lld edt:%d mult:%d mul:%lld\n",x,ls(x),rs(x),fa(x),tree[x].val,tree[x].maxn,tree[x].minn,tree[x].siz,tree[x].sum,tree[x].lmx,tree[x].rmx,tree[x].mx,tree[x].edt,tree[x].mult,tree[x].mul);
	if(rs(x)) print(rs(x));
}
int main()
{
	scanf("%d%d",&n,&q);
    arr[1]=arr[n+2]=1;
	for(int i=2;i<=n+1;i++) scanf("%d",&arr[i]);
	build(root,1,n+2);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&opt);
        print(root);
        //printf("siz=%d\n",tree[root].siz);
		switch(opt)
		{
			case 1: scanf("%d%d%d",&L,&R,&val),L++,R++,edit(L,R,val);break;
			case 2: scanf("%d%d",&L,&R),L++,R++,printf("%d\n",query_max(L,R));break;
			case 3: scanf("%d%d",&L,&R),L++,R++,printf("%d\n",query_min(L,R));break;
			case 4: scanf("%d%d",&nk,&pos);for(int j=1;j<=nk;j++){scanf("%d",&arr[j]);}pos++;ins(pos,nk);break;
			case 5: scanf("%d%d",&L,&R);L++;R++;del(L,R);break;
			case 6: scanf("%d%d",&L,&R);L++;R++;printf("%lld\n",query_max_sub_sum(L,R)%P);break;
			case 7: scanf("%d%d%d",&L,&R,&val);L++;R++;mul(L,R,val);break;
			case 8: scanf("%d%d",&L,&R);L++;R++;printf("%lld\n",query_sum(L,R)%P);break;
			case 9: scanf("%d%d",&L,&R);L++;R++;printf("%lld\n",query_mul(L,R)%P);break;
            case 10: print(root);break;
            default: puts("ERROR_UNKOWN_OPT");break;
		}
        //print(root);
	}
    //print(root);
    return 0;
}
