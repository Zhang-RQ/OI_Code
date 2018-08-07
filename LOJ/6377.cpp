#include<bits/stdc++.h>

using namespace std;

const int MAXN=2E5+10;

char s[MAXN];
int sg[MAXN];
vector<int> g[MAXN];
int son[MAXN][26],par[MAXN],mx[MAXN],lst=1,cnt=1,rt=1,n,du[MAXN];
bool vis[MAXN][27];
queue<int> q;

void insert(int x)
{
    x-='a';
    int np=++cnt,p=lst;
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
            memcpy(son[nq],son[q],sizeof son[q]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p]; 
        }
    }
    lst=np;
}

void init()
{
    memset(son,0,sizeof son);
    memset(par,0,sizeof par);
    memset(mx,0,sizeof mx);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=cnt;i++) g[i].clear();
    rt=lst=cnt=1;
}

bool solve()
{
    init();
    if(!(~scanf("%s",s+1))) return 0;
    for(int i=1;s[i];i++) insert(s[i]);
    for(int i=1;i<=cnt;i++)
        for(int j=0;j<26;j++)
            if(son[i][j])
                g[son[i][j]].push_back(i),++du[i];
    for(int i=1;i<=cnt;i++)
        if(!du[i]) q.push(i),sg[i]=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=0;i<=26;i++)
            if(!vis[x][i])
                {sg[x]=i;break;}
        for(auto v:g[x])
        {
            vis[v][sg[x]]=1;
            if(!(--du[v]))
                q.push(v);
        }
    }
    scanf("%d",&n);
    int ans=0;
    for(int i=1,x;i<=n;i++)
    {
        scanf("%s",s+1);
        x=rt;
        for(int j=1;s[j];j++)
            x=son[x][s[j]-'a'];
        ans^=sg[x];
    }
    puts(ans?"Alice":"Bob");
    return 1;
}

int main() {while(solve());}
