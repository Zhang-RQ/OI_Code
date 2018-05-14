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
const int MAXN=100010;
const int MAXQ=100010;
struct Query{
    int l,r,id;
}que[MAXQ];
int son[MAXN*40][2],lst[MAXN*40],o[40],n,q,cnt;
char s[MAXN];
ll ans[MAXN];
void insert(int p)
{
    int x=0;
    for(int i=0;i<40&&p+i<=n;i++)
    {
        if(!son[x][s[i+p]-'0']) son[x][s[i+p]-'0']=++cnt;
        else  o[i+1]=max(lst[son[x][s[i+p]-'0']],o[i+1]);
        x=son[x][s[i+p]-'0'];
        lst[x]=p;
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    for(int i=1;i<=q;i++) scanf("%d%d",&que[i].l,&que[i].r),que[i].id=i;
    sort(que+1,que+1+q,[](const Query &lhs,const Query &rhs)->bool{return lhs.r<rhs.r||(lhs.r==rhs.r&&lhs.l<rhs.l);});
    int cur=0;
    for(int i=1;i<=q;i++)
    {
        while(cur<que[i].r) insert(++cur);
        for(int j=1;j<=40;j++)
            if(o[j]>=que[i].l) ans[que[i].id]+=1ll*j*(o[j]-max(que[i].l-1,o[j+1]));
            else break;
    }
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
