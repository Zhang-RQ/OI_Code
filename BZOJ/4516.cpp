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
const int MAXN=200010;
map<int,int> son[MAXN];
int par[MAXN],mx[MAXN],rt=1,lst=1,cnt=1;
int n,x;
ll ans;
void insert(int x)
{
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            son[nq]=son[q];
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    ans+=mx[np]-mx[par[np]];
    lst=np;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        insert(x);
        printf("%lld\n",ans);
    }
}
