#include<cstdio>
#include<algorithm>
#define N 1111111
#define inf 1e15
using namespace std;
int n,i,j,x,u,sz,num,tot,to[N],cir[N],fa[N],v[N],fir[N],ne[N<<1],la[N<<1];
long long l,now,ans,mav,mav2,zs,n1,n2,va[N<<1],sum[N],d[N],len[N];bool c[N],vis[N],vis2[N];
void ins(int x,int y,long long z){la[++tot]=y;va[tot]=z;ne[tot]=fir[x];fir[x]=tot;}
void fcur(int x){//找环 
    v[x]=++sz;int y;
    for(;true;x=y){
        y=to[x];
        if(v[y]){
            cir[++num]=y;c[y]=1;
            for(;x!=y;x=fa[x])c[x]=1,cir[++num]=x,sum[num]=sum[num-1]+len[x];
            zs=sum[num]+len[cir[1]];return;
        }
        fa[y]=x;v[y]=1;
    }
}
void ghigh(int x,long long high){//第一遍DFS 
    vis[x]=1;if(high>mav)mav=high,u=x;
    for(int i=fir[x];i;i=ne[i])if(!vis[la[i]]&&!c[la[i]])ghigh(la[i],high+va[i]);
}
void ghigh2(int x,long long high){//第二遍DFS 
    vis2[x]=1;if(high>mav2)mav2=high;
    for(int i=fir[x];i;i=ne[i])if(!vis2[la[i]]&&!c[la[i]])ghigh2(la[i],high+va[i]);
}
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d%lld",&x,&l),to[i]=x,len[i]=l,ins(i,x,l),ins(x,i,l);
    for(i=1;i<=n;i++)if(!v[i]&&!vis2[i]&&!vis[i]){
        num=0;now=-inf;fcur(i);
        for(j=1;j<=num;j++){//对环上每个节点为根做DFS得到d[j]和该树直径更新答案 
            mav=-inf;mav2=-inf;ghigh(cir[j],0);
            c[cir[j]]=0;ghigh2(u,0);c[cir[j]]=1;
            d[j]=mav;now=max(now,mav2);
        }
        n1=inf;n2=-inf;//n1为min(sum[j]-d[j]),n2为max(sum[j]+d[j])，用这两个值快速更新答案 
        for(j=1;j<=num;j++){//更新答案 
            now=max(now,max(sum[j]+d[j]-n1,zs-(sum[j]-d[j])+n2));
            n1=min(n1,sum[j]-d[j]);n2=max(n2,sum[j]+d[j]);
        }
        ans+=now;
    }
    printf("%lld",ans);
}
// #include<cstdio>
// #include<cstring>
// #include<cstdlib>
// #include<cctype>
// #include<cmath>
// #include<iostream>
// #include<algorithm>
// #include<vector>
// #include<set>
// #include<map>
// #include<queue>
// #include<stack>
// #include<cassert>
// typedef long long ll;
// typedef unsigned long long ull;
// using namespace std;
// const int MAXN=1E6+10;
// const int MAXM=2E6+10;
// struct __edge{
//     int nxt,v,w;
// }Edge[MAXM];
// int head[MAXN],cnt_e,dfn[MAXN],cnt,cir[MAXN],tot,fa[MAXN],n,len[MAXN];
// ll f[MAXN][2],dis,sum[MAXN],tsum,n1,n2,now,ans;
// bool inc[MAXN];
// inline void add(int u,int v,int w)
// {
//     Edge[++cnt_e].v=v;
//     Edge[cnt_e].w=w;
//     Edge[cnt_e].nxt=head[u];
//     head[u]=cnt_e;
// }
// void find_circle(int x,int father)
// {
//     dfn[x]=++cnt;fa[x]=father;
//     for(int i=head[x];i;i=Edge[i].nxt)
//     {
//         int v=Edge[i].v;
//         if(v==father) continue;
//         if(dfn[v]&&dfn[v]<dfn[x])
//         {
//             for(int y=x;y!=v;y=fa[y]) cir[++tot]=y,inc[y]=1,sum[tot+1]=sum[tot]+len[y];
//             cir[++tot]=v;inc[v]=1;tsum=sum[tot]+Edge[i].w;
//             return;
//         }
//         else if(!dfn[v]) len[v]=Edge[i].w,find_circle(v,x);
//     }
// }
// void dfs(int x,int fa)
// {
//     f[x][0]=0;f[x][1]=-(1ll<<60);
//     for(int i=head[x];i;i=Edge[i].nxt)
//     {
//         int v=Edge[i].v;
//         if(v==fa||inc[v]) continue;
//         dfs(v,x);
//         if(f[v][0]+Edge[i].w>f[x][0]) f[x][1]=max(f[x][0],f[v][1]+Edge[i].w),f[x][0]=f[v][0]+Edge[i].w;
//         else f[x][1]=max(f[x][1],f[v][0]+Edge[i].w);
//     }
//     dis=max(dis,f[x][0]+f[x][1]);
// }
// int main()
// {
//     scanf("%d",&n);
//     for(int i=1,v,w;i<=n;i++) scanf("%d%d",&v,&w),add(i,v,w),add(v,i,w);
//     for(int i=1;i<=n;i++)
//     {
//         if(dfn[i]) continue;
//         now=tot=0;tsum=dis=0;
//         find_circle(i,0);
//         if(!tot) cir[++tot]=i;
//         for(int j=1;j<=tot;j++)
//             dfs(cir[j],0);
//         now=dis;
//         for(int j=1;j<=tot;j++) printf("%d %lld %lld %lld\n",cir[j],sum[j],f[cir[j]][0],f[cir[j]][1]);
//         for(int j=1;j<=n;j++) printf("%d ",inc[j]);
//         n1=1ll<<60;n2=-(1ll<<60);
//         printf("now=%lld \n",now);
//         for(int j=1;j<=tot;j++)
//         {
//             now=max(now,max(sum[j]+f[cir[j]][0]-n1,tsum-(sum[j]-f[cir[j]][0])+n2));
//             n1=min(n1,sum[j]-f[cir[j]][0]);n2=max(n2,sum[j]+f[cir[j]][0]);
//         }
//         ans+=now;
//     }
//     printf("%lld\n",ans);
//     #ifdef LOCAL
//         system("pause");
//     #endif
// }