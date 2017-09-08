#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#define F(i,j,k) e
using namespace std;
struct node{
    int P,D;
}peo[210];
bool cmp(node &a,node &b)
{
    return a.P+a.D>b.P+b.D;
}
bool F[210][30][900];//F[i][j][k]表示前i个人选j个sum(D)-Sum(P)=k是否有可能 450=0
bool choose[210][30];
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        memset(F,0,sizeof(0));
        F[0][0][450]=1;
        for(int i=1;i<=n;i++)    scanf("%d%d",&peo[i].D,&peo[i].P);
        sort(peo+1,peo+1+n,cmp);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                for(int k=50;k<=850;j++)
                {

                }
            }
        }
    }
}
