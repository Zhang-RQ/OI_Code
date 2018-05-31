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
const int MAXN=4010;
const int INF=1<<30;
int top,n,sum[MAXN][MAXN],mid,k;
struct _data{
    int x,y;
    _data(){}
    _data(int _,int __):x(_),y(__){}
    inline bool operator < (const _data &rhs) const {return x==rhs.x?y<rhs.y:x<rhs.x;}
    inline bool operator > (const _data &rhs) const {return x==rhs.x?y>rhs.y:x>rhs.x;}
    inline _data operator + (const _data &rhs) const {return _data(x+rhs.x,y+rhs.y);}
    inline _data operator + (const int &rhs) const {return _data(x+rhs,y);}
}f[MAXN];
struct decision{
    int x,l,r;
    decision(){}
    decision(int _,int __,int ___):x(_),l(__),r(___){}
};
deque<decision> q;
inline _data upd(const _data &a) {return _data(a.x+mid,a.y+1);}
_data calc(int x,int y)
{
    _data ret=upd(f[x]+(sum[y][y]-sum[x][y]));
    // printf("calc:%d %d=> %d %d\n",x,y,ret.x,ret.y);
    return ret;
}
int binary(int L,int R,int x,int _x)
{
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(calc(x,mid)>calc(_x,mid)) R=mid-1;
        else L=mid+1;
    }
    return L;
}
void solve()
{
    for(int i=1;i<=n;i++) f[i]=_data(INF,0);
    q.clear();
    // stk[++top]=decision(1,2,n);
    q.push_back(decision(0,1,n));
    // printf("i=1 ans=%d %d\n",f[1].x-mid*f[1].y,f[1].y);
    for(int i=1;i<=n;i++)
    {
        while(q.size()&&i>q.front().r) q.pop_front();
        f[i]=calc(q.front().x,i);
        // printf("i=%d ans=%d %d %d\n",i,f[i].x-mid*f[i].y,f[i].y,q.front().x);
        if(!q.size()||calc(i,n)<calc(q.back().x,n))
        {
            while(q.size()&&calc(i,q.back().l)<calc(q.back().x,q.back().l)) q.pop_back();
            if(q.size())
            {
                int _x=binary(q.back().l,q.back().r,q.back().x,i);
                assert(calc(q.back().x,_x)>calc(i,_x));
                decision _t=q.back();q.pop_back();
                q.push_back(decision(_t.x,_t.l,_x-1));
                q.push_back(decision(i,_x,n));
            }
            else q.push_back(decision(i,1,n));
        }
    }
}

char B[(1<<26) + 10],*S=B;int F(){for(;*S<'-';S++);int x=*S++-'0';for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');return x;}

int main()
{
    fread(B,1,1<<26,stdin);
    n=F();k=F();
    // scanf("%d%d",&n,&k);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            x=F();if(i>j) x=0;
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+x;
        }
    int L=0,R=sum[n][n];
    while(L<=R)
    {
        // printf("L=%d-------R=%d\n",L,R);
        mid=(L+R)>>1;solve();
        // printf("final K=%d\n",f[n].y);
        if(f[n].y<=k) R=mid-1;
        else L=mid+1;
    }
    mid=L;solve();
    // for(int i=1;i<=n;i++)
    //     printf("%d %d %d\n",f[i].x-f[i].y*L,f[i].y,frm[i]);
    printf("%d\n",f[n].x-k*L);
    #ifdef LOCAL
        system("pause");
    #endif
}