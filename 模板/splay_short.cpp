#include<cstdio>
using namespace std;
#define pushup(x) siz[x]=siz[son[x][0]]+siz[son[x][1]]+tims[x]
const int INF=1<<30;
const int MAXN=1000010;
int siz[MAXN],tims[MAXN],son[MAXN][2],val[MAXN],fa[MAXN];
int root,cnt;
void rotate(int x)
{
    int fx=fa[x],ffx=fa[fx];
    int d=(son[fx][1]==x); //0 right,1 left
    son[fx][d]=son[x][d^1];son[x][d^1]=fx;
    fa[x]=ffx;fa[fx]=x;fa[son[fx][d]]=fx;
    if(ffx) son[ffx][son[ffx][1]==fx]=x;
    pushup(fx);pushup(x);
}
void splay(int x,int pos=0)//WAAA
{
    if(fa[x]==pos) return;
    for(int fx;(fx=fa[x])!=pos;rotate(x))
        if(fa[fx]!=pos)
            rotate((son[fx][0]==x)==(son[fa[fx]][0]==fx)?fx:x);
    if(!pos) root=x;
    printf("root:%d\n",root);
    for(int i=1;i<=cnt;i++)
        printf("%d:val:%d,fa:%d,siz:%d,son[0]:%d,son[1]:%d\n",i,val[i],fa[i],siz[i],son[i][0],son[i][1]);
}
int search(int vl,int x=root)
{
    if(val[x]==vl) return x;
    int tmp=son[x][vl>val[x]];
    if(!tmp) return x;
    while(vl!=val[tmp]&&son[tmp][vl>val[tmp]])
        printf("%d,%d,%d\n",tmp,vl,val[tmp]),tmp=son[tmp][vl>val[tmp]];
    printf("return:%d\n",tmp);
    return tmp;
}
int insert(int &x,int vl,int _fa)
{
    if(!x)
    {
        val[x=++cnt]=vl;
        siz[cnt]=tims[cnt]=1;
        fa[cnt]=_fa;
        return x;
    }
    if(vl==val[x])
    {
        tims[x]++;siz[x]++;
        return x;
    }
    else
    {
        int ret=insert(son[x][vl>val[x]],vl,x);
        pushup(x);
        return ret;
    }
}
void ins(int vl)
{
    splay(insert(root,vl,0));
}
void del(int vl)
{
    int x=search(vl);
    //printf("%d\n",x);
    if(val[x]!=vl) return;
    if(tims[x]>1) {--tims[x];--siz[x];return;}
    splay(x);
    if(!son[x][0]&&!son[x][1]) {root=0;return;}
    if(!son[x][0])
    {
        int y=son[x][1];
        root=y;fa[y]=0;
        val[x]=siz[x]=tims[x]=son[x][0]=son[x][1]=0;
    }
    else
    {
        int y=search(INF,son[x][0]);
        fa[y]=0;root=y;
        splay(y);
        fa[son[x][1]]=y;
        son[y][1]=son[x][1];
        val[x]=siz[x]=tims[x]=son[x][0]=son[x][1]=0;
        pushup(y);
    }
    printf("root:%d\n",root);
    for(int i=1;i<=cnt;i++)
        printf("%d:val:%d,fa:%d,siz:%d,son[0]:%d,son[1]:%d\n",i,val[i],fa[i],siz[i],son[i][0],son[i][1]);
}
int query_rank(int vl)
{
    int x=search(vl);
    printf("%d,%d\n",vl,val[x]);
    splay(x);
    return siz[son[x][0]]+1;
}
int find_by_rank(int rk,int x=root)
{
    if((rk>=siz[son[x][0]]+1&&rk<=siz[son[x][0]]+tims[x])||!x)
        return x;
    if(rk<=siz[son[x][0]])
        return find_by_rank(rk,son[x][0]);
    else return find_by_rank(rk-siz[son[x][0]]-tims[x],son[x][1]);
}
int pred(int vl)
{
    int x=search(vl);
    splay(x);
    if(val[x]<vl) return x;
    else return search(INF,son[x][0]);
}
int succ(int vl)
{
    int x=search(vl);
    splay(x);
    if(val[x]>vl) return x;
    else return search(-INF,son[x][1]);
}
int main()
{
    //freopen("out.out","w",stdout);
    int n,ops,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        //printf("root:%d\n",root);
        /*for(int i=1;i<=cnt;i++)
            printf("%d:val:%d,fa:%d,siz:%d,son[0]:%d,son[1]:%d\n",i,val[i],fa[i],siz[i],son[i][0],son[i][1]);*/
        scanf("%d%d",&ops,&x);
        switch(ops)
        {
            case 1: ins(x);break;
            case 2: del(x);break;
            case 3: printf("%d\n",query_rank(x));break;
            case 4: printf("%d\n",val[find_by_rank(x)]);break;
            case 5: printf("%d\n",val[pred(x)]);break;
            case 6: printf("%d\n",val[succ(x)]);break;
        }
    }
}
