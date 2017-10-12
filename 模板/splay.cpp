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
#define MAXN 100010
#define INF 2147483640
using namespace std;
typedef long long ll;
int fa[MAXN],son[MAXN][3],val[MAXN],tims[MAXN],siz[MAXN],cnt=0;
int root;
inline void rotate(int x,int w) //w=1左旋 w=2右旋
{
    int y=fa[x];
    siz[y]=siz[y]-siz[x]+siz[son[x][w]];
    siz[x]=siz[x]-siz[son[x][w]]+siz[y];
    son[y][3-w]=son[x][w];
    if(son[x][w]) fa[son[x][w]]=y;
    fa[x]=fa[y];
    if(fa[y])
    {
        if(son[fa[y]][1]==y)
            son[fa[y]][1]=x;
        else son[fa[y]][2]=x;
    }
    fa[y]=x;
    son[x][w]=y;
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
        else if(son[fa[y]][1]==y)
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
    root=x;
}
inline int search(int x,int value)
{
    while(value!=val[x])
    {
        if(val[x]==value) return x;
        if(value<val[x])
        {
            if(!son[x][1]) break;
            x=son[x][1];
        }
        else
        {
            if(!son[x][2]) break;
            x=son[x][2];
        }
    }
    return x;
}
inline void insert(int value)
{
    int k,tk;
    bool flag;
    if(!cnt)
    {
        cnt=1;root=1;
        val[1]=value;
        tims[1]=1;
        siz[1]=1;
        return;
    }
    k=search(root,value);
    if(val[k]==value) {++tims[k];tk=k;flag=true;}
    else
    {
        ++cnt;
        val[cnt]=value;
        tims[cnt]=1;
        siz[cnt]=1;
        fa[cnt]=k;
        if(val[cnt]<val[k]) son[k][1]=cnt;
        else son[k][2]=cnt;
        flag=false;
    }
    while(k)
    {
        siz[k]++;
        k=fa[k];
    }
    if(flag) splay(tk);
    else splay(cnt);
}
inline int extreme(int x,int w) //w=1最小,w=2最大
{
    int k;
    if(w==1) k=search(x,-INF);
    else k=search(x,INF);
    splay(k);
    return val[k];
}
inline void del(int value)
{
    int k;
    k=search(root,value);
    splay(k);
    if(val[k]!=value) return;
    else
    {
        if(tims[k]>1)
        {
            tims[k]--;
            siz[k]--;
        }
        else if(!son[k][1])
        {
            int y=son[k][2];
            fa[y]=0;
            root=y;
            son[k][2]=0;
            val[k]=0;siz[k]=0;
            tims[k]=0;
        }
        else
        {
            fa[son[k][1]]=0;
            extreme(son[k][1],2);
            siz[root]+=siz[son[k][2]];
            son[root][2]=son[k][2];
            if(son[root][2]!=0) fa[son[root][2]]=root;
            val[k]=0;siz[k]=0;tims[k]=0;son[k][1]=son[k][2]=0;
        }
    }
}
inline int pred(int value)
{
    int k=search(root,value);
    splay(k);
    if(val[k]<value) return val[k];
    else
        return extreme(son[k][1],2);
}
inline int succ(int value)
{
    int k=search(root,value);
    splay(k);
    if(val[k]>value) return val[k];
    else
        return extreme(son[k][2],1);
}
inline int findnum(int value)
{
    int k=search(root,value);
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
    return i;
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
            case 4: printf("%d\n",val[kth(x)]);break;
            case 5: printf("%d\n",pred(x));break;
            case 6: printf("%d\n",succ(x));break;
        }
    }
}
