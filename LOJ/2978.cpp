#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E7+10;
const int P=998244353;

typedef bitset<501> dat;

map<int,int> mp;
vector<dat> st;
bool vis[MAXN];
int n,pr[MAXN],pc,minp[MAXN],lim,ID[MAXN];
dat b[501];

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

void sieve()
{
    for(int i=2;i<MAXN;i++)
    {
        if(!vis[i]) pr[++pc]=i,minp[i]=i,ID[i]=pc;
        for(int j=1;j<=pc&&i*pr[j]<MAXN;j++)
        {
            vis[i*pr[j]]=1;
            minp[i*pr[j]]=pr[j];
            if(!(i%pr[j])) break;
        }
    }
}

int Insert(dat a)
{
    for(int i=1;i<=500;i++)
        if(a[i])
        {
            if(b[i][i]) a^=b[i];
            else return b[i]=a,1;
        }
    return 0;
}

void solve()
{
    int L,R;
    scanf("%d%d",&L,&R);
    if(R-L<=6000)
    {
        lim=sqrt(R);
        int Ans=(L==1?2:1);L=max(L,2);
        st.clear();mp.clear();
        dat now;
        for(int i=1;i<=500;i++) b[i].reset();
        for(int i=L;i<=R;i++)
        {
            now.reset();
            int x=i,id=-1;
            while(x!=1)
            {
                int p=minp[x],c=0;
                while(!(x%p)) c^=1,x/=p;
                if(c)
                {
                    if(p>lim) id=ID[p];
                    else now[ID[p]]=1;
                }
            }
            if(id==-1) Ans=(Ans<<(!Insert(now)))%P;
            else
            {
                if(!mp.count(id))  mp[id]=st.size(),st.push_back(now);
                else Ans=(Ans<<(!Insert(now^st[mp[id]])))%P;
            }
        }
        printf("%d\n",Ans);
    }
    else
    {
        int cnt=0;
        for(int i=2;i<=R;i++) cnt+=(!vis[i])&&((L-1)/i<R/i);
        printf("%lld\n",ksm(2,R-L+1-cnt));
    }
}

int main()
{
    int T;
    for(scanf("%d",&T),sieve();T--;solve());
}