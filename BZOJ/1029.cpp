#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
struct node{
    int id,t1,t2;
    friend bool operator < (node a,node b)
    {
        return a.t1<b.t1;
    }
}A[150010];
inline bool cmp(node a,node b)
{
    return a.t2<b.t2;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&A[i].t1,&A[i].t2),A[i].id=i;
    sort(A+1,A+1+n,cmp);
    int now=0,ans=0;
    priority_queue<node> q;
    for(int i=1;i<=n;i++)
    {
        if(now+A[i].t1<=A[i].t2)
        {
            now+=A[i].t1;
            ans++;
            q.push(A[i]);
        }else if(!q.empty()){
            node tmp=q.top();
            if(tmp.t1>A[i].t1&&A[i].t1+now-tmp.t1<=A[i].t2){
                q.pop();
                now-=tmp.t1;
                now+=A[i].t1;
                q.push(A[i]);
            }
        }
    }
    printf("%d\n",ans);
}
