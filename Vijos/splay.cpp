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
#define MAXN 500010
#define INF 2147483640
using namespace std;
typedef long long ll;
int fa[MAXN],son[MAXN][3],val[MAXN],siz[MAXN],tims[MAXN],root,cnt=0;
inline void rotate(int x,int w) //w=1 => left;w=2 => right
{
    int y=fa[x];
    siz[y]=siz[y]-siz[x]+siz[son[x][w]];
    siz[x]=siz[x]-siz[son[x][w]]+siz[y];
    son[y][3-w]=son[x][w];
    if(son[x][w]) fa[son[x][w]]=y;
    fa[x]=fa[y];
    if(fa[y])
    {
        if(son[fa[y]][1]==y) son[fa[y]][1]=x;
        else son[fa[y]][2]=x;
    }
    son[x][w]=y;
    fa[y]=x;
}
inline void splay(int x)
{
    int y;
    while(fa[x])
    {
        y=fa[x];
        if(!fa[y])
        {
            if(son[y][1]==x) rotate(x,2);
            else rotate(x,1);
        }
        else
        {
            if(son[fa[y]][1]==y)
            {
                if(son[y][1]==x)
                {
                    rotate(y,2);
                    rotate(x,2);
                }
                else
                {
                    rotate(x,1);
                    rotate(x,2);
                }
            }
            else
            {
                if(son[y][1]==x)
                {
                    rotate(x,2);
                    rotate(x,1);
                }
                else
                {
                    rotate(y,1);
                    rotate(x,1);
                }
            }
        }
    }
    root=x;
}
inline int search(int x,int value)
{
    while(val[x]!=value)
    {
        if(value<val[x])
        {
            if(!son[x][1]) break;
            x=son[x][1];
        }
        else if(value>val[x])
        {
            if(!son[x][2]) break;
            x=son[x][2];
        }
    }
    return x;
}
inline void insert(int value)
{
    bool flag=0;
    int tk;
    if(!cnt)
    {
        cnt=1;val[1]=value;
        siz[1]=1;tims[1]=1;
        fa[1]=0;root=1;
        return;
    }
    int k=search(root,value);
    if(val[k]==value)
    {
        tims[k]++;
        tk=k;
        flag=0;
    }
    else
    {
        cnt++;
        fa[cnt]=k;
        val[cnt]=value;
        siz[cnt]=1;
        tims[cnt]=1;
        if(value<val[k])
            son[k][1]=cnt;
        else
            son[k][2]=cnt;
        flag=1;
    }
    while(k)
    {
        siz[k]++;
        k=fa[k];
    }
    if(flag) splay(cnt);
    else splay(tk);
}
inline int extreme(int x,int w) //w=1,max;w=2,min
{
    int k;
    if(w==1) k=search(x,INF);
    else k=search(x,-INF);
    splay(k);
    return k;
}
inline int pred(int value)
{
    int k=search(root,value);
    splay(k);
    if(val[k]<value) return val[k];
    else
        return val[extreme(son[k][1],1)];
}

inline int succ(int value)
{
    int k=search(root,value);
    splay(k);
    if(val[k]>value) return val[k];
    else return val[extreme(son[k][2],2)];
}
inline void del(int value)
{
    int k=search(root,value);
    splay(k);
    if(val[k]!=value) return;
    if(tims[k]>1)
    {
        tims[k]--;
        siz[k]--;
    }
    else if(!son[k][1])
    {
        root=son[k][2];
        fa[son[k][2]]=0;
        son[k][2]=0;
        val[k]=siz[k]=tims[k]=0;
    }
    else
    {
        fa[son[k][1]]=0;
        extreme(son[k][1],1);
        son[root][2]=son[k][2];
        siz[root]+=siz[son[root][2]];
        if(son[root][2]) fa[son[root][2]]=root;
        son[k][1]=son[k][2]=0;
        val[k]=siz[k]=tims[k]=0;
    }
}
inline int findnum(int value)
{
    int k=search(root,value);
    if(val[k]!=value) return 0;
    splay(k);
    return siz[son[k][1]]+1;
}
inline int kth(int th)
{
    int i=root;
    while(!(th>=siz[son[i][1]]+1&&th<=siz[son[i][1]]+tims[i])&&(i!=0))
    {
        if(th>siz[son[i][1]]+tims[i])
        {
            th-=siz[son[i][1]]+tims[i];
            i=son[i][2];
        }
        else i=son[i][1];
    }
    splay(i);
    return val[i];
}
int main()
{
    int n,ops,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&ops,&x);
        switch(ops)
        {
            case 1: insert(x);break;
            case 2: del(x);break;
            case 3: printf("%d\n",findnum(x));break;
            case 4: printf("%d\n",kth(x));break;
            case 5: printf("%d\n",pred(x));break;
            case 6: printf("%d\n",succ(x));break;
        }
    }
}
