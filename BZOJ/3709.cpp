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
const int MAXN=100100;
struct node{
    int a,b,id;
}a[MAXN],b[MAXN];
bool cmp1(node a,node b) {return a.a<b.a;}
bool cmp2(node a,node b) {return a.b>b.b;}
int tota,totb;
int n,aa,bb;
ll c,d;
bool ok=1;
int main()
{
    scanf("%d%lld",&n,&c);d=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&aa,&bb);
        if(aa<=bb) a[++tota].a=aa,a[tota].b=bb,a[tota].id=i;
        else b[++totb].a=aa,b[totb].b=bb,b[totb].id=i;
    }
    stable_sort(a+1,a+tota+1,cmp1);
    stable_sort(b+1,b+totb+1,cmp2);
    for(int i=1;i<=tota;i++)
    {
        c-=a[i].a;
        if(c<=d) {ok=0;break;}
        c+=a[i].b;
    }
    for(int i=1;i<=totb;i++)
    {
        c-=b[i].a;
        if(c<=d) {ok=0;break;}
        c+=b[i].b;
    }
    if(!ok) puts("NIE");
    else
    {
        puts("TAK");
        for(int i=1;i<=tota;i++) printf("%d ",a[i].id);
        for(int i=1;i<=totb;i++) printf("%d ",b[i].id);
    }
    puts("");
}
