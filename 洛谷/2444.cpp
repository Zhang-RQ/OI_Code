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
typedef unsigned long long ull;
const int MAXN=30000<<1;
int son[MAXN][2];
int stp[MAXN],fail[MAXN];
int tot=0;
void insert(char *s)
{
    int x=0;
    for(int i=1;s[i];i++)
    {
        if(!son[x][s[i]-'0'])
            son[x][s[i]-'0']=++tot;
        x=son[x][s[i]-'0'];
    }
    stp[x]=1;
}
void build_trie()
{
    queue<int> q;
    //printf("son[0][0]=%d,son[0][1]=%d\n",son[0][0],son[0][1]);
    for(int i=0;i<2;i++)
        if(son[0][i])
            q.push(son[0][i]),
            fail[son[0][1]]=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        //printf("x=%d\n",x);
        for(int i=0;i<2;i++)
            if(son[x][i])
                stp[son[x][i]]|=stp[son[fail[x]][i]],
                q.push(son[x][i]),
                fail[son[x][i]]=son[fail[x]][i];
            else son[x][i]=son[fail[x]][i];
    }
}
bool vis[MAXN],inpath[MAXN];
int ans=-1;
void dfs(int x)
{
    if(ans==1||stp[x]||vis[x]) return;
    //printf("%d\n",x);
    vis[x]=1;
    inpath[x]=1;
    for(int i=0;i<2;i++)
    {
        if(son[x][i]&&!stp[son[x][i]])
            if(inpath[son[x][i]])
                {ans=1;return;}
            else dfs(son[x][i]);
        else;
    }
    inpath[x]=0;
}
char str[400010];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str+1),
        insert(str);
    build_trie();
    dfs(0);
    if(ans==1) puts("TAK");
    else puts("NIE");
}
