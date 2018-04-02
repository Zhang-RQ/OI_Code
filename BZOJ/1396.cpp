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
const int MAXN=200010;
struct Segment_tree{
    int t[MAXN<<2],tag[MAXN<<2];
    void pushup(int x){t[x]=min(t[x<<1],t[x<<1|1]);}
    void pushdown(int x)
    {
        if(tag[x]!=0x3f3f3f3f)
        {
            tag[x<<1]=min(tag[x],tag[x<<1]);
            tag[x<<1|1]=min(tag[x],tag[x<<1|1]);
            t[x<<1]=min(t[x<<1],tag[x]);
            t[x<<1|1]=min(t[x<<1|1],tag[x]);
            tag[x]=0x3f3f3f3f;
        }
    }
    void build(int x,int l,int r)
    {
        t[x]=tag[x]=0x3f3f3f3f;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    }
    void change(int x,int l,int r,int cl,int cr,int val)
    {
        if(cl<=l&&r<=cr){t[x]=min(t[x],val);tag[x]=min(tag[x],val);return;}
        int mid=(l+r)>>1;pushdown(x);
        if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
        if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
        pushup(x);
    }
    int query(int x,int l,int r,int pos)
    {
        if(l==r) return t[x];
        int mid=(l+r)>>1;
        pushdown(x);
        if(pos<=mid) return query(x<<1,l,mid,pos);
        else return query(x<<1|1,mid+1,r,pos);
    }
}A,B;
int son[MAXN][26],siz[MAXN],par[MAXN],mx[MAXN],endpos[MAXN];
int buk[MAXN],tp[MAXN],mn[MAXN];
int rt=1,cnt=1,lst=1,n,ans[MAXN];
char str[MAXN];
void insert(int x,int pos)
{
    x-='a';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;endpos[np]=pos;siz[np]=1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void calc()
{
    for(int i=1;i<=cnt;i++) buk[mx[i]]++;
    for(int i=1;i<=n;i++)   buk[i]+=buk[i-1];
    for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--) siz[par[tp[i]]]+=siz[tp[i]],mn[i]=mx[par[i]]+1;
    A.build(1,1,n);B.build(1,1,n);
    for(int i=1;i<=cnt;i++)
        if(siz[i]==1)
        {
            // printf("c(A):%d %d %d\n",endpos[i]-mx[i]+1,endpos[i]-mn[i]+1,endpos[i]+1);
            A.change(1,1,n,endpos[i]-mx[i]+1,endpos[i]-mn[i]+1,endpos[i]+1);
            // printf("c(B):%d %d %d\n",endpos[i]-mn[i]+1,endpos[i],mn[i]);
            B.change(1,1,n,endpos[i]-mn[i]+1,endpos[i],mn[i]);
        }
    for(int i=1;i<=n;i++)
        ans[i]=min(A.query(1,1,n,i)-i,B.query(1,1,n,i));
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)
        insert(str[i],i);
    calc();
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
}
