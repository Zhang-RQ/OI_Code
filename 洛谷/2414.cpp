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
const int MAXN=100010;
const int MAXM=200010;
int head[MAXN];
struct Node{
    int v,nxt;
}Edge[MAXM];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
struct node{
    int x,y,num;
}Q[MAXN];
int ans[MAXN];
void add_(int,int);
int query_(int,int);
struct AC_automaton{
    int son[MAXN][26],fail[MAXN];
    int end[MAXN],dfn[MAXN],fa[MAXN];
    int node[MAXN],siz[MAXN],cnt;
    void build(char *s)
    {
        int x=0;
        int totnum=0;
        for(int i=1;s[i];i++)
        {
            if(s[i]=='P')
                node[++totnum]=x;
            else if(s[i]=='B')
                x=fa[x];
            else
            {
                if(!son[x][s[i]-'a'])
                {
                    son[x][s[i]-'a']=++cnt;
                    fa[cnt]=x;
                }
                x=son[x][s[i]-'a'];
            }
        }
    }
    void get_fail()
    {
        queue<int> q;
        for(int i=0;i<26;i++)
            if(son[0][i])
                fail[son[0][i]]=0,
                q.push(son[0][i]);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0;i<26;i++)
                if(son[x][i])
                {
                    int tmp=fail[x];
                    while(tmp&&!son[tmp][i])
                        tmp=fail[tmp];
                    if(son[tmp][i])
                        tmp=son[tmp][i];
                    fail[son[x][i]]=tmp;
                    q.push(son[x][i]);
                }
        }
        for(int i=1;i<=cnt;i++) // build_fail_tree
            add(fail[i],i);
    }
    int tot;
    void get_dfn(int x)
    {
        dfn[x]=++tot;
        siz[x]=1;
        for(int i=head[x];i;i=Edge[i].nxt)
            get_dfn(Edge[i].v),
            siz[x]+=siz[Edge[i].v];
    }
    void solve(char *s)
    {
        int x=0,qn=1;
        int nm=0;
        for(int i=1;s[i];i++)
        {
            switch(s[i])
            {
                case 'B': add_(dfn[x],-1);x=fa[x];break;
                case 'P':
                    nm++;
                    while(Q[qn].y==nm)
                    {
                        ans[Q[qn].num]+=query_(dfn[node[Q[qn].x]],dfn[node[Q[qn].x]]+siz[node[Q[qn].x]]-1);
                        qn++;
                    }
                break;
                default : x=son[x][s[i]-'a'];add_(dfn[x],1);break;
            }
        }
    }
}ACM;
int tree[MAXN];
void add_(int pos,int val)
{
    for(int i=pos;i<=ACM.tot;i+=i&-i)
        tree[i]+=val;
}
int query_(int l,int r)
{
    int ret=0;
    for(int i=r;i>=1;i-=i&-i)
        ret+=tree[i];
    for(int i=l-1;i>=1;i-=i&-i)
        ret-=tree[i];
    return ret;
}
bool cmp(node a,node b)
{
    return a.y<b.y;
}
int m;
char str[500010];
char tmp[500010];
int len,cont;
int main()
{
    scanf("%s",str+1);
    ACM.build(str);
    ACM.get_fail();
    ACM.get_dfn(0);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&Q[i].x,&Q[i].y),
        Q[i].num=i;
    sort(Q+1,Q+1+m,cmp);
    ACM.solve(str);
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}
