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
const int MAXN=3E5+5;
struct opte{
    int x,y,tp,id;  // tp=0 点  tp=1 询问
    opte(){}
    opte(int _x,int _y,int _tp,int _id):x(_x),y(_y),tp(_tp),id(_id){}
    bool operator < (const opte &rhs) const
    {
        if(x!=rhs.x) return x<rhs.x;
        return id<rhs.id;
    }
}opt[MAXN<<1],tmp[MAXN<<1];
int t[1000010],max_,ans[MAXN<<1],n,m,x,y,cnt,ot,iii,ch[MAXN<<1];
void clear(int pos)
{
    for(int i=pos;i<=max_;i+=i&-i)
        t[i]=0;
}
void change(int pos,int val)
{
    for(int i=pos;i<=max_;i+=i&-i)
        t[i]=max(t[i],val);
}
int query(int pos)
{
    int ret=0;
    for(int i=pos;i>=1;i-=i&-i)
        ret=max(ret,t[i]);
    return ret?ret:-1000000;
}
void CDQ(int l,int r)
{
    if (l>=r) return;
    int mid=(l+r)>>1;
    int pa=l,pb=mid+1;
    for (int i=l;i<=r;++i)
        if (opt[i].id<=mid) tmp[pa++]=opt[i];
        else tmp[pb++]=opt[i];
    for (int i=l;i<=r;++i) opt[i]=tmp[i];
    pa=l,pb=mid+1;int tot=0;
    while (pb<=r)
    {
        if (opt[pb].tp)
        {
            while (pa<=mid&&opt[pa].x<=opt[pb].x)
            {
                if(!opt[pa].tp) change(opt[pa].y,opt[pa].x+opt[pa].y);
                ch[++tot]=opt[pa].y;
                ++pa;
            }
            int t=query(opt[pb].y);
            if(t!=-1) ans[opt[pb].id]=min(ans[opt[pb].id],opt[pb].x+opt[pb].y-t);
        }
        ++pb;
    }
    for (int i=1;i<=tot;++i) clear(ch[i]);
    CDQ(l,mid);
    CDQ(mid+1,r);
}
int main()
{
    memset(ans,0x3f,sizeof(ans));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x,&y),x++,y++,opt[++cnt]=opte(x,y,0,i),max_=max(max_,max(x,y));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&ot,&x,&y);x++,y++;max_=max(max_,max(x,y));
        if(ot==2) opt[++cnt]=opte(x,y,1,n+i);
        else opt[++cnt]=opte(x,y,0,n+i);
    }
    max_+=10;
    sort(opt+1,opt+1+cnt);CDQ(1,cnt);
    for(int i=1;i<=cnt;i++) opt[i].x=max_-opt[i].x;
    sort(opt+1,opt+1+cnt);CDQ(1,cnt);
    for(int i=1;i<=cnt;i++) opt[i].y=max_-opt[i].y;
    sort(opt+1,opt+1+cnt);CDQ(1,cnt);
    for(int i=1;i<=cnt;i++) opt[i].x=max_-opt[i].x;
    sort(opt+1,opt+1+cnt);CDQ(1,cnt);
    for(int i=1;i<=cnt;i++)
        if(ans[i]!=0x3f3f3f3f) printf("%d\n",ans[i]);
}
