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
const int MAXN=200010;
const int MAXQ=200010;
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
template <typename T,int MAXN>
    class segment_tree
    {
        struct node{
            T val,tag;
        };
    private:
        node tree[MAXN<<2];
        inline void pushup(const int &x)
        {
            tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
        }
        inline void pushdown(const int &x,const int &l,const int &r)
        {
            if(tree[x].tag)
            {
                int mid=(l+r)>>1;
                tree[x<<1].val+=(mid-l+1)*tree[x].tag;
                tree[x<<1|1].val+=(r-mid)*tree[x].tag;
                tree[x<<1].tag+=tree[x].tag;
                tree[x<<1|1].tag+=tree[x].tag;
                tree[x].tag=0;
            }
        }
    public:
        inline void clear()
        {
            memset(tree,0,sizeof(tree));
        }
        void build(const int &x,const int &l,const int &r,T *arr)
        {
            if(l==r) {tree[x].val=arr[l];return;}
            int mid=(l+r)>>1;
            build(Ls,arr);
            build(Rs,arr);
            pushup(x);
        }
        void change_point(const int &x,const int &l,const int &r,const int &pos,const T &val)
        {
            if(l==r) {tree[x].val+=val;return;}
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            if(pos<=mid) change_point(Ls,pos,val);
            else change_point(Rs,pos,val);
            pushup(x);
        }
        void change(const int &x,const int &l,const int &r,const int &cl,const int &cr,const T &val)
        {
            if(cl<=l&&r<=cr) {tree[x].val+=val*(r-l+1);tree[x].tag+=val;return;}
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            if(cl<=mid) change(Ls,cl,cr,val);
            if(cr>mid) change(Rs,cl,cr,val);
            pushup(x);
        }
        T query(const int &x,const int &l,const int &r,const int &ql,const int &qr)
        {
            if(ql<=l&&r<=qr) return tree[x].val;
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            T ret=0;
            if(ql<=mid) ret+=query(Ls,ql,qr);
            if(qr>mid) ret+=query(Rs,ql,qr);
            return ret;
        }
        T query_point(const int &x,const int &l,const int &r,const int &pos)
        {
            if(l==r) return tree[x].val;
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            if(pos<=mid) return query_point(Ls,pos);
            else return query_point(Rs,pos);
        }
    };
struct node{
    int id;
    int l,r;
    ll ans;
    bool operator <(node a)
    {
        if(l!=a.l) return l<a.l;
        else return r<a.r;
    }
}query[MAXQ];
bool cmp(node a,node b)
{
    return a.id<b.id;
}
segment_tree<ll,MAXN> s;
stack<int> stk;
ll val[MAXN];
int r[MAXN];
int n,q,p1,p2;
void calc()
{
    s.clear();
    sort(query+1,query+1+q);
    while(!stk.empty()) stk.pop();
    for(int i=n;i>=1;i--)
    {
        while(!stk.empty()&&val[stk.top()]<val[i]) stk.pop();
        if(!stk.empty()) r[i]=stk.top();
        else r[i]=n+1;
        stk.push(i);
    }
    for(int i=n,j=q;i>=1;i--)
    {
        s.change(1,1,n+1,i+1,r[i],p2);
        s.change_point(1,1,n+1,r[i],p1-p2*2);
        while(query[j].l==i&&j>=1)
            query[j].ans+=s.query(1,1,n+1,1,query[j].r),j--;
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&q,&p1,&p2);
    for(int i=1;i<=n;i++)
        scanf("%lld",&val[i]);
    for(int i=1;i<=q;i++)
        scanf("%d%d",&query[i].l,&query[i].r),
        query[i].id=i;
    calc();
    reverse(val+1,val+1+n);
    for(int i=1;i<=q;i++)
        query[i].l=n+1-query[i].l,
        query[i].r=n+1-query[i].r,
        swap(query[i].l,query[i].r);
    calc();
    sort(query+1,query+1+q,cmp);
    for(int i=1;i<=q;i++)
        printf("%lld\n",query[i].ans);
    return 0;
}
