#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

const int MAXN=5E5+10;

int q,fa[MAXN],cnt;
double f[MAXN][62];

int main()
{
    scanf("%d",&q);cnt=1;
    for(int i=0;i<=60;i++)
        f[1][i]=1;
    for(int i=1,opt,x;i<=q;i++)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1)
        {
            int y=++cnt;fa[y]=x;
            double pre=1,pre1;
            for(int d=0;d<=60;d++)
                f[y][d]=1;
            for(int dep=0;dep<=60&&x;dep++,x=fa[x],y=fa[y])
            {
                pre1=f[x][dep];
                f[x][dep]=f[x][dep]/(pre+1)*(dep?(f[y][dep-1]+1):1);
                pre=pre1;
            }
        }
        else
        {
            double Ans=0;
            for(int i=1;i<=60;i++)
                Ans+=(f[x][i]-f[x][i-1])*i;
            printf("%.10lf\n",Ans);
        }
    }
}
