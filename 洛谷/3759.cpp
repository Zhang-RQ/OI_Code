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
const int MAXN=1E5+5;
const int P=1E9+7;
struct book{
    int pos,val;
}b[MAXN];
int n,m,x,y;
ll ans=0;
namespace get_raw_answer{
    struct BIT{
        ll t[MAXN];
        void change(int pos,int val)
        {
            for(int i=pos;i<=n;i+=i&-i) t[i]+=val;
        }
        ll query(int pos)
        {
            ll ret=0;
            for(int i=pos;i>=1;i-=i&-i) ret+=t[i];
            return ret;
        }
    }nm,vl;
    void get()
    {
        for(int i=1;i<=n;i++)
        {
            (ans+=(nm.query(n)-nm.query(b[i].pos))*b[i].val)%=P;
            (ans+=vl.query(n)-vl.query(b[i].pos))%=P;
            vl.change(b[i].pos,b[i].val);
            nm.change(b[i].pos,1);
        }
    }
}
namespace Segment_tree{
    struct node{
        int ls,rs;
        ll sum,siz;
    }t[MAXN<<7];
    int cnt;
    void insert(int &x,int l,int r,int pos,int val,int _x)
    {
        x=++cnt;
        t[x]=t[_x];
        t[x].siz+=val>0?1:-1;t[x].sum+=val;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].ls,l,mid,pos,val,t[_x].ls);
        else insert(t[x].rs,mid+1,r,pos,val,t[_x].rs);
    }
    ll query(int x,int l,int r,int ql,int qr,const bool &tp)
    {
        if(ql<=l&&r<=qr) return tp?t[x].sum:t[x].siz;
        int mid=(l+r)>>1;
        ll ret=0;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr,tp);
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr,tp);
        return ret%P;
    }
}
namespace BIT{
    int rt[MAXN];
    void change(int ps,int pos,int val)
    {
        for(int i=ps;i<=n;i+=i&-i) Segment_tree::insert(rt[i],1,100000,pos,val,rt[i]);
    }
    ll query(int L,int R,int l,int r,bool tp)
    {
        if(L>R||l>r) return 0;
        ll ret=0;
        for(int i=R;i>=1;i-=i&-i) ret+=Segment_tree::query(rt[i],1,100000,l,r,tp);
        for(int i=L-1;i>=1;i-=i&-i) ret-=Segment_tree::query(rt[i],1,100000,l,r,tp);
        return ret;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&b[i].pos,&b[i].val),BIT::change(i,b[i].pos,b[i].val);
    get_raw_answer::get();
    // printf("raw_ans=%lld\n",ans);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        if(x==y) {printf("%lld\n",ans);continue;}
        if(x>y) swap(x,y);
        (ans+=BIT::query(x+1,y-1,1,b[y].pos-1,1))%=P;
        (ans+=BIT::query(x+1,y-1,1,b[y].pos-1,0)*b[y].val)%=P;
        ans=(ans-BIT::query(x+1,y-1,b[y].pos+1,n,1)%P+P)%P;
        ans=(ans-BIT::query(x+1,y-1,b[y].pos+1,n,0)*b[y].val%P)%P;
        (ans+=BIT::query(x+1,y-1,b[x].pos+1,n,1))%=P;
        (ans+=BIT::query(x+1,y-1,b[x].pos+1,n,0)*b[x].val%P)%=P;
        ans=(ans-BIT::query(x+1,y-1,1,b[x].pos-1,1)%P+P)%P;
        ans=(ans-BIT::query(x+1,y-1,1,b[x].pos-1,0)*b[x].val%P+P)%P;
        if(b[x].pos>b[y].pos) ans=(ans-(b[x].val+b[y].val)%P+P)%P;
        else (ans+=b[x].val+b[y].val)%=P;
        BIT::change(x,b[x].pos,-b[x].val);BIT::change(x,b[y].pos,b[y].val);
        BIT::change(y,b[y].pos,-b[y].val);BIT::change(y,b[x].pos,b[x].val);
        swap(b[x],b[y]);
        ans%=P;
        printf("%lld\n",ans);
    }
}
