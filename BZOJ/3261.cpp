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
const int MAXN=301000;
struct node{
    int son[2],val;
}t[(MAXN<<7)+(MAXN<<4)];
int cnt,rt[MAXN<<1],pxor,n,m,x,l,r;
char opt[10];
inline void read(int &x)
{
    x=0;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) x=(x*10)+(ch^'0'),ch=getchar();
}
void insert(int x,int _x,int val)
{
    bool cur=0;
    for(int i=25;~i;i--)
    {
        cur=(val>>i)&1;
        t[x]=t[_x];t[x].val++;
        t[x].son[cur]=++cnt;
        x=t[x].son[cur];_x=t[_x].son[cur];
    }
    t[x]=t[_x];t[x].val++;
}
int query(int x,int _x,int val)
{
    bool cur=0;
    int siz=0,ret=0;
    for(int i=25;~i;i--)
    {
        cur=((val>>i)&1)^1;
        siz=t[t[x].son[cur]].val-t[t[_x].son[cur]].val;
        if(siz) x=t[x].son[cur],_x=t[_x].son[cur],ret|=cur<<i;
        else x=t[x].son[cur^1],_x=t[_x].son[cur^1],ret|=(cur^1)<<i;
    }
    return ret;
}
int main()
{
    read(n);read(m);
    n++;
    rt[1]=++cnt;
    insert(rt[1],0,0);
    for(int i=2;i<=n;i++)
    {
        read(x);
        pxor^=x;rt[i]=++cnt;
        insert(rt[i],rt[i-1],pxor);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt+1);
        if(opt[1]=='A') read(x),pxor^=x,++n,rt[n]=++cnt,insert(rt[n],rt[n-1],pxor);
        else
        {
            read(l);read(r);read(x);
            printf("%d\n",x^pxor^query(rt[r],rt[l-1],x^pxor));
        }
    }
    #ifdef LOCAL
        system("pause");
    #endif
}