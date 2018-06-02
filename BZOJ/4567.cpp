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
const int MAXN=510010;
char str[MAXN];
int son[MAXN][26],siz[MAXN],ed[MAXN],cnt,n,idx[MAXN],tot;
vector<int> g[MAXN];
ll ans=0;
void insert(int id)
{
    int x=0;
    for(int i=1;str[i];i++)
    {
        siz[x]++;
        if(!son[x][str[i]-'a']) son[x][str[i]-'a']=++cnt;
        x=son[x][str[i]-'a'];
    }
    siz[x]++;ed[x]=id;
}
void init()
{
    queue<pair<int,int> > q;
    q.push(make_pair(0,0));
    while(!q.empty())
    {
        pair<int,int> t=q.front();q.pop();
        if(ed[t.first]&&ed[t.first]!=t.second)
            g[t.second].push_back(ed[t.first]),
            t.second=ed[t.first];
        for(int i=0;i<26;i++)
            if(son[t.first][i])
                q.push(make_pair(son[t.first][i],t.second));
    }
}
void get_size(int x)
{
    siz[x]=1;
    for(auto v:g[x])
        get_size(v),siz[x]+=siz[v];
}
void dfs(int x)
{
    sort(g[x].begin(),g[x].end(),[](int a,int b)->bool{return siz[a]<siz[b];});
    for(auto v:g[x])
        idx[v]=++tot,ans+=idx[v]-idx[x],dfs(v);
}
int main()
{
    scanf("%d",&n);
    for(int i=1,len;i<=n;i++)
    {
        scanf("%s",str+1);
        len=strlen(str+1);
        reverse(str+1,str+1+len);
        insert(i);
    }
    init();get_size(0);dfs(0);
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}