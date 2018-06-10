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
    const int MAXN=1E4+5;
    const int MAXM=3E5+5;
    const int INF=0x3f3f3f3f;
    struct __edge{
        int nxt,v,f,c;
    }Edge[MAXM];
    int head[MAXN],cnt_e=1,flw[MAXN],pre[MAXN],preedge[MAXN],S,T=MAXN-1,n,m;
    ll dis[MAXN],dif[MAXN];
    bool inq[MAXN];
    queue<int> q;
    inline void add(int u,int v,int f,int c)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        Edge[cnt_e].f=f;
        Edge[cnt_e].c=c;
        head[u]=cnt_e;
    }
    bool spfa()
    {
        while(!q.empty()) q.pop();
        memset(dis,0x3f,sizeof dis);
        memset(flw,0,sizeof flw);
        q.push(S);dis[S]=0;flw[S]=0x3f3f3f3f;
        inq[S]=1;
        while(!q.empty())
        {
            int x=q.front();inq[x]=0;q.pop();
            for(int i=head[x];i;i=Edge[i].nxt)
            {
                if(!Edge[i].f) continue;
                int v=Edge[i].v;
                if(dis[v]>dis[x]+Edge[i].c)
                {
                    pre[v]=x;preedge[v]=i;
                    flw[v]=min(flw[x],Edge[i].f);
                    dis[v]=dis[x]+Edge[i].c;
                    if(!inq[v]) q.push(v),inq[v]=1;
                }
            }
        }
        return dis[T]!=0x3f3f3f3f3f3f3f3f;
    }
    ll MCMF()
    {
        ll ret=0;
        while(spfa())
        {
            int x=T,fw=flw[T];
            while(x!=S)
            {
                Edge[preedge[x]].f-=fw;
                Edge[preedge[x]^1].f+=fw;
                x=pre[x];
            }
            ret+=dis[T]*flw[T];
        }
        return ret;
    }
    int main()
    {
        scanf("%d%d",&n,&m);
        for(int i=1,y;i<=n;i++)  scanf("%d",&y),add(i,i+1,INF,0),add(i+1,i,0,0),dif[i]-=y,dif[i+1]+=y;
        for(int i=1,l,r,w;i<=m;i++) scanf("%d%d%d",&l,&r,&w),add(r+1,l,INF,w),add(l,r+1,0,-w);
        for(int i=1;i<=n+1;i++)
        {
            if(dif[i]>0) add(S,i,dif[i],0),add(i,S,0,0);
            else add(i,T,-dif[i],0),add(T,i,0,0);
        }
        printf("%lld\n",MCMF());
        #ifdef LOCAL
            system("pause");
        #endif
    }