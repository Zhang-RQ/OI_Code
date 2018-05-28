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
#include<cassert>
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=500010;
struct Linear_Base{
    uint b[32];
    Linear_Base(){memset(b,0,sizeof b);}
    inline uint& operator [] (int i) {return b[i];}
    inline const uint& operator [] (int i) const {return b[i];}
    void insert(uint val)
    {
        for(int i=31;~i;i--)
            if((val>>i)&1)
            {
                if(b[i]) val^=b[i];
                else
                {
                    b[i]=val;break;
                }
            }
    }
}ey;
struct node{
    vector<int> v;
    inline const int& operator [] (int i) const {return v[i];}
}t[MAXN<<2];
int n;
map<int,int> mp;
Linear_Base merge(const Linear_Base &lhs,const Linear_Base &rhs)
{
    Linear_Base ret=lhs;
    for(int i=31;~i;i--)
        ret.insert(rhs[i]);
    return ret;
}
void insert(int x,int l,int r,int cl,int cr,uint val)
{
    if(cl<=l&&r<=cr) {t[x].v.push_back(val);return;}
    int mid=(l+r)>>1;
    if(cl<=mid) insert(x<<1,l,mid,cl,cr,val);
    if(cr>mid)  insert(x<<1|1,mid+1,r,cl,cr,val);
}
void calc(int x,int l,int r,const Linear_Base &lst)
{
    Linear_Base tmp=lst;
    for(int i=0;i<t[x].v.size();i++)
        tmp.insert(t[x][i]);
    if(l==r)
    {
        uint ans=0;
        for(int i=31;~i;i--)
            if((ans^tmp[i])>ans) ans=ans^tmp[i];
        return printf("%u\n",ans),void();
    }
    int mid=(l+r)>>1;
    calc(x<<1,l,mid,tmp);calc(x<<1|1,mid+1,r,tmp);
}
int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        if(x>0) mp[x]=i;
        else x=-x,insert(1,1,n,mp[x],i-1,x),mp.erase(x);
    }
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++)
        insert(1,1,n,it->second,n,it->first);
    calc(1,1,n,ey);
    #ifdef LOCAL
        system("pause");
    #endif
}