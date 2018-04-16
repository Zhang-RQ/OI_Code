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
const int MAXN=1E5+5;
int n,L,P,lst[MAXN],ls,T,sum[MAXN],nxt[MAXN];
long double f[MAXN];
char s[MAXN][32];
struct dat{
    int l,r,p;
    dat(){}
    dat(int _l,int _r,int _pos):l(_l),r(_r),p(_pos){}
};
deque<dat> q;
long double ksm(long double a)
{
    a=a<0?-a:a;
    int b=P;
    long double ret=1;
    while(b)
    {
        if(b&1) ret*=a;
        a*=a;b>>=1;
    }
    return ret;
}
long double calc(int j,int i)
{
    return  f[j]+ksm(sum[i]-sum[j]+(i-j-1)-L);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(f,0,sizeof f);q.clear();
        scanf("%d%d%d",&n,&L,&P);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s[i]+1);
            sum[i]=sum[i-1]+strlen(s[i]+1);
        }
        q.push_back(dat(0,n,0));
        for(int i=1;i<=n;i++)
        {
            while(q.size()&&i>q.front().r) q.pop_front();
            f[i]=calc(q.front().p,i);
            lst[i]=q.front().p;
            if(!q.size()||calc(i,n)<=calc(q.back().p,n))
            {
                while(q.size()&&calc(q.back().p,q.back().l)>=calc(i,q.back().l)) q.pop_back();
                if(q.size())
                {
                    int L=q.back().l,R=q.back().r;
                    while(L<=R)
                    {
                        int mid=(L+R)>>1;
                        if(calc(q.back().p,mid)<calc(i,mid)) L=mid+1;
                        else R=mid-1;
                    }
                    dat tmp=q.back();q.pop_back();
                    q.push_back(dat(tmp.l,L-1,tmp.p));q.push_back(dat(L,n,i));
                }
                else q.push_back(dat(0,n,i));
            }
        }
        if(f[n]>1E18) puts("Too hard to arrange\n--------------------");
        else
        {
            printf("%lld\n",(ll)(f[n]+0.5));
            int tmp=n;
            while(tmp) nxt[lst[tmp]]=tmp,tmp=lst[tmp];
            while(tmp!=n)
            {
                for(int i=tmp+1;i<=nxt[tmp];i++)
                {
                    printf("%s",s[i]+1);
                    if(i!=nxt[tmp]) printf(" ");
                }
                puts("");
                tmp=nxt[tmp];
            }
            puts("--------------------");
        }
    }
}
