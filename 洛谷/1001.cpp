#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
typedef long long ll;
using namespace std;
ll f[30][30];
bool b[30][30];
int N,M,x,y;
int main()
{
    scanf("%d%d%d%d",&N,&M,&x,&y);
    b[x][y]=-1;
    if(x-2>=0&&y-1>=0) b[x-2][y-1]=1;
    if(x-2>=0) b[x-2][y+1]=1;
    if(x-1>=0&&y-2>=0) b[x-1][y-2]=1;
    if(x-1>=0) b[x-1][y+2]=1;
    if(y-1>=0) b[x+2][y-1]=1;
    b[x+2][y+1]=1;
    if(y-2>=0) b[x+1][y-2]=1;
    b[x+1][y+2]=1;
    if(!b[0][1])    f[0][1]=1;
    if(!b[1][0])    f[1][0]=1;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            if(j&&!b[i][j])   f[i][j]+=f[i][j-1];
            if(i&&!b[i][j])   f[i][j]+=f[i-1][j];
        }
    }
    printf("%lld\n",f[N][M]);
}
