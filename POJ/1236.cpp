#include<cstdio>
#include<cstring>
using namespace std;
bool DAC[110][110];
bool instack[110];
int LOW[110],DFN[110];
int stack[110],belong[110];
int in[110],out[110];
int ans1,ans2;
int cnt=1,tot=0,N;
int cnt1=1;
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
void Tarjan(int num)
{

    LOW[num]=DFN[num]=cnt++;
    stack[++tot]=num;
    instack[num]=1;
    for(int i=1;i<=N;i++)
    {
        if(!DAC[num][i]) continue;
        if(DFN[i]==-1)
        {
            Tarjan(i);
            LOW[num]=min(LOW[num],LOW[i]);
        }else if(instack[i])
        {
            LOW[num]=min(LOW[num],DFN[i]);
        }
    }
    if(DFN[num]=LOW[num])
    {
        int temp;
        while(1)
        {
            temp=stack[tot--];
            //printf("%d:%d?=%d\n",tot+1,temp,num);
            instack[temp]=0;
            belong[temp]=cnt1;printf("%d\n",belong[temp]);
            if(temp==num) break;
        }
        cnt1++;
    }
}
int main()
{
    memset(instack,0,sizeof(instack));
    memset(LOW,0,sizeof(LOW));
    memset(DFN,-1,sizeof(DFN));
    memset(DAC,0,sizeof(DAC));
    ans1=0;
    ans2=0;
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    int temp;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        while(scanf("%d",&temp)&&temp!=0) DAC[i][temp]=1;
    for(int i=1;i<=N;i++) if(DFN[i]==-1) Tarjan(i);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            if(belong[i]==belong[j]) continue;
            if(DAC[i][j])
            {
                in[belong[j]]++;
                out[belong[i]]++;
            }
        }
    for(int i=1;i<=cnt1;i++)
    {
        if(in[i]==0) ans1++;
        if(out[i]==0) ans2++;
    }

    if(cnt1==2) printf("1\n0\n");
    //printf("%d\n%d\n",ans1,max(ans1,ans2));
    return 0;
}
