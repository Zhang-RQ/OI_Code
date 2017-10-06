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
int size;
struct node1{
    int l,r,time,id;
    node1(){}
    node1(int L,int R,int TIME,int ID):l(L),r(R),time(TIME),id(ID){}
    friend bool operator < (const node1 &a,const node1 &b)
    {
        if(a.l/size!=b.l/size) return a.l/size<b.l/size;
        else if(a.r/size!=b.r/size) return a.r/size<b.r/size;
        else return a.time<b.time;
    }
}query[10000];
struct node2{
    int val,pos;
    int last;
    node2(){}
    node2(int POS,int VAL,int LAST):val(VAL),pos(POS),last(LAST){}
}change[1010];
int cntq=0,cntc=0;
int ans[10000];
int arr[10010];
int arr_[10010];
int cnt[1000010];
int n,m,t1,t2,curL=1,curR=0,cur=0,L,R;
char ops[2];
int answer=0;
void add(int pos)
{
    if((++cnt[arr[pos]])==1) answer++;
}
void del(int pos)
{
    if((--cnt[arr[pos]])==0) answer--;
}
void cg(int pos,int val,int _val) //_val(val_old)
{
    if(pos<=curR&&pos>=curL&&(--cnt[_val])==0)
            answer--;
    if(pos<=curR&&pos>=curL&&(++cnt[val])==1)
            answer++;
    arr[pos]=val;
}

int main()
{
    scanf("%d%d",&n,&m);
    size=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]),arr_[i]=arr[i];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ops);
        scanf("%d%d",&t1,&t2);
        if(ops[0]=='Q') ++cntq,query[cntq]=node1(t1,t2,cntc,cntq);
        else change[++cntc]=node2(t1,t2,arr_[t1]),arr_[t1]=t2;
    }
    sort(query+1,query+1+cntq);
    for(int i=1;i<=cntq;i++)
    {
        int L=query[i].l;
        int R=query[i].r;
        while(cur<query[i].time)
            cur++,cg(change[cur].pos,change[cur].val,change[cur].last);
        while(cur>query[i].time)
            cg(change[cur].pos,change[cur].last,change[cur].val),cur--;
        while(curL>L)
            add(--curL);
        while(curL<L)
            del(curL++);
        while(curR>R)
            del(curR--);
        while(curR<R)
            add(++curR);
        ans[query[i].id]=answer;
    }
    for(int i=1;i<=cntq;i++)    printf("%d\n",ans[i]);
}
