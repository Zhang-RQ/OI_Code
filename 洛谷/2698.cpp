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
int n,d,mx[1000100],mn[1000100],x,y,mxx;
deque<int> q1,q2;//Q1单增(min)  Q2单减(max)
bool check(int x)
{
    q1.clear();q2.clear();
    for(int i=1;i<=mxx;i++)
        if(mn[i]!=0x3f3f3f3f)
        {
            while(q1.size()&&i-q1.front()>x) q1.pop_front();
            while(q2.size()&&i-q2.front()>x) q2.pop_front();
            while(q1.size()&&mn[q1.back()]>=mn[i]) q1.pop_back();
            while(q2.size()&&mx[q2.back()]<=mx[i]) q2.pop_back();
            q1.push_back(i);q2.push_back(i);
            if(q1.size()&&q2.size()&&mx[q2.front()]-mn[q1.front()]>=d) return true;
        }
    return false;
}
int main()
{
    scanf("%d%d",&n,&d);
    memset(mn,0x3f,sizeof mn);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        mxx=max(mxx,x);
        mx[x]=max(mx[x],y);
        mn[x]=min(mn[x],y);
    }
    int L=1,R=1e9,ans=-1;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) ans=mid,R=mid-1;
        else L=mid+1;
    }
    printf("%d\n",ans);
}
