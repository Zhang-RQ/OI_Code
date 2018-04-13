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
const int MAXM=1E5+5;
const int mid=105;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int n,col[110],cnt[4],siz[MAXN],blk,bl[MAXN];
bool f[110][211];
int lst[110][211],ops[110][211],b[110];
vector<int> ans1,ans2;
bool gg;
void dfs(int x,int c)
{
    col[x]=c;cnt[c]++;bl[x]=blk;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!col[v]) dfs(v,c^1);
        else if(col[v]==col[x]) {gg=1;return;}
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int j;
        b[i]=i;
        while(scanf("%d",&j),j) b[j]=i;
        for(int k=1;k<=n;k++) if(b[k]!=i) add(i,k),add(k,i);
    }
    for(int i=1;i<=n;i++)
        if(!col[i])
        {
            ++blk;cnt[3]=cnt[2]=0;
            dfs(i,2);
            siz[blk]=cnt[2]-cnt[3];
        }
    if(gg) puts("No solution");
    else
    {
        f[0][mid]=1;
        for(int i=1;i<=blk;i++)
        {
            for(int j=0;j<=210;j++)
            {
                if(!f[i-1][j]) continue;
                if(j+siz[i]>=0&&j+siz[i]<=210)
                {
                    f[i][j+siz[i]]|=f[i-1][j];
                    lst[i][j+siz[i]]=j;ops[i][j+siz[i]]=1;
                }
                if(j-siz[i]>=0&&j-siz[i]<=210)
                {
                    f[i][j-siz[i]]|=f[i-1][j];
                    lst[i][j-siz[i]]=j;ops[i][j-siz[i]]=2;
                }
            }
        }
        int l=mid,r=mid;
        for(l=mid;l>=0&&!f[blk][l];l--);
        for(r=mid;r<=210&&!f[blk][r];r++);
        int ls=abs(r-mid)<abs(l-mid)?r:l;
        for(int i=blk;i>=1;i--)
        {
            if(ops[i][ls]==1)
            {
                for(int j=1;j<=n;j++)
                    if(bl[j]==i)
                    {
                        if(col[j]==2) ans1.push_back(j);
                        else ans2.push_back(j);
                    }
            }
            else
            {
                for(int j=1;j<=n;j++)
                    if(bl[j]==i)
                    {
                        if(col[j]==3) ans1.push_back(j);
                        else ans2.push_back(j);
                    }
            }
            ls=lst[i][ls];
        }
        printf("%d ",ans2.size());
        for(int i=0;i<ans2.size();i++) printf("%d ",ans2[i]);
        puts("");
        printf("%d ",ans1.size());
        for(int i=0;i<ans1.size();i++) printf("%d ",ans1[i]);
        puts("");
    }
}
