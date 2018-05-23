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
const int MAXN=3E7+10;
bool a[MAXN],b[MAXN];
int n,opt,x,y,kk;
struct Sset{
    set<int,greater<int>> s;
    int cnt[MAXN>>4];
    Sset(){s.clear();s.insert(-1);memset(cnt,0,sizeof cnt);}
    void insert(int x)
    {
        if(!cnt[x>>4]) s.insert(x>>4);
        cnt[x>>4]++;
    }
    void erase(int x)
    {
        cnt[x>>4]--;
        if(!cnt[x>>4]) s.erase(x>>4);
    }
    int query(int x)
    {
        x--;
        if(x<0) return -2;
        for(int i=x;i>=(x>>4)<<4;i--) if(a[i]^b[i]) return i;
        int y=*s.upper_bound(x>>4);
        if(~y) for(int i=((y+1)<<4)-1;i>=y<<4;i--) if(a[i]^b[i]) return i;
        return -2;
    }
}Set;
void add(int x,int y,bool *A)
{
    for(int i=y;x;x>>=1,i++)
        if(x&1)
        {
            A[i]^=1;
            if(a[i]^b[i]) Set.insert(i);
            else Set.erase(i);
            if(!A[i]) x+=2;
        }
}
int main()
{
    scanf("%d%*d%*d%*d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&opt);
        if(opt==1)
        {
            scanf("%d%d",&x,&y);
            if(x>0) add(x,y,a);
            else add(-x,y,b);
        }
        else
        {
            scanf("%d",&x);
            kk=Set.query(x);
            puts((a[x]==b[x])^(kk==-2||a[kk])?"1":"0");
        }
        
    }
    #ifdef LOCAL
        system("pause");
    #endif
}