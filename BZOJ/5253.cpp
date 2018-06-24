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
const int INF=1<<30;

int n,q;
char str[MAXN];

namespace Segment_Tree{
    struct node{
        int l,r,mn,mx;
        ll S;
    }t[MAXN<<7],VOID;
    int cnt;
    void insert(int &x,int l,int r,int pos)
    {
        if(!x) x=++cnt,t[x].mx=t[x].mn=pos;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].l,l,mid,pos);
        else insert(t[x].r,mid+1,r,pos);
    }
    int query_mx(int x,int l,int r,int ql,int qr)
    {
        // printf("mx:%d %d %d %d\n",l,r,ql,qr);
        if(ql<=l&&r<=qr) return t[x].mx;
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret=max(ret,query_mx(t[x].l,l,mid,ql,qr));
        if(qr>mid) ret=max(ret,query_mx(t[x].r,mid+1,r,ql,qr));
        return ret;
    }
    int query_mn(int x,int l,int r,int ql,int qr)
    {
        // printf("mn:%d %d %d %d\n",l,r,ql,qr);
        if(ql<=l&&r<=qr) return t[x].mn?t[x].mn:INF;
        int mid=(l+r)>>1,ret=INF;
        if(ql<=mid) ret=min(ret,query_mn(t[x].l,l,mid,ql,qr));
        if(qr>mid) ret=min(ret,query_mn(t[x].r,mid+1,r,ql,qr));
        return ret;
    }
    int lstmx,tmprt;
    ll query(int x,int ql,int qr,int l,int r)
    {
        if(ql<=l&&r<=qr)
        {
            ll ret=t[x].S-1LL*(t[x].mx-t[x].mn)*(ql-1);
            if(t[x].mn)
            {
                if(lstmx)
                    ret+=1LL*(t[x].mn-lstmx)*(t[x].mn-ql+1);
                else
                {
                    int lst=query_mx(tmprt,1,n,1,t[x].mn-1);
                    ret+=1LL*(t[x].mn-lst)*(t[x].mn-ql+1);
                }
            }
            lstmx=max(lstmx,t[x].mx);
            return ret;
        }
        int mid=(l+r)>>1;
        ll ret=0;
        if(ql<=mid)
            ret+=query(t[x].l,ql,qr,l,mid);
        if(qr>=mid+1)
            ret+=query(t[x].r,ql,qr,mid+1,r);
        return ret;
    }
    int merge(int x,int y)
    {
        if(!x||!y) return x|y;
        int ret=++cnt;
        t[ret].mn=min(t[x].mn,t[y].mn);
        t[ret].mx=max(t[x].mx,t[y].mx);
        t[ret].l=merge(t[x].l,t[y].l);
        t[ret].r=merge(t[x].r,t[y].r);
        t[ret].S=t[t[ret].l].S+t[t[ret].r].S+(t[t[ret].l].mx?1LL*t[t[ret].r].mn*(t[t[ret].r].mn-t[t[ret].l].mx):0);
        return ret;
    }
}

namespace SAM{
    int son[MAXN<<1][10],par[MAXN<<1],mx[MAXN<<1];
    int nd[MAXN<<1],jmp[MAXN<<1][20];
    int cnt=1,rt=1,lst=1,srt[MAXN<<1];
    vector<int> V[MAXN<<1];
    void insert(int x,int pos)
    {
        x-='0';
        int p=lst,np=++cnt;
        mx[np]=mx[p]+1;
        Segment_Tree::insert(srt[np],1,n,pos);
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
                memcpy(son[nq],son[q],sizeof son[q]);
                while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
            }
        }
        nd[pos]=lst=np;
    }
    void dfs(int x)
    {
        for(auto v:V[x]) 
            dfs(v),srt[x]=Segment_Tree::merge(srt[x],srt[v]);
    }
    void init()
    {
        for(int i=2;i<=cnt;i++) V[par[i]].push_back(i),jmp[i][0]=par[i];
        for(int j=1;j<20;j++)
            for(int i=1;i<=cnt;i++)
                jmp[i][j]=jmp[jmp[i][j-1]][j-1];
        dfs(1);
    }
    int locate(int pos,int len)
    {
        int x=nd[pos];
        for(int i=19;~i;i--)
            if(mx[jmp[x][i]]>=len) x=jmp[x][i];
        return x;
    }
}

inline ll calc(int l,int r)
{
    int L=n-r-1,R=n-l-1;
    return 1LL*(L+R)*(R-L+1)/2;
}

int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++) SAM::insert(str[i],i);
    SAM::init();
    for(int i=1,l,r,len,x;i<=q;i++)
    {
        scanf("%d%d",&l,&r);len=r-l+1;
        x=SAM::locate(r,len);
        int ln=Segment_Tree::t[SAM::srt[x]].mx-len+1,r1=Segment_Tree::t[SAM::srt[x]].mn;
        ll ans=0;
        if(ln<r1) ans=Segment_Tree::t[SAM::srt[x]].S-1ll*(ln+len-1-r1)*ln+calc(ln,r1-1)+1ll*(r1-len)*(r1-ln);
        else
        {
            if(ln-r1-1>=len&&Segment_Tree::query_mn(SAM::srt[x],1,n,r1+len,ln-1)!=INF) ans=0;
            else
            {
                Segment_Tree::lstmx=0, Segment_Tree::tmprt=SAM::srt[x];
                ans=Segment_Tree::query(SAM::srt[x],ln+1,r1+len-2,1,n);
                int posl=Segment_Tree::query_mx(SAM::srt[x],1,n,1,r1+len-2),posr=Segment_Tree::query_mn(SAM::srt[x],1,n,posl+1,n);
                if(posr>ln) ans+=1ll*(r1-posl+len-1)*(posr-ln);
            }
        }
        printf("%lld\n",calc(1,n-1)-ans);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}