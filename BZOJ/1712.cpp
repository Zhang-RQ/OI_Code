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
const int MAXN=500010;
struct node{
    int mx,tag;
}t[MAXN<<4];
struct section{
    int l,r,len;
    inline bool operator < (const section &rhs) const
    {
        if(len!=rhs.len) return len<rhs.len;
        if(l!=rhs.l) return l<rhs.l;
        return r<rhs.r;
    }
}s[MAXN];
inline void pushup(const int &x) {t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);}
inline void pushdown(const int &x) {if(t[x].tag) t[x<<1].mx+=t[x].tag,t[x<<1|1].mx+=t[x].tag,t[x<<1].tag+=t[x].tag,t[x<<1|1].tag+=t[x].tag,t[x].tag=0;}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {t[x].mx+=val;t[x].tag+=val;return;}
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
    pushup(x);
}
int tmp[MAXN<<1],n,m,cnt;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&s[i].l,&s[i].r),s[i].len=s[i].r-s[i].l,tmp[++cnt]=s[i].l,tmp[++cnt]=s[i].r;
    sort(s+1,s+1+n);
    sort(tmp+1,tmp+1+cnt);
    cnt=unique(tmp+1,tmp+1+cnt)-tmp-1;
    for(int i=1;i<=n;i++)
        s[i].l=lower_bound(tmp+1,tmp+1+cnt,s[i].l)-tmp,
        s[i].r=lower_bound(tmp+1,tmp+1+cnt,s[i].r)-tmp;
    int j=0,ans=1<<30;
    for(int i=1;i<=n;i++)
    {
        while((j-i+1<m||t[1].mx<m)&&j<n) j++,change(1,1,cnt,s[j].l,s[j].r,1);
        if(j==n&&t[1].mx<m) break;
        ans=min(ans,s[j].len-s[i].len);
        change(1,1,cnt,s[i].l,s[i].r,-1);
    }
    printf("%d\n",ans==(1<<30)?-1:ans);
    #ifdef LOCAL
        system("pause");
    #endif
}