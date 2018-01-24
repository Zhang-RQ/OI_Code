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
vector<string> v;
int val[1010],sum[1010];
int n,tsum;
char str[1010],tt[1010];
string tmp;
struct node{
    int l,r;
    bool operator <(node a)
    {
        return l<a.l;
    }
}output[1010];
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]),sum[i]=sum[i-1]+val[i];
    for(int i=1;i<=n;i++)
    {
        memset(tt,0,sizeof tt);
        for(int j=0;j<=n-i;j++)
            tt[j]=str[i+j],
            v.push_back(string(tt));
    }
    sort(v.begin(),v.end());
    int cnt=unique(v.begin(),v.end())-v.begin();
    int ans=0;
    //for(int i=0;i<cnt;i++)
    //    cout<<i+1<<":"<<v[i]<<endl;
    for(int i=1;i<=n;i++)
    {
        memset(tt,0,sizeof tt);
        for(int j=0;j<=n-i;j++)
        {
            tt[j]=str[i+j];
            int Rk=cnt-(lower_bound(v.begin(),v.begin()+cnt,string(tt))-v.begin());
            if(Rk==sum[i+j]-sum[i-1])
                output[++ans].l=i,output[ans].r=i+j;
        }
    }
    sort(output+1,output+1+ans);
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++)
        printf("%d %d\n",output[i].l,output[i].r);
}
