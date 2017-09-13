#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
int pos[350];
int p,v;
int f[350][40];
int we(int l,int r)
{
    int ret=0;
    int sum=(l+r)>>1;
    for(int i=l;i<=r;i++)
    {
        ret+=abs(pos[i]-pos[sum]);
    }
    return ret;
}
int main()
{
    scanf("%d%d",&v,&p);
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=v;i++)   {scanf("%d",&pos[i]);}
    sort(pos+1,pos+1+v);
    for(int i=1;i<=v;i++)
    {
        for(int j=1;j<=p;j++)
        {
            int minn=0x3f3f3f3f;
            for(int k=0;k<i;k++)
            {
                minn=min(minn,f[k][j-1]+we(k+1,i));
            }
            f[i][j]=minn;
        }
    }
    printf("%d\n",f[v][p]);
}
