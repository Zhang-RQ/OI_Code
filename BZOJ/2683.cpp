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
%:pragma GCC optimize(3)
%:pragma GCC optimize(2)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=500010;
namespace FastIO
{
	const int Bufsiz=1<<22;	// buffer size
	inline char get_c() {
		static char buf[Bufsiz];	// buffer
		static char *head = buf + Bufsiz;
		static char *tail = buf + Bufsiz;
		if (head == tail)	// at the end of buffer
			tail = buf + fread(head = buf, 1, BUFSIZ, stdin);	// reload from STDIN
		return *head++;
	}
	inline int get_i() {
		int res = 0;	// result
		int isn = 0; 	// is negative
		int chr = get_c();	// current char
		for (; chr < 48; chr = get_c())
			if (chr == '-')isn ^= 1;
		for (; chr > 47; chr = get_c())
			res = res * 10 + chr - 48;
		return isn ? -res : res;
	}
}
struct operation{
    int x,y,tp,w,id;  //tp==0 修改 tp==1 查询
    operation(){}
    operation(int _x,int _y,int _tp,int _w,int _id):x(_x),y(_y),tp(_tp),w(_w),id(_id){}
}opt[900000],tmp[900000];
int t[MAXN],ans[900000];
int n,ot,x1,y1,x2,y2,cnt,val,iii;
void add(int pos,int val)
{
    if(pos==0) return;
    for(int i=pos;i<=n;i+=i&-i)
        t[i]+=val;
}
int query(int pos)
{
    if(pos==0) return -1000000;
    int ret=0;
    for(int i=pos;i;i-=i&-i)
        ret+=t[i];
    return ret;
}
void clear(int pos)
{
    if(pos==0) return;
    for(int i=pos;i<=n;i+=i&-i)
        t[i]=0;
}
void CDQ(int L,int R)
{
    if(L==R) return;
    int mid=(L+R)>>1;
    CDQ(L,mid);CDQ(mid+1,R);
    int l=L,r=mid+1,ccnt=0;
    while(l<=mid&&r<=R)
    {
        if(opt[l].x<=opt[r].x)
        {
            if(!opt[l].tp) add(opt[l].y,opt[l].w);
            tmp[++ccnt]=opt[l++];
        }
        else
        {
            if(opt[r].tp) ans[opt[r].id]+=query(opt[r].y)*opt[r].w;
            tmp[++ccnt]=opt[r++];
        }
    }
    while(l<=mid) tmp[++ccnt]=opt[l++];
    while(r<=R)
    {
        if(opt[r].tp) ans[opt[r].id]+=query(opt[r].y)*opt[r].w;
        tmp[++ccnt]=opt[r++];
    }
    for(int i=L;i<=mid;i++)
        clear(opt[i].y);
    for(int i=1;i<=ccnt;i++)
        opt[L+i-1]=tmp[i];
}
int main()
{
    n=FastIO::get_i();
    n+=5;
    while((ot=FastIO::get_i())&&ot!=3)
    {
        x1=FastIO::get_i();
        y1=FastIO::get_i();
        x1++;y1++;
        if(ot==1) val=FastIO::get_i(),opt[++cnt]=operation(x1,y1,0,val,0);
        else if(ot==2) x2=FastIO::get_i(),y2=FastIO::get_i(),x2++,y2++,
            opt[++cnt]=operation(x2,y2,1,1,++iii),
            opt[++cnt]=operation(x1-1,y1-1,1,1,iii),
            opt[++cnt]=operation(x1-1,y2,1,-1,iii),
            opt[++cnt]=operation(x2,y1-1,1,-1,iii);
    }
    CDQ(1,cnt);
    for(int i=1;i<=iii;i++)
        printf("%d\n",ans[i]);
}
