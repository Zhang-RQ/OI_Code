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
    #include<ctime>
    using namespace std;
    typedef long long ll;
    typedef unsigned long long ull;
    #define get_val(l,r) sumv[r]-sumv[l-1]
    const int MAXN=100010;
    struct O{
        int l,r;
        bool operator < (O a)
        {
            return l<a.l;
        }
    }ot[MAXN];
    int t[MAXN<<2];
    inline void pushup(int x)
    {
        t[x]=t[x<<1]*(t[x<<1]==t[x<<1|1]);
    }
    inline void pushdown(int x,int l,int r)
    {
        if(!t[x])
            return;
        t[x<<1]=t[x<<1|1]=t[x];
    }
    inline void change(int x,int l,int r,int ql,int qr,int val)
    {
        if(ql>r||qr<l)
            return;
        if(ql<=l&&r<=qr){
            t[x]=val+1;
            return;
        }
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        if(ql<=mid)
            change(x<<1,l,mid,ql,qr,val);
        if(qr>=mid+1)
            change(x<<1|1,mid+1,r,ql,qr,val);
        pushup(x);
    }
    inline int query(int x,int l,int r,int pos)
    {
        //printf("%d %d %d %d\n",x,l,r,pos);
        if(t[x])
            return t[x]-1;
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        if(pos<=mid)
            return query(x<<1,l,mid,pos);
        else
            return query(x<<1|1,mid+1,r,pos);
    }
    char str[MAXN];
    ll Rank[MAXN],sa[MAXN];
    ll sum[MAXN],tp[MAXN];
    ll height[MAXN],h[MAXN];
    ll val[MAXN],sumv[MAXN];
    ll tmprank[MAXN],tot;
    int n;
    ll ans=0;
    void get_sa(int n)
    {
        int m=127;
        for(int i=1;i<=n;i++) Rank[i]=str[i],tp[i]=i;
        for(int i=0;i<=m;i++) sum[i]=0;
        for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
        int p=1;
        for(int len=1;p<n;len<<=1,m=p)
        {
            p=0;
            for(int i=n-len+1;i<=n;i++) tp[++p]=i;
            for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
            for(int i=0;i<=m;i++) sum[i]=0;  //Rank为第一关键字，tp为第二关键字
            for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
            for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
            for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
            swap(Rank,tp);Rank[sa[1]]=1;p=1;
            for(int i=2;i<=n;i++)
                Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
        }
        int lst=0,j;
        for(int i=1;i<=n;h[i]=lst,height[Rank[i++]]=lst)
            for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[j+lst]==str[i+lst];++lst);
    }
    ll get_rank(int lpos,int pos)
    {
        if(pos-lpos+1>height[Rank[lpos]]) return sum[n]-(sum[Rank[lpos]-1]+pos-lpos-height[Rank[lpos]]);
        else
        {
            //printf("rank:%d %d\n",lpos,pos);
            ll pre=query(1,1,n,pos-lpos+1);
            //printf("pre=%d tmprank=%d ret=%d\n",pre,tmprank[pre],tmprank[pre]+pre-(pos-lpos+1));
            return tmprank[pre]+pre-(pos-lpos+1);
        }
    }
    int tttt;
    int main()
    {
        scanf("%s",str+1);
        n=strlen(str+1);
        for(int i=1;i<=n;i++)
            scanf("%lld",&val[i]),sumv[i]=sumv[i-1]+val[i];
        get_sa(n);
        for(int i=1;i<=n;i++)
            sum[i]=n-sa[i]-height[i]+1+sum[i-1];
        for(int i=1;i<=n;i++) //枚举Rank
        {
            int L=sa[i],R=n,lpos=sa[i];
            //printf("i=%d lpos=%d\n",i,lpos);
            while(L<R)
            {
                int mid=(L+R)>>1;
                //printf("lpos=%d L=%d R=%d mid=%d\n",lpos,L,R,mid);
                if(get_val(lpos,mid)<get_rank(lpos,mid))
                    L=mid+1;
                else R=mid;
            }

            if(get_val(lpos,L)==get_rank(lpos,L))
                ot[++ans]={lpos,L};
            if(i!=n&&height[i]<height[i+1])
                tmprank[height[i]+1]=get_rank(sa[i],sa[i]+height[i]),
                change(1,1,n,height[i]+1,height[i+1],height[i]+1);
        }
        sort(ot+1,ot+1+ans);
        printf("%lld\n",ans);
        for(int i=1;i<=ans;i++)
            printf("%d %d\n",ot[i].l,ot[i].r);
    }
