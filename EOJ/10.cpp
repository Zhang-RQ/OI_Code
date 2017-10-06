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
using namespace std;
typedef long long ll;

bitset<1010> bs[1010];

int main()
{
    int n,m;
    int a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        bs[a][b]=1;
    }
    for(int k=1;k<=n;++k)
    {
       for(int i=1;i<=n;++i) 
       {
           if(bs[i][k])
           {
               bs[i]|=bs[k];
           }
       }
   }
    int ans=0;
    for(int i=1;i<=n;++i)
    {
     ++ans;
     for(int j=1;j<=n;++j)
     {
         if(i!=j&&!(bs[i][j]||bs[j][i]))
         {
             --ans;
             break;
         }
     }
 }
    printf("%d\n",ans);
}
