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
const int MAXN=3e6+5;
struct node{
    int val;//max
    int fa,son[26];
}SAM[MAXN];
int tp[MAXN],buk[MAXN],siz[MAXN];
int cnt=1,root=1,lst=1,n;
char str[MAXN];
void append(int x)
{
    x-='a';
    int p=lst,np=++cnt;
    SAM[np].val=SAM[p].val+1;
    siz[np]=1;
    for(;p&&!SAM[p].son[x];p=SAM[p].fa)
        SAM[p].son[x]=np;
    if(!p)
        SAM[np].fa=root;
    else
    {
        int q=SAM[p].son[x];
        if(SAM[q].val==SAM[p].val+1)
            SAM[np].fa=q;
        else
        {
            int nq=++cnt,q=SAM[p].son[x];
            //siz[nq]=1;
            SAM[nq].val=SAM[p].val+1;
            memcpy(SAM[nq].son,SAM[q].son,sizeof SAM[q].son);
            SAM[nq].fa=SAM[q].fa;
            SAM[q].fa=SAM[np].fa=nq;
            while(p&&SAM[p].son[x]==q)
                SAM[p].son[x]=nq,p=SAM[p].fa;
        }
    }
    lst=np;
}
ll ans=0;
void calc()
{
    for(int i=1;i<=cnt;i++)
        buk[SAM[i].val]++;
    for(int i=1;i<=cnt;i++)
        buk[i]+=buk[i-1];
    for(int i=1;i<=cnt;i++)
        tp[buk[SAM[i].val]--]=i;
    for(int i=cnt;i>=1;i--)
    {
        int t=tp[i];
        //printf("%d %d %d\n",t,siz[t],SAM[t].val);
        siz[SAM[t].fa]+=siz[t];
        if(siz[t]!=1) ans=max(ans,1ll*siz[t]*SAM[t].val);
    }
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)
        append(str[i]);
    calc();
    //printf("%d\n",cnt);
    //for(int i=1;i<=cnt;i++)
    //    printf("%d ",SAM[i].val);
    //puts("");
    printf("%lld\n",ans);
}
