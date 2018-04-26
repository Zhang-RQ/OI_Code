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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+10;
int son[MAXN][2],t[MAXN<<3],tag[MAXN<<3],rt,fa[MAXN],tot,m,arr[MAXN];
set<int> s;
struct opt{
    int op,val;
}op[MAXN];
std::vector<int> v;
void pushdown(int x)
{
    if(tag[x])
    {
        t[x<<1]+=tag[x];t[x<<1|1]+=tag[x];
        tag[x<<1]+=tag[x];tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {t[x]+=val;tag[x]+=val;return;}
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
}
void change(int x,int l,int r,int pos,int val)
{
    if(l==r) {t[x]=val;return;}
    int mid=(l+r)>>1;pushdown(x);
    if(pos<=mid) change(x<<1,l,mid,pos,val);
    else change(x<<1|1,mid+1,r,pos,val);
}
int query(int x,int l,int r,int pos)
{
    if(l==r) return t[x];
    int mid=(l+r)>>1;pushdown(x);
    if(pos<=mid) return query(x<<1,l,mid,pos);
    else return query(x<<1|1,mid+1,r,pos);
}
int insert(int x)
{
    set<int>::iterator it=s.insert(x).first;
    if(!rt) {rt=x;change(1,1,tot,rt,1);return 1;}
    if(it!=s.begin())
    {
        if(!son[*--it][1]) son[fa[x]=*it][1]=x;
        it++;
    }
    if(!fa[x]) son[fa[x]=*++it][0]=x;
    int dep=query(1,1,tot,fa[x])+1;
    // printf("dep=%d val=%d fa=%d\n",dep,x,fa[x]);
    change(1,1,tot,x,dep);
    return dep;
}
int findmin()
{
    int x=*s.begin(),ret=query(1,1,tot,x);
    if(x==rt) return 1;
    if(x+1<=fa[x]-1) change(1,1,tot,x+1,fa[x]-1,-1);
    change(1,1,tot,1,tot,1);
    son[fa[x]][0]=son[x][1];
    fa[son[x][1]]=fa[x];
    son[fa[rt]=x][1]=rt;fa[rt]=x;
    rt=x;fa[x]=0;
    change(1,1,tot,x,1);
    return ret;
}
int delmin()
{
    int ret=findmin();
    change(1,1,tot,1,tot,-1);
    s.erase(rt);
    rt=son[rt][1];
    fa[rt]=0;
    return ret;
}
int findmax()
{
    int x=*s.rbegin(),ret=query(1,1,tot,x);
    if(x==rt) return 1;
    if(x-1>=fa[x]+1) change(1,1,tot,fa[x]+1,x-1,-1);
    change(1,1,tot,1,tot,1);
    son[fa[x]][1]=son[x][0];
    fa[son[x][0]]=fa[x];
    son[fa[rt]=x][0]=rt;
    rt=x;fa[x]=0;
    change(1,1,tot,x,1);
    return ret;
}
int delmax()
{
    int ret=findmax();
    change(1,1,tot,1,tot,-1);
    s.erase(rt);
    // printf("%d->",rt);
    rt=son[rt][0];
    // printf("%d\n",rt);
    fa[rt]=0;
    return ret;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&op[i].op);
        if(op[i].op==1) scanf("%d",&op[i].val),arr[++tot]=op[i].val;
    }
    sort(arr+1,arr+1+tot);
    tot=unique(arr+1,arr+1+tot)-arr-1;
    for(int i=1;i<=m;i++)
        if(op[i].op==1) op[i].val=lower_bound(arr+1,arr+1+tot,op[i].val)-arr;
    for(int i=1;i<=m;i++)
    {
        switch(op[i].op)
        {
            case 1: printf("%d\n",insert(op[i].val));break;
            case 2: printf("%d\n",findmin());break;
            case 3: printf("%d\n",findmax());break;
            case 4: printf("%d\n",delmin());break;
            case 5: printf("%d\n",delmax());break;
        }
        // printf("rt=%d\n",rt);
    }
}
