#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E5+10;

struct T{
    int a,b,c;

    bool operator < (const T &rhs) const {return a<rhs.a;}
}c[MAXN];

int n,p,q,r,mxs[MAXN];
ll pre[MAXN],Ans;

int main()
{
    scanf("%d%d%d%d",&n,&p,&q,&r);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&c[i].a,&c[i].b,&c[i].c),mxs[c[i].b]=max(mxs[c[i].b],c[i].c);
    for(int i=q;i;i--) mxs[i]=max(mxs[i],mxs[i+1]);
    for(int i=1;i<=q;i++) pre[i]=pre[i-1]+mxs[i];
    sort(c+1,c+1+n);
    for(int i=p,k=q,ptr=n,mxc=0,mxb=0;i;i--)
    {
        while(ptr&&c[ptr].a>=i) mxc=max(mxc,c[ptr].c),mxb=max(mxb,c[ptr].b),--ptr;
        while(k&&mxs[k]<=mxc) --k;
        Ans+=1ll*(q-mxb)*r;
        if(k>=mxb) Ans-=pre[k]-pre[mxb]+1ll*(q-k)*mxc;
        else Ans-=1ll*(q-mxb)*mxc;
    }
    printf("%lld\n",Ans);
}
