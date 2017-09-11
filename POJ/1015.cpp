#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int D[210],P[210];
int sum[210],v[210];
int F[210][2000];//F[i][j]表示选了i个人sumD-sumP为j时最大的sumD+sumP -1表示不可能
int path[210][2000];//记录路径
const int mid=1000;

bool chose(int j,int k,int i)//方案j,k是否选过i
{
    while(path[j][k]!=i&&j>0)
    {
        k-=v[path[j][k]];
        --j;
    }
    if(!j) return false;
    else return true;
}
int main()
{
    int n,m;
    int cnt=0;
    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        memset(F,-1,sizeof(F));
        for(int i=1;i<=n;i++)    scanf("%d%d",&D[i],&P[i]),sum[i]=D[i]+P[i],v[i]=D[i]-P[i];
        F[0][mid]=0;
        for(int i=1;i<=m;i++)
        {
            for(int k=mid-n*20;k<=mid+20*n;k++)
            {
                if(F[i-1][k]>=0)
                {
                    for(int j=1;j<=n;j++)
                    {
                        if(F[i][k+v[j]]<F[i-1][k]+sum[j]&&!chose(i,k,j))
                        {
                            F[i][k+v[j]]=F[i-1][k]+sum[j];
                            path[i][k+v[j]]=j;
                        }
                    }
                }
            }
        }
        /*for(int i=1;i<=m;i++)
        {
            for(int k=mid-n*20;k<=mid+20*n;k++)
            {
                printf("%d : %d\n",k,path[i][k]);
            }
        }
        printf("\n\n\n\n\n\n\n");*/
        int i,ans;
        for(i=0;i<=n*20;i++)    if(F[m][mid-i]>=0||F[m][mid+i]>=0) break;
        if(F[m][mid-i]>F[m][mid+i]) i=-i;
        //printf("\n\n\n\n%d\n\n\n\n",mid+i);
        printf("Jury #%d\n",++cnt);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",(i+F[m][mid+i])/2,(-i+F[m][mid+i])/2);
        int chosen[25];
        int k=mid+i;
        for(int i=0;i<m;i++)
        {
                chosen[i]=path[m-i][k];
                k-=v[chosen[i]];
        }
        sort(chosen,chosen+m);
        for(int i=0;i<m;i++)
        {
                printf(" %d",chosen[i]);
        }
        printf("\n");
    }
}
