#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=105;
const int maxe=105*105;
struct edge
{
       int x,y,next;
}e[maxe];
int g[maxn],dfn[maxn],low[maxn],v[maxn],f[maxn],s[maxn],b[maxn],h[maxn];
int n,tot=0,cnt=0,ans=0,times=0,t=0,ans2;

void ins(int x,int y)
{
     e[++tot].x=x;e[tot].y=y;
     e[tot].next=h[x];h[x]=tot;
}

void tarjan(int x)
{
     int y,i;
     times++;t++;
     dfn[x]=low[x]=times;
     v[x]=1;s[t]=x;
     for (i=h[x];i;i=e[i].next)
     {
         y=e[i].y;
         if (v[y]==0)
         {
            tarjan(y);
            low[x]=min(low[x],low[y]);
         }
         if (v[y]==1)
            low[x]=min(low[x],dfn[y]);
     }
     if (dfn[x]==low[x])
     {
        cnt++;
        do
        {
              y=s[t--];
              b[y]=cnt;v[y]=2;
              //printf("%d\n",b[y]);
        }while (y!=x);
     }
}

int main()
{
    int i,j;
    cin >> n;
    for (i=1;i<=n;i++)
    {
        cin >> j;
        while (j)
        {
              ins(i,j);
              cin >> j;
        }
    }
    for (i=1;i<=n;i++)
        if (v[i]==0)
           tarjan(i);
    if (cnt==1)
    {
             cout << 1 << endl << 0 << endl;
             return 0;
    }

    for (i=1;i<=tot;i++)
        if (b[e[i].x]!=b[e[i].y])
        {
           f[b[e[i].x]]++;
           g[b[e[i].y]]++;
        }
    for(i=1;i<=cnt;i++)
        {
            printf("%d %d\n",g[i],f[i]);
        }
    ans=0;
    for (i=1;i<=cnt;i++)
        if (g[i]==0) ans++;
    cout << ans << endl;
    ans2=0;
    for (i=1;i<=cnt;i++)
        if (f[i]==0) ans2++;
    cout << max(ans,ans2)<< endl;
    //cout<<cnt<<endl;
}
