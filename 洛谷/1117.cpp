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
typedef unsigned long long ull;
const int MAXN=50010;
template <int MN>
    class SuffixArray{
    public:
        int tp[MN],sa[MN],Rank[MN],height[MN];
        int st[MN][20],lg2[MN],sum[MN];
    public:
        inline void get_sa(char *str,int n)
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
                for(int i=0;i<=m;i++) sum[i]=0;
                for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
                for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
                for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
                swap(Rank,tp);
                Rank[sa[1]]=1;
                p=1;
                for(int i=2;i<=n;i++)
                    Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
            }
            int lst=0,j;
            for(int i=1;i<=n;height[Rank[i++]]=lst)
                for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[i+lst]==str[j+lst];lst++);
        }
        inline void get_st(int n)
        {
            for(int i=2;i<=n;i++)
                lg2[i]=lg2[i>>1]+1;
            for(int i=1;i<=n;i++)
                st[i][0]=height[i];
            for(int j=1;j<=lg2[n];j++)
                for(int i=1;i<=n;i++)
                    st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
        inline int query(int l,int r)
        {
            l=Rank[l];r=Rank[r];
            if(l>r) swap(l,r);
            l+=1,r+=1;
            //printf("%d %d\n",l,r);
            int len=lg2[r-l];
            return min(st[l][len],st[r-(1<<len)][len]);
        }
    };
SuffixArray<MAXN> SA,rSA;
int n,pre[MAXN],lst[MAXN],T,x,y,l,r;
char str[MAXN];
ll ans=0;
inline int LCP(int pos1,int pos2)
{
    return SA.query(pos1,pos2);
}
inline int LCS(int pos1,int pos2)
{
    return rSA.query(n-pos1+1,n-pos2+1);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(&SA,0,sizeof SA);
        memset(&rSA,0,sizeof rSA);
        memset(pre,0,sizeof pre);
        memset(lst,0,sizeof lst);
        ans=0;
        scanf("%s",str+1);
        n=strlen(str+1);//printf("%d\n",n);
        //puts(str+1);
        SA.get_sa(str,n);
        SA.get_st(n);
        reverse(str+1,str+1+n);
        rSA.get_sa(str,n);
        rSA.get_st(n);
        reverse(str+1,str+1+n);
        //for(int i=1;i<=n;i++)
        //    printf("%d ",SA.height[i]);
        //puts("");
        for(int len=1;(len<<1)<=n;len++)
        {
            for(int i=1,j=len+1;j<=n;i+=len,j+=len)
                if(str[i]==str[j])
                {
                    x=LCS(i,j);y=LCP(i,j);
                    l=max(i-x+len,i),r=min(i+y,j);
                    if(r-l>=1)
                    {
                        pre[l+len]+=1;  //i+len+x-(x+y-len)-1=i+2*len-y-1
                        pre[r+len]-=1; //i+len+x-1 +1=i+len+x
                        lst[l-len+1]+=1;
                        lst[r-len+1]-=1; //i-y+1+(x+y-len) +1=i+x-len+1
                    }
                }
        }
        pre[0]=lst[0]=0;
        for(int i=1;i<=n;i++)
            pre[i]+=pre[i-1],lst[i]+=lst[i-1]/*,printf("%d %d\n",pre[i],lst[i])*/;
        for(int i=1;i<n;i++)
            ans+=1LL*pre[i]*lst[i+1];
        printf("%lld\n",ans);
    }
}
