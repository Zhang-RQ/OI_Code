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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=5010;
int son[MAXN][26],len[6];
int par[MAXN],mx[MAXN],lx[MAXN],ans[MAXN];
int rt=1,cnt=1,lst=1,n,tp[MAXN],buk[MAXN];
char s[6][MAXN];
void init()
{
    int mxx=0;
    for(int i=1;i<=cnt;i++) ans[i]=mx[i],buk[mx[i]]++,mxx=max(mxx,mx[i]);
    for(int i=1;i<=mxx;i++) buk[i]+=buk[i-1];
    for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
}
void insert(int x)
{
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x])  son[p][x]=np,p=par[p];
    if(!p)  par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1)  par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q)  son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1),len[i]=strlen(s[i]+1);
    for(int i=1;i<=len[1];i++)
        insert(s[1][i]-'a');
    init();
    for(int i=2;i<=n;i++)
    {
        memset(lx,0,sizeof lx);
        int pos=rt,l=0;
        for(int j=1;j<=len[i];j++)
        {
            while(pos!=rt&&!son[pos][s[i][j]-'a']) pos=par[pos],l=mx[pos];
            if(son[pos][s[i][j]-'a']) pos=son[pos][s[i][j]-'a'],l++;
            else pos=rt,l=0;
            lx[pos]=max(lx[pos],l);
        }
        for(int j=cnt;j>=1;j--) lx[par[tp[j]]]=max(lx[par[tp[j]]],lx[tp[j]]);
        for(int j=1;j<=cnt;j++) ans[j]=min(ans[j],lx[j]);
    }
    int as=0;
    for(int i=1;i<=cnt;i++) as=max(as,ans[i]);
    printf("%d\n",as);
}
