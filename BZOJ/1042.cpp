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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
ll f[100100],ans=0;
int s,tot,c1,c2,c3,c4,d1,d2,d3,d4;
int main()
{
    scanf("%d%d%d%d%d",&c1,&c2,&c3,&c4,&tot);
    f[0]=1;
    for(int i=c1;i<=100000;i++)
        f[i]+=f[i-c1];
    for(int i=c2;i<=100000;i++)
        f[i]+=f[i-c2];
    for(int i=c3;i<=100000;i++)
        f[i]+=f[i-c3];
    for(int i=c4;i<=100000;i++)
        f[i]+=f[i-c4];
    while(tot--)
    {
        scanf("%d%d%d%d%d",&d1,&d2,&d3,&d4,&s);//0000 0001 0010 0100 1000
        ans=f[s]-((s>=c1*(d1+1))?f[s-c1*(d1+1)]:0)-((s>=c2*(d2+1))?f[s-c2*(d2+1)]:0)-((s>=c3*(d3+1))?f[s-c3*(d3+1)]:0)-((s>=c4*(d4+1))?f[s-c4*(d4+1)]:0);
        ans+=((s>=c1*(d1+1)+c2*(d2+1))?f[s-c1*(d1+1)-c2*(d2+1)]:0)+((s>=c1*(d1+1)+c3*(d3+1))?f[s-c1*(d1+1)-c3*(d3+1)]:0);//0011 0101
        ans+=((s>=c1*(d1+1)+c4*(d4+1))?f[s-c1*(d1+1)-c4*(d4+1)]:0)+((s>=c2*(d2+1)+c3*(d3+1))?f[s-c2*(d2+1)-c3*(d3+1)]:0);//1010 0110
        ans+=((s>=c2*(d2+1)+c4*(d4+1))?f[s-c2*(d2+1)-c4*(d4+1)]:0)+((s>=c3*(d3+1)+c4*(d4+1))?f[s-c3*(d3+1)-c4*(d4+1)]:0);
        ans-=(s>=c1*(d1+1)+c2*(d2+1)+c3*(d3+1))?f[s-c1*(d1+1)-c2*(d2+1)-c3*(d3+1)]:0;
        ans-=(s>=c1*(d1+1)+c2*(d2+1)+c4*(d4+1))?f[s-c1*(d1+1)-c2*(d2+1)-c4*(d4+1)]:0;
        ans-=(s>=c1*(d1+1)+c3*(d3+1)+c4*(d4+1))?f[s-c1*(d1+1)-c3*(d3+1)-c4*(d4+1)]:0;
        ans-=(s>=c2*(d2+1)+c3*(d3+1)+c4*(d4+1))?f[s-c2*(d2+1)-c3*(d3+1)-c4*(d4+1)]:0;
        ans+=(s>=c1*(d1+1)+c2*(d2+1)+c3*(d3+1)+c4*(d4+1))?f[s-c1*(d1+1)-c2*(d2+1)-c3*(d3+1)-c4*(d4+1)]:0;
        printf("%lld\n",ans);
    }
}
