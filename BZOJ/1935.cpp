#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
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
const int MAXN=500010;
const int MAXM=500010<<2;
struct operation{
    int tp,x,y,w,id; //tp=1 修改 tp=2 查询
    operation(){}
    operation(int _tp,int _x,int _y,int _w,int _id):tp(_tp),x(_x),y(_y),w(_w),id(_id){}
}opt[MAXN+MAXM],tmp[MAXN+MAXM];
int ans[MAXM],n,m,cnt,x1,y1,x2,y2,maxy;
int t[10000010];
void add(int pos,int val)
{
    for(int i=pos;i<=maxy;i+=i&(-i))
        t[i]+=val;
}
int query(int pos)
{
    int ret=0;
    for(int i=pos;i;i-=i&(-i))
        ret+=t[i];
    return ret;
}
void CDQ(int L,int R)
{
    if(L==R) return;
    int mid=(L+R)>>1;
    CDQ(L,mid);CDQ(mid+1,R);
    int cntt=0,l=L,r=mid+1;
    while(l<=mid&&r<=R)
    {
        if(opt[l].x<=opt[r].x)
        {
            if(opt[l].tp==1) add(opt[l].y,1);
            tmp[++cntt]=opt[l++];
        }
        else
        {
            if(opt[r].tp==2) ans[opt[r].id]+=opt[r].w*query(opt[r].y);
            tmp[++cntt]=opt[r++];
        }
    }
    while(l<=mid)
    {
        if(opt[l].tp==1) add(opt[l].y,1);
        tmp[++cntt]=opt[l++];
    }
    while(r<=R)
    {
        if(opt[r].tp==2) ans[opt[r].id]+=opt[r].w*query(opt[r].y);
        tmp[++cntt]=opt[r++];
    }
    for(int i=L;i<=mid;i++) if(opt[i].tp==1) add(opt[i].y,-1);
    for(int i=1;i<=cntt;i++) opt[L+i-1]=tmp[i];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&x1,&y1),x1++,y1++,opt[++cnt]=operation(1,x1,y1,0,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);x1++,y1++,x2++,y2++;
        maxy=max(y2,maxy);maxy=max(y1,maxy);
        opt[++cnt]=operation(2,x2,y2,1,i);
        opt[++cnt]=operation(2,x1-1,y1-1,1,i);
        opt[++cnt]=operation(2,x1-1,y2,-1,i);
        opt[++cnt]=operation(2,y1-1,x2,-1,i);
    }
    CDQ(1,cnt);
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}
