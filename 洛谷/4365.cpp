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
#include<cassert>
#include<stack>
typedef unsigned int uint;
using namespace std;
const uint P=64123;
const int MAXN=1700;
const int MAXM=5000;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,rt[MAXN],stk[MAXN<<6],top,cnt,d[MAXN],n,k,w,u,v,ans[MAXN],f[MAXN],tmp[MAXN];
int inv[P+10];
inline void add(int u,int v) {Edge[++cnt_e].v=v;Edge[cnt_e].nxt=head[u];head[u]=cnt_e;}
struct data{
    uint a,b,c,d;
    inline void clear(){a=1;b=c=d=0;}
    inline data(uint _a=1,uint _b=0,uint _c=0,uint _d=0):a(_a),b(_b),c(_c),d(_d){}
    inline data operator * (const data &rhs) const {return data(a*rhs.a%P,(rhs.b+b*rhs.a%P)%P,(a*rhs.c%P+c)%P,(b*rhs.c%P+d+rhs.d)%P);}
    inline data operator *= (const data &rhs) {return (*this)=(*this)*rhs;}
};
struct node{
    int ls,rs;
    data val;
    node(){val.a=1;val.b=val.c=val.d=ls=rs=0;}
    inline void clear(){val.a=1;val.b=val.c=val.d=ls=rs=0;}
}t[MAXN<<6];
inline int newnode() {if(top) return stk[top--];else return ++cnt;}
inline void delnode(int &x)
{
    if(!x) return;
    delnode(t[x].ls);delnode(t[x].rs);
    stk[++top]=x;t[x].clear();x=0;
}
inline void pushdown(const int &x)
{
    if(!t[x].ls) t[x].ls=newnode();
    if(!t[x].rs) t[x].rs=newnode();
    t[t[x].ls].val*=t[x].val;
    t[t[x].rs].val*=t[x].val;
    t[x].val.clear();
}
void change(int &x,int l,int r,int cl,int cr,data val)
{
    if(!x) x=newnode();
    if(cl<=l&&r<=cr) {t[x].val*=val;return;}
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(t[x].ls,l,mid,cl,cr,val);
    if(cr>mid)  change(t[x].rs,mid+1,r,cl,cr,val);
}
int merge(int &x,int &y)
{
    if(!x||!y) return x|y;
    if(!t[x].ls&&!t[x].rs)  swap(x,y);
    if(!t[y].ls&&!t[y].rs)
    {
        t[x].val*=data(t[y].val.b,0,0,0);
        t[x].val*=data(1,0,0,t[y].val.d);
        return x;
    }
    pushdown(x);pushdown(y);
    t[x].ls=merge(t[x].ls,t[y].ls);
    t[x].rs=merge(t[x].rs,t[y].rs);
    return x;
}
uint query(int x,int l,int r)
{
    if(l==r) return t[x].val.d;
    int mid=(l+r)>>1;
    uint ret=0;
    pushdown(x);
    ret=query(t[x].ls,l,mid);
    (ret+=query(t[x].rs,mid+1,r))%=P;
    return ret;
}
void dfs(int x,int fa,int k0)
{
    change(rt[x],1,w,1,w,data(0,1,0,0));
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x,k0);
        merge(rt[x],rt[v]);
        delnode(rt[v]);
    }
    change(rt[x],1,w,1,d[x],data(k0,0,0,0));
    change(rt[x],1,w,1,w,data(1,0,1,0));
    change(rt[x],1,w,1,w,data(1,1,0,0));
}
uint Lagrange_interpolation()
{
    uint ret=0;
    memset(f,0,sizeof f);f[0]=1;
    for(int i=1;i<=n+1;i++)
    {
        for(int j=n+1;j>=1;j--)
            f[j]=f[j]*(P-i)%P,f[j]=(f[j]+f[j-1])%P;
        f[0]=f[0]*(P-i)%P;
    }
    for(int i=1;i<=n+1;i++)
    {
        memcpy(tmp,f,sizeof(uint)*(n+1));
        for(int j=0;j<=n;j++)  //divide by (x-i)
            tmp[j]=P-tmp[j]*inv[i]%P,tmp[j+1]=(tmp[j+1]-tmp[j]+P)%P;
        uint tans=0;
        for(int j=k;j<=n;j++) tans=(tans+tmp[j])%P;
        for(int j=1;j<=n+1;j++)
        {
            if(i==j) continue;
            if(j<i) tans=tans*inv[i-j]%P;
            else tans=tans*(P-inv[j-i])%P;
        }
        ret=(ret+tans*ans[i]%P)%P;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d",&n,&k,&w);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1;i<n;i++)  scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n+1;i++)
    {
        dfs(1,0,i);
        ans[i]=query(rt[1],1,w);
        delnode(rt[1]);
    }
    inv[1]=1;
    for(int i=2;i<P;i++)
        inv[i]=(P-(P/i)*inv[P%i]%P)%P,assert(inv[i]>0);
    printf("%u\n",Lagrange_interpolation());
}
