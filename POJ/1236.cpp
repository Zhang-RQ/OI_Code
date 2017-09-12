#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;
bool instack[110];
int LOW[110],DFN[110];
int belong[110];
int in[110],out[110];
int ans1,ans2;
int cnt=1,tot=0,N;
int cnt1=1;
#define M 200010
#define NN 200010
int alist[M];
struct Node{
    int v,nxt;
}Edge[NN];
int cnte=0;
void add(int u,int v)
{
    Edge[++cnte].nxt=alist[u];
    Edge[cnte].v=v;
    alist[u]=cnte;
 }
int min(int a,int b)
{
    if(a<b) return a;
    else return b;
}
int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}
stack<int> s;
void Tarjan(int num)
{

    LOW[num]=DFN[num]=cnt++;
    s.push(num);
    instack[num]=1;
    for(int i=alist[num];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(DFN[v]==-1)
        {
            Tarjan(v);
            LOW[num]=min(LOW[num],LOW[v]);
        }else if(instack[v])
        {
            LOW[num]=min(LOW[num],DFN[v]);
        }
    }
    if(DFN[num]==LOW[num])
    {
        int temp;
        while(1)
        {
            temp=s.top();
            s.pop();
            instack[temp]=0;
            belong[temp]=cnt1;
            //printf("%d\n",belong[temp]);
            if(temp==num) break;
        }
        cnt1++;
    }
}
int main()
{
    memset(DFN,-1,sizeof(DFN));
    ans1=0;
    ans2=0;
    int temp;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        while(scanf("%d",&temp)&&temp!=0) add(i,temp);
    for(int i=1;i<=N;i++) if(DFN[i]==-1) Tarjan(i);
    for(int i=1;i<=N;i++)
    {
        for(int j=alist[i];j;j=Edge[j].nxt)
        {
            int v=Edge[j].v;
            if(belong[i]==belong[v]) continue;
            in[belong[v]]++;
            out[belong[i]]++;
        }
    }
    for(int i=1;i<cnt1;i++)
    {
        if(in[i]==0) ans1++;
        if(out[i]==0) ans2++;
    }
    if(cnt1==2) {printf("1\n0\n");return 0;}
    printf("%d\n%d\n",ans1,max(ans1,ans2));
    return 0;
}
