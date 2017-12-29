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
#define now prime[j]*i
int prime[100010],F[100010],h[100010],miu[100010],Q;//h表示i的最小质因子的积
bool vis[100010];
int p[100010];
bool cmp(int a,int b)
{
    return F[a]<F[b];
}
void init()
{
    miu[1]=F[1]=h[1]=1;
    for(int i=2;i<=100000;i++)
    {
        if(!vis[i])
        {
            prime[++prime[0]]=i;
            F[i]=i+1;
            h[i]=i;
            miu[i]=-1;
        }
        for(int j=1;j<=prime[0]&&prime[j]*i<=100000;j++)
        {
            vis[now]=1;
            if(i%prime[j]==0)
            {
                miu[now]=0;
                h[now]=h[i]*prime[j];
                F[now]=F[i]+F[i/h[i]]*h[now];
                break;
            }
            else
            {
                miu[now]=-miu[i];
                F[now]=F[i]+F[i]*prime[j];
                h[now]=prime[j];
            }
        }
    }
    for(int i=1;i<=100000;i++)
        p[i]=i;
    sort(p+1,p+100001,cmp);
}
struct node{
    int n,m,a,id;
    bool operator < (node a)
    {
        return this->a<a.a;
    }
}query[20010];
int ans[20010],tree[100100];
void add(int pos,int val)
{
    for(;pos<=100000;pos+=pos&-pos)
        tree[pos]+=val;
}
int ask(int pos)
{
    int ret=0;
    for(;pos>=1;pos-=pos&-pos)
        ret+=tree[pos];
    return ret;
}
int main()
{
    init();
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
        scanf("%d%d%d",&query[i].n,&query[i].m,&query[i].a),
        query[i].id=i;
    sort(query+1,query+1+Q);
    int nw=0;
    for(int i=1;i<=Q;i++)
    {
        while(nw<100000&&F[p[nw+1]]<=query[i].a)
        {
            ++nw;
            int k=p[nw];
            for(int j=1;j*k<=100000;j++)
                add(j*k,miu[j]*F[k]);
        }
        int _n=query[i].n,_m=query[i].m;
        int lim=min(_n,_m);
        int t_ans=0;
        for(int j=1;j<=lim;)
        {
            int pos=min(_n/(_n/j),_m/(_m/j));
            t_ans+=(_n/j)*(_m/j)*(ask(pos)-ask(j-1));
            j=pos+1;
        }
        t_ans&=2147483647;
        ans[query[i].id]=t_ans;
    }
    for(int i=1;i<=Q;i++)
        printf("%d\n",ans[i]);
}
