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
const int MAXN=5E5+10;
int a[MAXN],n,head,tail;
double f[MAXN],g[MAXN];
double calc(int j,int i) {return a[j]+sqrt(fabs(j-i))-a[i];}
struct dat{
    int l,r,p;
    dat(){}
    dat(int _l,int _r,int _p):l(_l),r(_r),p(_p){}
}Q[MAXN];
int main()
{
    scanf("%d",&n);
    head=1;tail=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        Q[head].l++;
        if(head<=tail&&Q[head].r<Q[head].l) head++;
        if(head>tail||calc(Q[tail].p,n)<calc(i,n))
        {
            while(head<=tail&&calc(Q[tail].p,Q[tail].l)<calc(i,Q[tail].l)) tail--;
            if(head<=tail)
            {
                int L=Q[tail].l,R=Q[tail].r;
                while(L<=R)
                {
                    int mid=(L+R)>>1;
                    if(calc(Q[tail].p,mid)>calc(i,mid)) L=mid+1;
                    else R=mid-1;
                }
                dat tmp=Q[tail];tail--;
                Q[++tail]=dat(tmp.l,L-1,tmp.p);Q[++tail]=dat(L,n,i);
            }
            else Q[++tail]=dat(i,n,i);
        }
        f[i]=calc(Q[head].p,i);
    }
    reverse(a+1,a+1+n);
    head=1;tail=0;
    for(int i=1;i<=n;i++)
    {
        Q[head].l++;
        if(head<=tail&&Q[head].r<Q[head].l) head++;
        if(head>tail||calc(Q[tail].p,n)<calc(i,n))
        {
            while(head<=tail&&calc(Q[tail].p,Q[tail].l)<calc(i,Q[tail].l)) tail--;
            if(head<=tail)
            {
                int L=Q[tail].l,R=Q[tail].r;
                while(L<=R)
                {
                    int mid=(L+R)>>1;
                    if(calc(Q[tail].p,mid)>calc(i,mid)) L=mid+1;
                    else R=mid-1;
                }
                dat tmp=Q[tail];tail--;
                Q[++tail]=dat(tmp.l,L-1,tmp.p);Q[++tail]=dat(L,n,i);
            }
            else Q[++tail]=dat(i,n,i);
        }
        g[i]=calc(Q[head].p,i);
    }
    for(int i=1;i<=n;i++) printf("%d\n",(int)ceil(max(f[i],g[n-i+1])));
}
