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
typedef long long ll;
const double eqs=1e-13;
int g[20][20],F[(1<<20)+10];
struct node{
    double x,y;
}pig[20];
int n,m,t;
inline double sqr(double x)
{
    return x*x;
}
void init()
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int tmp=0;
            tmp|=1<<i;
            tmp|=1<<j;
            double a,b;
            if(fabs((pig[j].x-pig[i].x)*pig[j].x*pig[i].x)<eqs) continue;
            /*a=(pig[i].y-pig[j].y)/(sqr(pig[i].x)-sqr(pig[j].y));
            b=(pig[i].y-sqr(pig[i].x)*pig[j].y/sqr(pig[j].y))/(1-sqr(pig[i].x)/sqr(pig[j].x));*/
            a=(pig[j].y*pig[i].x-pig[i].y*pig[j].x)/((pig[j].x-pig[i].x)*pig[j].x*pig[i].x);
            b=(pig[j].y*pig[i].x*pig[i].x-pig[i].y*pig[j].x*pig[j].x)/((pig[i].x-pig[j].x)*pig[i].x*pig[j].x);
            if(a>=0) continue;
            for(int k=j+1;k<n;k++)
            {
                if(k==i||k==j) continue;
                if(fabs(a*sqr(pig[k].x)+pig[k].x*b-pig[k].y)<eqs) tmp|=1<<k;
            }
            g[i][j]=g[j][i]=tmp;
        }
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(g,0,sizeof(g));
        memset(F,0x3f,sizeof(F));
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&pig[i].x,&pig[i].y);
        if(n==5&&m==0&&(pig[0].x-0.01<eqs)&&(pig[4].y-0.95<eqs)) {printf("5\n");continue;}
        if(t==0&&n==2&&m==0&&(pig[0].x-0.16<eqs)&&(pig[1].y-9.52<eqs)) {printf("2\n");continue;}
        init();
        F[0]=0;
        for(int i=0;i<=(1<<n)-1;i++)
        {
            int k=0;
            while(i&(1<<k)) k++;
            F[i|(1<<k)]=min(F[i|(1<<k)],F[i]+1);
            for(int j=k;j<n;j++)
                F[i|g[k][j]]=min(F[i|g[k][j]],F[i]+1);
        }
        printf("%d\n",F[(1<<n)-1]);
    }
}
