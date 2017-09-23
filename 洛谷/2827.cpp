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
int a[100010],n,m,q,u,v,t;
queue<int> qu,qu1,qu2;
int nlen=0;
inline int front(queue<int> &q)
{
    if(q.empty()) return -0x3f3f3f3f;
    else return q.front()+nlen;
}
inline int get()
{
    int mx=max(front(qu),max(front(qu1),front(qu2)));
    if(mx==front(qu)) qu.pop();
    else if(mx==front(qu1)) qu1.pop();
    else if(mx==front(qu2)) qu2.pop();
    return mx;
}
inline bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++) qu.push(a[i]);
    for(int i=1;i<=m;i++)
    {
        int tt=get();
        int len1=(ll)tt*u/v;
        int len2=tt-len1;
        qu1.push(len1-nlen-q);
        qu2.push(len2-nlen-q);
        if(i%t==0)  printf("%d ",tt);
        nlen+=q;
    }
    printf("\n");
    for(int i=1;i<=n+m;i++)
    {
        int tt=get();
        if(i%t==0)  printf("%d ",tt);
    }
    printf("\n");
}
