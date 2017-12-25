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
ll tree[300010];
int n,m,x,y,k;
int cont[300010];
ll ned[300010];
vector<int> satt[300010];
struct node{
    int l,r,val;
}opt[300010];
void edit(int pos,int val)
{
    for(int i=pos;i<=m;i+=i&-i)
        tree[i]+=val;
}
ll query(int pos)
{
    ll ret=0;
    for(int i=pos;i>=1;i-=i&-i)
        ret+=tree[i];
    return ret;
}
void change(int l,int r,int val)
{
    if(l<=r)
    {
        edit(l,val);
        edit(r+1,-val);
    }
    else
    {
        edit(l,val);edit(m+1,-val);
        edit(1,val);edit(r+1,-val);
    }
}
int larr[300010],rarr[300010];
int ans[300010],tv[300010];
int now=0;
void query(int l,int r,int L,int R){
    if(l>r) return;
    if(L>R) return;
    if(l==r){
        for(register int i=L;i<=R;++i)
            ans[cont[i]]=l;
        return;
    }
    int mid=(l+r)>>1;
    while(now<mid)
        ++now,
        change(opt[now].l,opt[now].r,opt[now].val);
    while(now>mid)
        change(opt[now].l,opt[now].r,-opt[now].val),
        --now;
    for(int i=L;i<=R;++i){
        tv[cont[i]]=0;
        for(int j=0;j<satt[cont[i]].size();++j)
            tv[cont[i]]+=query(satt[cont[i]][j]);
    }
    int lct=0,rct=0;
    for(register int i=L;i<=R;++i)
        if(tv[cont[i]]>=ned[cont[i]])
            larr[++lct]=cont[i];//把可以的国家归于左区间
        else rarr[++rct]=cont[i];//把不可以的国家归于右区间
    int mid2=lct;
    for(register int i=1;i<=lct;++i)
        cont[i+L-1]=larr[i];
    for(register int i=1;i<=rct;++i)
        cont[L+lct+i-1]=rarr[i];//复制区间
    query(l,mid,L,L+mid2-1);
    query(mid+1,r,L+mid2,R);//继续二分
}
int main()
{
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            cont[i]=i;
        for(int i=1;i<=m;i++)
            scanf("%d",&x),
            satt[x].push_back(i);
        for(int i=1;i<=n;i++)
            scanf("%lld",&ned[i]);
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d%d%d",&opt[i].l,&opt[i].r,&opt[i].val);
        opt[++k].l=1;
        opt[k].r=m;
        opt[k].val=0x3f3f3f3f;
        query(1,k,1,n);
        for(int i=1;i<=n;i++)
            if(ans[i]!=k)
                printf("%d\n",ans[i]);
            else printf("NIE\n");
        return 0;
}
