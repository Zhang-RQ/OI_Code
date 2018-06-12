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
const int MAXN=300010<<1;
char str[MAXN],s[MAXN];
ll ans=0;
int son[MAXN][26],par[MAXN],mx[MAXN],siz[MAXN];
int buk[MAXN],tp[MAXN],jmp[MAXN][21],nd[MAXN],hw[MAXN];
int lst=1,rt=1,cnt=1,n;
void insert(int x)
{
    int np=++cnt,p=lst;
    mx[np]=mx[p]+1;
    siz[np]=1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        } 
    }
    lst=np;
}
void topo()
{
    for(int i=1;i<=cnt;i++) jmp[i][0]=par[i];
    for(int j=1;j<=20;j++)
        for(int i=1;i<=cnt;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    int mxx=0;
    for(int i=1;i<=cnt;i++) buk[mx[i]]++,mxx=max(mxx,mx[i]);
    for(int i=1;i<=mxx;i++) buk[i]+=buk[i-1];
    for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--) siz[par[tp[i]]]+=siz[tp[i]];
}
ll calc(int l,int r)
{
    int len=r-l+1,x=nd[r];
    for(int j=20;~j;j--)
        if(mx[jmp[x][j]]>=len)
            x=jmp[x][j];
    return 1ll*siz[x]*(r-l+1);
}
void manacher()
{
	int mx=0,id;str[0]='+';str[n+1]='*';
	for(int i=1;i<=n;i++)
	{
		if(mx>i) hw[i]=min(mx-i,hw[2*id-i-1]);
		else hw[i]=0;
		while(str[i+hw[i]+1]==str[i-hw[i]])
		{
			hw[i]++;
			ans=max(ans,calc(i-hw[i]+1,i+hw[i]));
		}
		if(hw[i]+i>mx)mx=hw[i]+i,id=i;
	}
	mx=0;
	for(int i=1;i<=n;i++)
	{
		if(mx>i) hw[i]=min(mx-i-1,hw[2*id-i]);
		else {hw[i]=1;ans=max(ans,calc(i-hw[i]+1,i+hw[i]-1));}
		while(str[i+hw[i]]==str[i-hw[i]])
		{
			hw[i]++;
			ans=max(ans,calc(i-hw[i]+1,i+hw[i]-1));
		}
		if(hw[i]+i>mx) mx=hw[i]+i,id=i;
	}
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) insert(str[i]-'a'),nd[i]=lst;
    topo();manacher();
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}