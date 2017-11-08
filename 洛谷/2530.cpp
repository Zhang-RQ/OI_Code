#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
#define cnta(l,r) suma[r]-suma[l-1]
#define cntb(l,r) sumb[r]-sumb[l-1]
#define cntc(l,r) sumc[r]-sumc[l-1]
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int f[110][15][15][15];
int suma[110],sumb[110],sumc[110];
int n,ans;
char str[5];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        suma[i]=suma[i-1];
        sumb[i]=sumb[i-1];
        sumc[i]=sumc[i-1];
        switch(str[1])
        {
            case 'A': ++suma[i];break;
            case 'B': ++sumb[i];break;
            case 'C': ++sumc[i];break;
        }
    }
    if(n<=10)
    {
        ans=3;
        if(!suma[n]) --ans;
        if(!sumb[n]) --ans;
        if(!sumc[n]) --ans;
        printf("%d\n",ans);
        return 0;
    }
    memset(f,0x3f,sizeof(f));
    f[10][suma[10]][sumb[10]][sumc[10]]=0;
    for(int i=10;i<=n;i++)
        for(int a=0;a<=10;a++)
            for(int b=0;a+b<=10;b++)
                for(int c=0;a+b+c<=10;c++)
                {
                    if(f[i][a][b][c]>=10000000)
                        continue;
                    if(i==n)
                    {
                        ans=3;
                        if(!a) ans--;
                        if(!b) ans--;
                        if(!c) ans--;
                        f[n][0][0][0]=min(f[n][0][0][0],f[n][a][b][c]+ans);
                        continue;
                    }
                    if(a)
                    {
                        int r=min(i+a,n);
                        f[r][cnta(i+1,r)][b+cntb(i+1,r)][c+cntc(i+1,r)]=min(f[r][cnta(i+1,r)][b+cntb(i+1,r)][c+cntc(i+1,r)],f[i][a][b][c]+1);
                    }
                    if(b)
                    {
                        int r=min(i+b,n);
                        f[r][a+cnta(i+1,r)][cntb(i+1,r)][c+cntc(i+1,r)]=min(f[r][a+cnta(i+1,r)][cntb(i+1,r)][c+cntc(i+1,r)],f[i][a][b][c]+1);
                    }
                    if(c)
                    {
                        int r=min(i+c,n);
                        f[r][a+cnta(i+1,r)][b+cntb(i+1,r)][cntc(i+1,r)]=min(f[r][a+cnta(i+1,r)][b+cntb(i+1,r)][cntc(i+1,r)],f[i][a][b][c]+1);
                    }
                }
    printf("%d\n",f[n][0][0][0]);
}
