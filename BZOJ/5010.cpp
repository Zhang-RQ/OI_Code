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
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int P=1E9+7;
const int MAXN=30;
const int MAXM=2050;
int x[MAXN][2],y[MAXN][2],lim[MAXN];
int xx[45],yy[45],cntx,cnty;
int blklim[MAXM],blkcnt,blkS[MAXM],blkfil[MAXM];
int T,n,h,w,m,ful;
ll f[MAXM][MAXM];
bool in(int _x,int _y,int i)
{
    return x[i][0]<=_x&&_x<=x[i][1]&&y[i][0]<=_y&&_y<=y[i][1];
}
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&h,&w,&m,&n);
        memset(f,0,sizeof f);
        memset(blkfil,0,sizeof blkfil);
        cntx=cnty=0;ful=(1<<n);blkcnt=0;
        xx[++cntx]=0;yy[++cnty]=0;
        xx[++cntx]=h;yy[++cnty]=w;
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d%d",&x[i][0],&y[i][0],&x[i][1],&y[i][1],&lim[i]),
            xx[++cntx]=x[i][0]-1,yy[++cnty]=y[i][0]-1,xx[++cntx]=x[i][1],yy[++cnty]=y[i][1];
        sort(xx+1,xx+1+cntx);sort(yy+1,yy+1+cnty);
        cntx=unique(xx+1,xx+1+cntx)-xx-1;
        cnty=unique(yy+1,yy+1+cnty)-yy-1;
        for(int i=2;i<=cntx;i++)
            for(int j=2;j<=cnty;j++)
            {
                ++blkcnt;
                blklim[blkcnt]=m;
                blkS[blkcnt]=(xx[i]-xx[i-1])*(yy[j]-yy[j-1]);
                for(int k=1;k<=n;k++)
                    if(in(xx[i],yy[j],k)) blklim[blkcnt]=min(blklim[blkcnt],lim[k]);
                for(int k=1;k<=n;k++)
                    if(in(xx[i],yy[j],k)&&blklim[blkcnt]==lim[k])
                        blkfil[blkcnt]|=1<<(k-1);
            }
        f[0][0]=1;
        // for(int i=1;i<=blkcnt;i++) printf("%d %d %d\n",blkS[i],blklim[i],blkfil[i]);
        for(int i=1;i<=blkcnt;i++)
        {
            int blkful=blkfil[i];
            ll nchsn=ksm(blklim[i]-1,blkS[i]);
            ll chsn=(ksm(blklim[i],blkS[i])-nchsn+P)%P;
            assert(chsn>=0);assert(nchsn>=0);
            for(int s=0;s<ful;s++)
            {
                (f[i][s]+=f[i-1][s]*nchsn%P)%=P;
                (f[i][s|blkful]+=f[i-1][s]*chsn%P)%=P;
            }
        }
        cout<<f[blkcnt][ful-1]<<endl;
    }
}
