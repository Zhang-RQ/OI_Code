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
int st[100100][20];
int lg2[100100];
int n,m,l,r,len;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
    for(int i=1;i<=n;i++) scanf("%d",&st[i][0]);
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
        len=lg2[r-l+1];
        printf("%d\n",max(st[l][len],st[r-(1<<len)+1][len]));
    }
}
