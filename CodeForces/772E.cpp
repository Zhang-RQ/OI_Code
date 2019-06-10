#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;

char str[233];
int n,tot;
int son[MAXN][2],fa[MAXN],siz[MAXN],Ll[MAXN],Rl[MAXN],vis[MAXN],rt,mxrt;

char Query(int x,int y,int z)
{
    printf("%d %d %d\n",x,y,z);fflush(stdout);
    scanf("%s",str+1);
    return str[1];
}

void get_rt(int x,int lst,int sz)
{
    int mx=0;
    siz[x]=x<=n;
    if(!vis[fa[x]]&&fa[x]!=lst)
    {
        get_rt(fa[x],x,sz);
        siz[x]+=siz[fa[x]];
        mx=max(mx,siz[fa[x]]);
    }
    if(!vis[son[x][0]]&&son[x][0]!=lst)
    {
        get_rt(son[x][0],x,sz);
        siz[x]+=siz[son[x][0]];
        mx=max(mx,siz[son[x][0]]);
    }
    if(!vis[son[x][1]]&&son[x][1]!=lst)
    {
        get_rt(son[x][1],x,sz);
        siz[x]+=siz[son[x][1]];
        mx=max(mx,siz[son[x][1]]);
    }
    mx=max(mx,sz-siz[x]);
    if(x>n&&mx<mxrt)
        mxrt=mx,rt=x;
}

bool rson(int x){return son[fa[x]][1]==x;}

void solve(int x,int nx)
{
    vis[x]=1;
    char t=Query(Ll[x],Rl[x],nx);
    if(t=='X')//not in subtree x
    {
        if(!fa[x]||vis[fa[x]]) //newnode
        {
            int rfa=fa[x],rsx=rson(x);
            ++tot;
            fa[x]=tot;
            son[tot][0]=x;
            fa[nx]=tot;
            son[tot][1]=nx;
            Ll[tot]=Ll[x];
            Rl[tot]=nx;
            if(rfa)
                son[rfa][rsx]=tot;
            fa[tot]=rfa;
            return;
        }
        mxrt=1<<30;
        get_rt(fa[x],x,siz[fa[x]]);
        solve(rt,nx);
    }
    else if(t=='Y')//in Right
    {
        if(son[x][1]<=n||vis[son[x][1]])//newnode
        {
            ++tot;
            fa[tot]=x;
            son[tot][1]=son[x][1];
            fa[son[tot][1]]=tot;
            son[tot][0]=nx;
            fa[son[tot][0]]=tot;
            Ll[tot]=Ll[son[tot][0]];
            Rl[tot]=Rl[son[tot][1]];
            son[x][1]=tot;
            return;
        }
        mxrt=1<<30;
        get_rt(son[x][1],x,siz[son[x][1]]);
        solve(rt,nx);
    }
    else if(t=='Z')//in Left
    {
        if(son[x][0]<=n||vis[son[x][0]])//newnode
        {
            ++tot;
            fa[tot]=x;
            son[tot][0]=son[x][0];
            fa[son[tot][0]]=tot;
            son[tot][1]=nx;
            fa[son[tot][1]]=tot;
            Ll[tot]=Ll[son[tot][0]];
            Rl[tot]=Rl[son[tot][1]];
            son[x][0]=tot;
            return;
        }
        mxrt=1<<30;
        get_rt(son[x][0],x,siz[son[x][0]]);
        solve(rt,nx);
    }
}

void insert(int x)
{
    memset(vis,0,sizeof vis);
    vis[0]=1;
    mxrt=1<<30;
    get_rt(x-1,0,x-1);
    solve(rt,x);
}

int main()
{
    scanf("%d",&n);
    tot=n+1;
    fa[1]=fa[2]=tot;
    son[tot][0]=1,son[tot][1]=2;
    Ll[tot]=1;Rl[tot]=2;
    for(int i=1;i<=n;i++)
        Ll[i]=Rl[i]=i;
    for(int i=3;i<=n;i++)
        insert(i);
    puts("-1");
    for(int i=1;i<=tot;i++)
        printf("%d%c",fa[i]?fa[i]:-1,"\n "[i!=tot]);
}
