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
const int s0=170;
char st[25];
ll f[25][1005][340][3];
int k,len;
void init()
{
    scanf("%s %d",st+1,&k);
    len=strlen(st+1);
    reverse(st+1,st+1+len);
    for(int i=1;i<=len;i++) st[i]-='0';
    memset(f,-1,sizeof f);len+=3;
}
ll dfs(int x,int r,int s,int lim)  //s=s-t
{
    if(x>len) return r==0&&s==s0&&lim<=1;
    if(~f[x][r][s][lim]) return f[x][r][s][lim];
    ll ret=0;
    for(int i=0;i<=9;i++)
        ret+=dfs(x+1,(i*k+r)/10,s+i-(i*k+r)%10,i==st[x]?lim:(i>st[x])<<1);
    return f[x][r][s][lim]=ret;
}
int main()
{
    init();
    printf("%lld\n",dfs(1,0,s0,1)-1);
}
