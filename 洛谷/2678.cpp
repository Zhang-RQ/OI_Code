    #include<cstdio>
    #include<iostream>
    #include<cmath>
    #include<algorithm>
    #include<cstring>
    #include<vector>
    #include<map>
    #include<set>
    #include<queue>
    #include<stack>
    #include<bitset>
    using namespace std;
    typedef long long ll;
    int pos[50010];
    int l,m,n,la,tm;
    bool check(int x)
    {
        int cnt=0;
        int last=0;
        for(int i=1;i<=n;i++)
        {
            if(pos[i]-last>=x)
                last=pos[i];
            else cnt++;
        }
        if(cnt>m) return 0;
        else return 1;
    }
    int main()
    {
        ios::sync_with_stdio(0);
        cin>>l>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>pos[i];
        pos[++n]=l;
        int L=0,R=l;
        int ans;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check(mid)) L=mid+1,ans=mid;
            else R=mid-1;
        }
        printf("%d\n",ans);
    }
