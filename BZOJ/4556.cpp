
// Unfinished

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
char str[100010];
int sa[100010],rnk[100010];
int tp[100010],sum[100010];
int height[100010];
int st[100010][20],lg2[100010];
int n,m;
void get_sa(int n)
{
    int m=127;
    for(int i=1;i<=n;i++) rnk[i]=str[i],tp[i]=i;
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[rnk[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[rnk[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;len<<=1,m=p)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=0;i<=m;i++) sum[i]=0;  //x为第一关键字，y为第二关键字
        for(int i=1;i<=n;i++) sum[rnk[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[rnk[tp[i]]]--]=tp[i];
        swap(rnk,tp);rnk[sa[1]]=1;p=1;
        for(int i=2;i<=n;i++)
            rnk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int lst=0,j;
for(int i=1;i<=n;height[rnk[i++]]=lst)
    for(lst=lst?lst-1:lst,j=sa[rnk[i]-1];str[j+lst]==str[i+lst];++lst);
}
void get_st(int n)
{
    for(int i=2;i<=n;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int i=1;i<=n;i++)
        st[i][0]=height[i];
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i<=n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r)
{
    if(l>r) swap(l,r);
    int len=lg2[r-l+1];
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
struct node{int ls,rs,val;} tree[4000100];
int cnt=0,rt[100010];
void insert(int &x,int l,int r,int pos,int x_)
{
    x=++cnt;
    tree[x]=tree[x_];
    tree[x].val++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(tree[x].ls,l,mid,pos,tree[x_].ls);
    else insert(tree[x].rs,mid+1,r,pos,tree[x_].rs);
}
int query_sum(int x,int l,int r,int ql,int qr,int x_)
{
    if(l>qr||r<ql) return 0;
    if(ql<=l&&r<=qr) return tree[x].val-tree[x_].val;
    int mid=(l+r)>>1,ret=0;
    if(tree[x].val-tree[x_].val==0) return 0;
    if(ql<=mid) ret+=query_sum(tree[x].ls,l,mid,ql,qr,tree[x_].ls);
    if(qr>mid) ret+=query_sum(tree[x].rs,mid+1,r,ql,qr,tree[x_].rs);
    return ret;
}
int query_pre(int x,int l,int r,int pos,int x_)
{
    if(l==r) return l;
    int tmp=tree[tree[x].ls].val-tree[tree[x_].ls].val;
    int mid=(l+r)>>1;
    if(tmp>=pos) return query_pre(tree[x].ls,l,mid,pos,tree[x_].ls);
    else return query_pre(tree[x].rs,mid+1,r,pos-tmp,tree[x_].rs);
}
int query_sub(int x,int l,int r,int pos,int x_)
{
    if(l==r) return l;
    int tmp=tree[tree[x].rs].val-tree[tree[x_].rs].val;
    int mid=(l+r)>>1;
    if(tmp>=pos) return query_sub(tree[x].rs,mid+1,r,pos,tree[x_].rs);
    else return query_sub(tree[x].ls,l,mid,pos-tmp,tree[x_].rs);
}
bool check(int x,int a,int b,int c,int d)
{
    int ans=0;
    int kk=query_sum(rt[b-x+1],1,n,1,rnk[c]-1,rt[a]);
    int l=kk?query_pre(rt[b-x+1],1,n,kk,rt[a]):-1;
    kk=query_sum(rt[b-x+1],1,n,rnk[c]+1,n,rt[a]);
    int r=kk?query_sub(rt[b-x+1],1,n,kk,rt[a]):-1;
    if(l!=-1)
    {
        int xx=min(query(l,rnk[c]),b-sa[l]+1);
        ans=max(ans,xx);
    }
    if(r!=-1)
    {
        int xx=min(query(r,rnk[c]),b-sa[l]+1);
        ans=max(ans,xx);
    }
    if(c>=a&&c<=b) ans=max(ans,min(d,b)-c+1);
    return ans>=x;
}
int t1,t2,t3,t4;
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",str+1);
    get_sa(n);
    get_st(n);
    for(int i=1;i<=n;i++)
        insert(rt[i],1,n,rnk[i],rt[i-1]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
        int L=0,R=t2-t1+1,ans=0;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check(mid,t1,t2,t3,t4)) ans=mid,L=mid+1;
            else R=mid-1;
        }
        printf("%d\n",ans);
    }
}
