#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;

const int MAXN=2E5+10;
const double PI=acos(-1);

int n;
ll Ans,X[MAXN<<1],Y[MAXN<<1];
struct __node{
    int x,y;double a;
    friend bool operator < (const __node &lhs,const __node &rhs){return lhs.a<rhs.a;}
}P[MAXN<<1];
 
inline void update(const int &L,const int &R){if(L<=R)Ans=max(Ans,1ll*(X[R]-X[L-1])*(X[R]-X[L-1])+1ll*(Y[R]-Y[L-1])*(Y[R]-Y[L-1]));}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&P[i].x,&P[i].y);
        P[i].a=atan2(P[i].x,P[i].y);P[i+n]=P[i];
        P[i+n].a+=2*PI;
    }
    sort(P+1,P+1+2*n);
    for(int i=1;i<=2*n;i++) X[i]=X[i-1]+P[i].x,Y[i]=Y[i-1]+P[i].y;
    int L=1,R=1;
    for(;R<=2*n;R++)
    {
        for(;L<R&&P[L].a<=P[R].a-PI;L++,update(L,R-1));
        update(L,R);
    }
    for(;L<=2*n;update(L,2*n),L++);
    printf("%lld\n",Ans);
}
