    #include<cstdio>
    #include<algorithm>
    #include<ext/pb_ds/assoc_container.hpp>
    #include<ext/pb_ds/tree_policy.hpp>
    using namespace std;
    typedef long long ll;
    typedef unsigned long long ull;
    using namespace __gnu_pbds;
    typedef pair<int,int> pii;
    typedef tree<pii,null_type,less<pii>,ov_tree_tag> pbds_set;
    pbds_set s[2];
    int n,b,P,x,tt;
    ll ans=0;
    ll ksm(ll a,ll b)
    {
        ll ret=1;
        while(b)
        {
            if(b&1) (ret*=a)%=P;
            (a*=a)%=P;
            b>>=1;
        }
        return ret%P;
    }
    int main()
    {
        scanf("%d%d%d",&n,&b,&P);
        scanf("%d",&x);
        ans=x+x;
        s[1].insert(make_pair(x,x));
        for(int i=2;i<=n;i++)
        {
            int now=i&1;
            scanf("%d",&x);
            s[now].clear();
            ans=max((ll)x+x,ans);
            s[now].insert(make_pair(x,x));
            for(pbds_set::iterator it=s[now^1].begin();it!=s[now^1].end();++it)
            {
                s[now].insert(make_pair(it->first&x,it->second|x));
                ans=max(ans,(ll)(it->first&x)+(it->second|x));
            }
        }
        printf("%lld\n",ksm(ans+233,b));
        return 0;
    }
