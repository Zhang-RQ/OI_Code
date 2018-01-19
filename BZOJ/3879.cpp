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
const int MAXN=500010;
const ll P=23333333333333333LL;
int Rank[MAXN],sa[MAXN],height[MAXN];
int tp[MAXN],sum[MAXN];
int st[MAXN][25],lg2[MAXN];
int vis[MAXN],tot,ps[MAXN],t,x,tmp[MAXN];
int pre[MAXN],lst[MAXN],stk[MAXN];
int top=0,Q,N;
char str[MAXN];
bool cmp(int a,int b)
{
    return Rank[a]<Rank[b];
}
void get_sa(int n)
{
    int m=127;
    for(int i=1;i<=n;i++) Rank[i]=str[i],tp[i]=i;
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;m=p,len<<=1)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=0;i<=m;i++) sum[i]=0;
        for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
        swap(Rank,tp);
        Rank[sa[1]]=1;
        p=1;
        for(int i=2;i<=n;i++)
            Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int _lst=0,j;
    for(int i=1;i<=n;height[Rank[i++]]=_lst) // i -> lpos
        for(_lst=_lst?_lst-1:_lst,j=sa[Rank[i]-1];str[j+_lst]==str[i+_lst];_lst++);
}
void get_st(int n)
{
    for(int i=2;i<=n;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int i=1;i<=n;i++)
        st[i][0]=height[i];
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i<=n&&i+(1<<(j-1))<=n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r) //l,r => Rank
{
    if(l>r) swap(l,r);
    ++l; //notice
    int len=lg2[r-l+1];
    //printf("%d %d %d %d %d\n",l,r,st[l][len],st[r-(1<<len)+1][len],len);
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
void solve()
{
    ll ans=0;
    scanf("%d",&t);
    tot=0;
    for(int i=1;i<=t;i++)
    {
        scanf("%d",&x);
        if(!vis[x])
            ps[++tot]=x,vis[x]=1;
    }
    sort(ps+1,ps+1+tot,cmp);
    for(int i=2;i<=tot;i++)
        tmp[i]=query(Rank[ps[i-1]],Rank[ps[i]]);
    tmp[1]=tmp[tot+1]=-1;
    stk[top=1]=1;
    for(int i=2;i<=tot;i++)
    {
        while(top&&tmp[stk[top]]>=tmp[i])
            --top;
        pre[i]=stk[top];
        stk[++top]=i;
    }
    stk[top=1]=tot+1;
    for(int i=tot;i>=2;i--)
    {
        while(top&&tmp[stk[top]]>tmp[i]) //notice
            --top;
        lst[i]=stk[top];
        stk[++top]=i;
    }
    vis[ps[1]]=0;
    for(int i=2;i<=tot;i++)
        //printf("pre=%d lst=%d i=%d tmp=%d\n",pre[i],lst[i],i,tmp[i]),
        (ans+=1ll*(i-pre[i])*(lst[i]-i)*tmp[i])%=P,
        vis[ps[i]]=0;
    printf("%lld\n",ans);
}
int main()
{
    scanf("%d%d",&N,&Q);
    scanf("%s",str+1);
    get_sa(N);
    get_st(N);
    while(Q--)
        solve();
    return 0;
}
