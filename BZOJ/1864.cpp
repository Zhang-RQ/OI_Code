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
char str[500010];
int son[500010][2];
int cnt=0;
int DPx[500010][3][3];//DP[i][j][k]表示第i个节点颜色为j时k色的子节点的最大个数
int DPn[500010][3][3];
int pos=0;
int build() {
    if(str[pos]==0) return 0;
    ++cnt;
    int cur=cnt;
    //int tmp = cnt;
    if(str[pos]=='0') {
        pos++;
    } else if(str[pos]=='1') {
        pos++;
        son[cur][0]=build();
    } else {
        pos++;
        son[cur][0]=build();
        son[cur][1]=build();
    }
    return cur;
}
void dfs(int x)
{
    int ls=son[x][0];
    int rs=son[x][1];
    if(ls)
    {
        if(rs)
        {
            dfs(ls);
            dfs(rs);
            DPx[x][0][0]=max(DPx[ls][1][0]+DPx[rs][2][0],DPx[ls][2][0]+DPx[rs][1][0])+1;
            DPx[x][0][1]=max(DPx[ls][1][1]+DPx[rs][2][1],DPx[ls][2][1]+DPx[rs][1][1]);
            DPx[x][0][2]=max(DPx[ls][1][2]+DPx[rs][2][2],DPx[ls][2][2]+DPx[rs][1][2]);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            DPx[x][1][0]=max(DPx[ls][0][0]+DPx[rs][2][0],DPx[ls][2][0]+DPx[rs][0][0]);
            DPx[x][1][1]=max(DPx[ls][0][1]+DPx[rs][2][1],DPx[ls][2][1]+DPx[rs][0][1])+1;
            DPx[x][1][2]=max(DPx[ls][0][2]+DPx[rs][2][2],DPx[ls][2][2]+DPx[rs][0][2]);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            DPx[x][2][0]=max(DPx[ls][1][0]+DPx[rs][0][0],DPx[ls][0][0]+DPx[rs][1][0]);
            DPx[x][2][1]=max(DPx[ls][1][1]+DPx[rs][0][1],DPx[ls][0][1]+DPx[rs][1][1]);
            DPx[x][2][2]=max(DPx[ls][1][2]+DPx[rs][0][2],DPx[ls][0][2]+DPx[rs][1][2])+1;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            DPn[x][0][0]=min(DPn[ls][1][0]+DPn[rs][2][0],DPn[ls][2][0]+DPn[rs][1][0])+1;
            DPn[x][0][1]=min(DPn[ls][1][1]+DPn[rs][2][1],DPn[ls][2][1]+DPn[rs][1][1]);
            DPn[x][0][2]=min(DPn[ls][1][2]+DPn[rs][2][2],DPn[ls][2][2]+DPn[rs][1][2]);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            DPn[x][1][0]=min(DPn[ls][0][0]+DPn[rs][2][0],DPn[ls][2][0]+DPn[rs][0][0]);
            DPn[x][1][1]=min(DPn[ls][0][1]+DPn[rs][2][1],DPn[ls][2][1]+DPn[rs][0][1])+1;
            DPn[x][1][2]=min(DPn[ls][0][2]+DPn[rs][2][2],DPn[ls][2][2]+DPn[rs][0][2]);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            DPn[x][2][0]=min(DPn[ls][1][0]+DPn[rs][0][0],DPn[ls][0][0]+DPn[rs][1][0]);
            DPn[x][2][1]=min(DPn[ls][1][1]+DPn[rs][0][1],DPn[ls][0][1]+DPn[rs][1][1]);
            DPn[x][2][2]=min(DPn[ls][1][2]+DPn[rs][0][2],DPn[ls][0][2]+DPn[rs][1][2])+1;
            return;
        }
        dfs(ls);
        DPx[x][0][0] = max(DPx[ls][1][0], DPx[ls][2][0]) + 1;
        DPx[x][0][1] = max(DPx[ls][1][1], DPx[ls][2][1]);
        DPx[x][0][2] = max(DPx[ls][1][2], DPx[ls][2][2]);
        DPx[x][1][0] = max(DPx[ls][0][0], DPx[ls][2][0]);
        DPx[x][1][1] = max(DPx[ls][0][1], DPx[ls][2][1]) + 1;
        DPx[x][1][2] = max(DPx[ls][0][2], DPx[ls][2][2]);
        DPx[x][2][0] = max(DPx[ls][0][0], DPx[ls][1][0]);
        DPx[x][2][1] = max(DPx[ls][0][1], DPx[ls][1][1]);
        DPx[x][2][2] = max(DPx[ls][0][2], DPx[ls][1][2]) + 1;

        DPn[x][0][0] = min(DPn[ls][1][0], DPn[ls][2][0]) + 1;
        DPn[x][0][1] = min(DPn[ls][1][1], DPn[ls][2][1]);
        DPn[x][0][2] = min(DPn[ls][1][2], DPn[ls][2][2]);
        DPn[x][1][0] = min(DPn[ls][0][0], DPn[ls][2][0]);
        DPn[x][1][1] = min(DPn[ls][0][1], DPn[ls][2][1]) + 1;
        DPn[x][1][2] = min(DPn[ls][0][2], DPn[ls][2][2]);
        DPn[x][2][0] = min(DPn[ls][0][0], DPn[ls][1][0]);
        DPn[x][2][1] = min(DPn[ls][0][1], DPn[ls][1][1]);
        DPn[x][2][2] = min(DPn[ls][0][2], DPn[ls][1][2]) + 1;
        return;
    }
    DPx[x][0][0]=DPx[x][1][1]=DPx[x][2][2]=1;
    DPn[x][0][0]=DPn[x][1][1]=DPn[x][2][2]=1;
    return;
}
int main()
{
    scanf("%s",str);
    build();
    dfs(1);
    int ansx=max(max(DPx[1][0][0],DPx[1][0][1]),DPx[1][0][2]);
    int ansn=min(min(DPn[1][0][0],DPn[1][0][1]),DPn[1][0][2]);
    printf("%d %d\n",ansx,ansn);
}
