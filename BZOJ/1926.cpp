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
int r,c,m;
namespace solve1
{
    int val[210][210],num[210][210][1010],sum[210][210][1010],mx;
    inline int asksum(int x1,int y1,int x2,int y2,int k) {return sum[x2][y2][k]-sum[x1-1][y2][k]-sum[x2][y1-1][k]+sum[x1-1][y1-1][k];}
    inline int asknum(int x1,int y1,int x2,int y2,int k) {return num[x2][y2][k]-num[x1-1][y2][k]-num[x2][y1-1][k]+num[x1-1][y1-1][k];}
    void init()
    {
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                scanf("%d",&val[i][j]),mx=max(mx,val[i][j]);
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                for(int k=0;k<=mx;k++)
                    num[i][j][k]=num[i][j-1][k]+num[i-1][j][k]-num[i-1][j-1][k]+(val[i][j]>=k),
                    sum[i][j][k]=sum[i][j-1][k]+sum[i-1][j][k]-sum[i-1][j-1][k]+(val[i][j]>=k?val[i][j]:0);
    }
    void solve()
    {
        int x1,y1,x2,y2,h;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
            if(asksum(x1,y1,x2,y2,0)<h) {puts("Poor QLW");continue;}
            int L=1,R=mx,ans=0;
            while(L<=R)
            {
                int mid=(L+R)>>1;
                if(asksum(x1,y1,x2,y2,mid)>=h) L=mid+1,ans=mid;
                else R=mid-1;
            }
            printf("%d\n",asknum(x1,y1,x2,y2,ans)-(asksum(x1,y1,x2,y2,ans)-h)/ans);
        }
    }
}
namespace solve2
{
    struct node{
        int ls,rs,val[2];
    }t[500100<<4];
    int rt[500100],cnt,val[500100],mx;
    void insert(int &x,int l,int r,int pos,int x_)
    {
        x=++cnt;t[x]=t[x_];
        t[x].val[0]++;
        t[x].val[1]+=pos;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].ls,l,mid,pos,t[x_].ls);
        else insert(t[x].rs,mid+1,r,pos,t[x_].rs);
    }
    int query(int x,int l,int r,int ql,int qr,int x_,int f)
    {
        if(ql<=l&&r<=qr) return t[x].val[f]-t[x_].val[f];
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr,t[x_].ls,f);
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr,t[x_].rs,f);
        return ret;
    }
    void init()
    {
        for(int i=1;i<=c;i++)
            scanf("%d",&val[i]),mx=max(mx,val[i]);
        for(int i=1;i<=c;i++)
            insert(rt[i],1,mx,val[i],rt[i-1]);
    }
    void solve()
    {
        int x1,y1,x2,y2,h;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
            if(query(rt[y2],1,mx,1,mx,rt[y1-1],1)<h) {puts("Poor QLW");continue;}
            int L=1,R=mx,ans=0;
            while(L<=R)
            {
                int mid=(L+R)>>1;
                // printf("%d(%d)\n",query(rt[y2],1,mx,1,mid,rt[y1-1],1),mid);
                if(query(rt[y2],1,mx,mid,mx,rt[y1-1],1)>=h) ans=mid,L=mid+1;
                else R=mid-1;
            }
            printf("%d\n",query(rt[y2],1,mx,ans,mx,rt[y1-1],0)-(query(rt[y2],1,mx,ans,mx,rt[y1-1],1)-h)/ans);
        }
    }
}
int main()
{
    scanf("%d%d%d",&r,&c,&m);
    if(r==1) solve2::init(),solve2::solve();
    else solve1::init(),solve1::solve();
}
