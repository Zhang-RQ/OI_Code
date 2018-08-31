#include<bits/stdc++.h>

using namespace std;

const int MAXN=5E5+10;

typedef long long ll;

#define X(i) a[i]
#define Y(i) (s[i]-a[i]*(i))

const double EPS=1E-8;

int n,q,top,stk[MAXN];
ll a[MAXN],s[MAXN],ans[MAXN];

struct node{
    int x,y,id;
    bool operator < (const node &rhs) const {return y<rhs.y;}
}Q[MAXN];

double slope(int l,int r){return 1.0*(Y(r)-Y(l))/(X(r)-X(l));}

int get(int i)
{
    int L=1,R=top,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(stk[mid]>=i) R=mid-1,ans=mid;
        else L=mid+1;
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)  scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
    scanf("%d",&q);
    for(int i=1;i<=q;i++) scanf("%d%d",&Q[i].x,&Q[i].y),Q[i].id=i;
    sort(Q+1,Q+1+q);
    for(int i=1,j=1;i<=n;i++)
    {
        while(top&&a[stk[top]]>=a[i]) --top;
        while(top>1&&slope(stk[top],i)>=slope(stk[top-1],i)) --top;
        stk[++top]=i;
        while(Q[j].y==i&&j<=q)
        {
            int L=get(Q[j].y-Q[j].x),R=top-1,Ans=0;
            while(L<=R)
            {
                int mid=(L+R)>>1;
                if(slope(stk[mid],stk[mid+1])<=(Q[j].x-Q[j].y)) R=mid-1,Ans=mid;
                else L=mid+1;
            }
            if(!Ans) Ans=(Q[j].x-Q[j].y)>0?top:get(Q[j].y-Q[j].x);
            L=stk[Ans],R=Q[j].y;
            ans[Q[j].id]=s[R]-s[L]+(Q[j].x-(R-L))*a[L];
            ++j;
        }
    }
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}