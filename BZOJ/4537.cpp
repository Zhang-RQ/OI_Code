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
const int MAXN=2E5+10;
const int MAXM=2E5+10;
struct node{
    int x,y,a,b;
    inline bool operator < (const node &rhs)  const {return a<rhs.a||(a==rhs.a&&b<rhs.b);}
}Edge[MAXM];
struct Query{
    int x,y,a,b,id;
    inline bool operator <  (const Query &rhs) const {return b<rhs.b||(b==rhs.b&&a<rhs.a);}
}Q[MAXN];
namespace UFS
{
    struct operation{
        operation(){}
        operation(int _x,int _y,int _mxAx,int _mxAy,int _mxBx,int _mxBy,int _sizx,int _sizy){x=_x;y=_y;mxAx=_mxAx;mxAy=_mxAy;mxBx=_mxBx;mxBy=_mxBy;sizx=_sizx;sizy=_sizy;}
        int x,y,mxAx,mxAy,mxBx,mxBy,sizx,sizy;
    }stk[MAXN];
    int fa[MAXN],siz[MAXN],mxA[MAXN],mxB[MAXN],top;
    void init(int n)
    {
        for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,mxA[i]=mxB[i]=-1;
        top=0;
    }
    int find(int x) {return x==fa[x]?x:find(fa[x]);}
    void merge(int x,int y,int a,int b)
    {
        x=find(x);y=find(y);
        if(siz[x]<siz[y]) swap(x,y);
        stk[++top]=operation(x,y,mxA[x],mxA[y],mxB[x],mxB[y],siz[x],siz[y]);
        if(x!=y) siz[x]+=siz[y];
        mxA[x]=max(a,max(mxA[x],mxA[y]));
        mxB[x]=max(b,max(mxB[x],mxB[y]));
        if(x!=y) fa[y]=x;
    }
    bool judge(int x,int y,int a,int b)
    {
        int _x=find(x),_y=find(y);
        if(_x!=_y) return 0;
        return mxA[_x]==a&&mxB[_x]==b;
    }
    void rollback()
    {
        operation op=stk[top--];
        fa[op.x]=op.x;fa[op.y]=op.y;
        mxA[op.x]=op.mxAx;mxA[op.y]=op.mxAy;
        mxB[op.x]=op.mxBx;mxB[op.y]=op.mxBy;
        siz[op.x]=op.sizx;siz[op.y]=op.sizy;
    }
}
inline bool cmp (const Query &lhs,const Query &rhs) {return lhs.a<rhs.a;}
inline bool cmp1(const node &lhs,const node &rhs) {return lhs.b<rhs.b;}
vector<Query> blkQ[MAXN];
int n,m,q,bl[MAXN],siz,st[MAXN],ed[MAXN];
bool ans[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    siz=sqrt(m);
    for(int i=1;i<=m;i++)
    {
        bl[i]=(i-1)/siz+1;
        if(!st[bl[i]]) st[bl[i]]=i;
        ed[bl[i]]=i;
    }
    st[bl[m]+1]=ed[bl[m]+1]=m+1;
    for(int i=1;i<=m;i++) scanf("%d%d%d%d",&Edge[i].x,&Edge[i].y,&Edge[i].a,&Edge[i].b);
    sort(Edge+1,Edge+1+m);
    scanf("%d",&q);
    for(int i=1;i<=q;i++) scanf("%d%d%d%d",&Q[i].x,&Q[i].y,&Q[i].a,&Q[i].b),Q[i].id=i;
    sort(Q+1,Q+1+q,cmp);
    int p1=0;
    for(int i=1;i<=q;i++)
    {
        while(Edge[p1+1].a<=Q[i].a&&p1+1<=m) p1++;
        if(p1) blkQ[bl[p1]].push_back(Q[i]);
    }
    for(int i=1;i<=bl[m];i++)
    {
        sort(blkQ[i].begin(),blkQ[i].end());
        UFS::init(n);
        int p1=0,cnt=0;
        for(auto Q:blkQ[i])
        {
            cnt=0;
            while(p1+1<=ed[i-1]&&Edge[p1+1].b<=Q.b) p1++,UFS::merge(Edge[p1].x,Edge[p1].y,Edge[p1].a,Edge[p1].b);
            for(int j=st[i];j<=ed[i];j++)
                if(Edge[j].b<=Q.b&&Edge[j].a<=Q.a) UFS::merge(Edge[j].x,Edge[j].y,Edge[j].a,Edge[j].b),++cnt;
            ans[Q.id]=UFS::judge(Q.x,Q.y,Q.a,Q.b);
            while(cnt--) UFS::rollback();
        }
        sort(Edge+1,Edge+1+ed[i],cmp1);
    }
    for(int i=1;i<=q;i++) puts(ans[i]?"Yes":"No");
    #ifdef LOCAL
        system("pause");
    #endif
}