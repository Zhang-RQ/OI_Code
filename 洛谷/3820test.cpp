#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
const int Max=1001000;
int n,m,Q,d;
char ch;
int a[Max];
int f[Max];
bool flag[Max];
int s[Max];
int i,j;
int T,w;
int ans,sum;
int xx,yy;
int fa[Max];
int ff;
inline int getid(int x,int y)
{
    return (x-1)*m+y;
}
int read()
{
    char ch=getchar();
    int x=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x;
}
int gf(int x)
{
    if (fa[x]==x) return x;
    fa[x]=gf(fa[x]);
    return fa[x];
}
void dfs(int x,int y)
{
    int id=(x-1)*m+y;
    if (flag[id]||a[id]==0) return;
    flag[id]=1;
    f[id]=d;
    s[d]++;
    if (x>1) dfs(x-1,y);
    if (y>1) dfs(x,y-1);
    if (x<n) dfs(x+1,y);
    if (y<m) dfs(x,y+1);
}
void merge(int x,int y,int x1,int y1)
{
    int d1=(x-1)*m+y;
    int d2=(x1-1)*m+y1;
    int f1=gf(f[d1]);
    int f2=gf(f[d2]);
    if (a[d1]==0||a[d2]==0||f1==f2) return;
    s[f1]+=s[f2];
    s[f2]=0;
    fa[f2]=f1;
}
int main()
{
    n=read();
    m=read();
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            ch=getchar();
            while (ch!='.'&&ch!='*') ch=getchar();
            if (ch=='.') a[(i-1)*m+j]=1;
}

    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            if (a[(i-1)*m+j]==1&&!flag[(i-1)*m+j])
            {
                d++;
                dfs(i,j);
            }
        }
    for (i=1;i<=d;i++)
        fa[i]=i;
    Q=read();
    while (Q--)
    {
        printf("\n\n");
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<m;j++)
            {
                printf(" %d ",a[getid(i,j)]);
            }
            printf("\n");
        }
        printf("\n\n");
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                printf(" %d ",gf(f[getid(i,j)]));
            }
            printf("\n");
        }
        printf("\n\n");
        T=read();
        w=read();
        if (T==1)
        {
            ans=1;
            sum=0;
            for (i=1;i<=w;i++)
            {
                xx=read();
                yy=read();
                ff=gf(f[(xx-1)*m+yy]);
                if (a[(xx-1)*m+yy]==0) continue;
                if (s[ff]>sum)
                {
                    sum=s[ff];
                    ans=i;
                }
            }
            printf("%d\n",ans);
        } else
        {
            while (w--)
            {
                xx=read();
                yy=read();
                if (a[(xx-1)*m+yy]==1)
                {
                    a[(xx-1)*m+yy]=0;
                    ff=gf(f[(xx-1)*m+yy]);
                    s[ff]--;
                    f[(xx-1)*m+yy]=0;
                } else
                {
                    a[(xx-1)*m+yy]=1;
                    d++;
                    f[(xx-1)*m+yy]=d;
                    fa[d]=d;
                    s[d]++;
                    if (xx>1) merge(xx,yy,xx-1,yy);
                    if (yy>1) merge(xx,yy,xx,yy-1);
                    if (xx<n) merge(xx,yy,xx+1,yy);
                    if (yy<m) merge(xx,yy,xx,yy+1);
                }
            }
        }
    }
    return 0;
}
