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
struct node{
    int l,r,id;
    node(){}
    node(int L,int R,int ID):l(L),r(R),id(ID){}
}Query[200010];
int answer[200010];
int cnt[1000010];
int arr[50010];
int n,m,tl,tr;
int size,ans=0;
bool cmp(node &a,node &b)
{
    return (a.l/size==b.l/size)?(a.r<b.r):(a.l/size<b.l/size);
}

void add(int pos)
{
    if((++cnt[arr[pos]])==1) ans++;
    return;
}
void del(int pos)
{
    if((--cnt[arr[pos]])==0) ans--;
    return;
}
int main()
{
    scanf("%d",&n);
    size=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&tl,&tr);
        Query[i]=node(tl,tr,i);
    }
    sort(Query+1,Query+1+m,cmp);
    int curL=1,curR=0;
    for(int i=1;i<=m;i++)
    {
         int L=Query[i].l,R=Query[i].r;
         while(curL<L) del(curL++);
         while(curL>L) add(--curL);
         while(curR>R) del(curR--);
         while(curR<R) add(++curR);
         answer[Query[i].id]=ans;
    }
    for(int i=1;i<=m;i++) printf("%d\n",answer[i]);
}
