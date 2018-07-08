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
 
const int MAXN=1E5+10;
 
int n,val[MAXN],S;
int cnt[20],ans,f[1<<16];
int stk[20],top,bin[20];
 
int main()
{
    scanf("%d",&n);memset(f,0x3f,sizeof f);
    bin[0]=1;
    for(int i=1;i<=15;i++) bin[i]=bin[i-1]<<1;
    for(int i=1,u,v,w;i<n;i++)
        scanf("%d%d%d",&u,&v,&w),++u,++v,val[u]^=w,val[v]^=w;
    for(int i=1;i<=n;i++) cnt[val[i]]++;
    for(int i=1;i<=15;i++) ans+=cnt[i]>>1,S|=(cnt[i]&1)<<i;
    f[0]=0;
    for(int l=1;l<=15;l++)
        for(int s=0;s<(1<<16);s++)
            if(__builtin_popcount(s)==l&&(s&1)==0)
                {
                    top=0;
                    for(int i=1;i<16;i++) if((s>>i)&1) stk[++top]=i;
                    for(int i=1;i<=top;i++)
                        for(int j=i+1;j<=top;j++)
                            f[s]=min(f[s],f[s^bin[stk[i]]^bin[stk[j]]^bin[stk[i]^stk[j]]]+1+((s>>(stk[i]^stk[j]))&1));
                }
    printf("%d\n",f[S]+ans);
    #ifdef LOCAL
        system("pause");
    #endif
}