#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int pay[10010];
bool vis[10010];
int nxt[20010],v[20010];
int in[10010],front[10010];
int main()
{
    int n,m;
    int uu,vv;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   pay[i]=100;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&uu,&vv);
        nxt[i]=front[vv];
        v[i]=uu;
        front[vv]=i;
        ++in[uu];
    }
    queue<int> q;
    int cnt=0;
    int money=0;
    while(true)
    {
        for(int i=1;i<=n;i++)
        {
            if((!vis[i])&&(!in[i]))
            {
                q.push(i);
                vis[i]=true;
            }
        }
        if(q.empty()) break;
        while(!q.empty())
        {
            cnt++;
            int tmp=q.front();
            q.pop();
            pay[tmp]+=money;
            for(int j=front[tmp];j;j=nxt[j])
            {
                //printf("%d->%d,%d\n",tmp,v[j],money);
                --in[v[j]];
            }
        }
        money++;
    }
    int ans=0;
    if(cnt==n)
    {
        for(int i=1;i<=n;i++)   ans+=pay[i];
        printf("%d\n",ans);
    }else puts("Poor Xed\n");
}
