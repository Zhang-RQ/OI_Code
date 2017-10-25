#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
const int MAXN=100010;
using namespace std;
long long hi[MAXN];
long long disa[MAXN],disb[MAXN];
long long disab[36][MAXN],disaa[36][MAXN],disbb[36][MAXN];
int stab[36][MAXN];int sta[MAXN],stb[MAXN];
int n,q;
struct da{
    long long he;
    int id;
}date[MAXN];

set<long long> s;
set<long long>::iterator it,it2;

bool comp(da x,da y){
    return x.he<y.he;
}

void cl(){
    memset(disaa,0,sizeof(disaa));
    memset(disbb,0,sizeof(disbb));
    memset(disab,0,sizeof(disab));
    memset(stab,0,sizeof(stab));
    memset(sta,0,sizeof(sta));
    memset(stb,0,sizeof(stb));
    memset(disa,0,sizeof(disa));
    memset(disb,0,sizeof(disb));
}

int main(){
    cl();
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>hi[i];
    for(int i=1;i<=n;i++) date[i].id=i,date[i].he=hi[i];
    sort(date+1,date+n+1,comp);
    for(int i=n;i>=1;i--){
        long long minn=100000000000000000,minn2=100000000000000000,he1=100000000000000000,he2=100000000000000000;
        s.insert(hi[i]);
        it=s.find(hi[i]);
        if(it!=s.begin()){
            it--;
            long long diss=abs(hi[i]-*it),gao=*it;
            if(diss<minn||(diss==minn&&gao<he1)) swap(gao,he1),swap(minn,diss);
            if((diss>minn&&diss<minn2)||(diss==minn&&gao>he1)) he2=gao,minn2=diss;
        }
        if(it!=s.begin()){
            it--;
            long long diss=abs(hi[i]-*it),gao=*it;
            if(diss<minn||(diss==minn&&gao<he1)) swap(gao,he1),swap(minn,diss);
            if((diss>minn&&diss<minn2)||(diss==minn&&gao>he1)) he2=gao,minn2=diss;
        }
        it=s.find(hi[i]);it2=s.end();
        it++;
        if(it!=it2){
            long long diss=abs(hi[i]-*it),gao=*it;
            if(diss<minn||(diss==minn&&gao<he1)) swap(gao,he1),swap(minn,diss);
            if((diss>minn&&diss<minn2)||(diss==minn&&gao>he1)) he2=gao,minn2=diss;
        }
        if(it!=it2){
            it++;
            if(it!=it2){
                long long diss=abs(hi[i]-*it),gao=*it;
                if(diss<minn||(diss==minn&&gao<he1)) swap(gao,he1),swap(minn,diss);
                if((diss>minn&&diss<minn2)||(diss==minn&&gao>he1)) he2=gao,minn2=diss;
            }
        }
        if(minn==100000000000000000) disb[i]=0;
        else disb[i]=minn;
        if(minn2==100000000000000000) disa[i]=0;
        else disa[i]=minn2;
        int ans=0,l=1,r=n,mid;
        while(l<=r){mid=(l+r)/2;if(date[mid].he>=he1) ans=date[mid].id,r=mid-1;else l=mid+1;}
        if(ans==0) stb[i]=0;
        else stb[i]=ans;
        ans=0,l=1,r=n;
        while(l<=r){mid=(l+r)/2;if(date[mid].he>=he2) ans=date[mid].id,r=mid-1;else l=mid+1;}
        if(ans==0) sta[i]=0;
        else sta[i]=ans;
    }
    for(int i=1;i<=n;i++){
        if(!disa[i]||!disb[sta[i]]) continue;
        disab[0][i]=disa[i]+disb[sta[i]];
        disaa[0][i]=disa[i],disbb[0][i]=disb[sta[i]];
        stab[0][i]=stb[sta[i]];
    }
    for(int j=1;j<=35;j++){
        for(int i=1;i<=n;i++){
            if(!disab[j-1][i]||!disab[j-1][stab[j-1][i]]) continue;
            disab[j][i]=disab[j-1][i]+disab[j-1][stab[j-1][i]];
            disaa[j][i]=disaa[j-1][i]+disaa[j-1][stab[j-1][i]];
            disbb[j][i]=disbb[j-1][i]+disbb[j-1][stab[j-1][i]];
            stab[j][i]=stab[j-1][stab[j-1][i]];
        }
    }
    int x0,ans=0;
    double minn=1<<30;scanf("%d",&x0);
    for(int i=1;i<=n;i++){
        int tota=0,totb=0,tot=0,now=i;
        for(int j=35;j>=0;j--){
            if(stab[j][now]&&tot+disab[j][now]<=x0)
            tot+=disab[j][now],tota+=disaa[j][now],totb+=disbb[j][now],now=stab[j][now];
        }
        if(sta[now]&&tot+disa[now]<=x0) tot+=disa[now],tota+=disa[now],now=sta[now];
        double zhi=double(tota)/double(totb);
        if(minn>zhi) minn=zhi,ans=i;
    }
    printf("%d\n",ans);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int star,x;
        scanf("%d%d",&star,&x);
        int tota=0,totb=0,tot=0,now=star;
        for(int j=35;j>=0;j--){
            if(stab[j][now]&&tot+disab[j][now]<=x)
            tot+=disab[j][now],tota+=disaa[j][now],totb+=disbb[j][now],now=stab[j][now];
        }
        if(sta[now]&&tot+disa[now]<=x) tot+=disa[now],tota+=disa[now],now=sta[now];
        printf("%d %d\n",tota,totb);
    }
    return 0;
}
/*#include<cstdio>
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
#define MAXN 100010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int des[MAXN][20],dis[MAXN][20][2],lg2[MAXN];
int destination[MAXN][2];
int n,x0,m,tx;
ll tc;
struct node{
    int h,id;
    bool operator < (const node &a) const
    {
        if(h!=a.h) return h<a.h;
        return id<a.id;
    }
    node(){}
    node(int h,int id):h(h),id(id){}
}city[MAXN];
struct Node{
    int id,dis,h;
    Node(){}
    Node(int id,int dis,int h):id(id),dis(dis),h(h){}
    bool operator < (const Node &a)const
    {
        if(dis!=a.dis) return dis<a.dis;
        else return h<a.h;
    }
};
set<node> s;
void getdes()
{
    set<node>::iterator it1;
    set<node>::iterator it2;
    vector<Node> v;
    for(int i=n;i>=1;i--)
    {
        v.clear();
        s.insert(city[i]);
        it1=it2=s.find(city[i]);
        if(++it2!=s.end())
        {
            v.push_back(Node(it2->id,abs(it2->h-city[i].h),it2->h));
            if(++it2!=s.end())
                v.push_back(Node(it2->id,abs(it2->h-city[i].h),it2->h));
        }
        if(it1!=s.begin())
        {
            --it1,v.push_back(Node(it1->id,abs(it1->h-city[i].h),it1->h));
            if(it1!=s.begin())
                --it1,v.push_back(Node(it1->id,abs(it1->h-city[i].h),it1->h));
        }
        if(v.size()>=2)
        {
            sort(v.begin(),v.end());
            destination[i][1]=v[0].id;
            destination[i][0]=v[1].id;
        }
        else if(v.size()==1)
        {
            destination[i][1]=v[0].id;
            destination[i][0]=-1;
        }
        else destination[i][1]=destination[i][0]=-1;
    }
    return;
}
void init()
{
    for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
    for(int i=1;i<=n;i++)
    {
        if(destination[i][0]!=-1&&destination[destination[i][0]][1]!=-1)
        {
            des[i][0]=destination[destination[i][0]][1];
            dis[i][0][0]=abs(city[i].h-city[destination[i][0]].h);
            dis[i][0][1]=abs(city[destination[i][0]].h-city[des[i][0]].h);
        }
        else des[i][0]=-1;
    }
}
void work()
{
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
        {
            if(des[i][j-1]!=-1)
                des[i][j]=des[des[i][j-1]][j-1];
            else
                des[i][j]=-1;
            if(des[i][j]!=-1)
                dis[i][j][0]=dis[i][j-1][0]+dis[des[i][j-1]][j-1][0],
                dis[i][j][1]=dis[i][j-1][1]+dis[des[i][j-1]][j-1][1];
        }
}
pair<ll,ll> jump(int s,ll x)
{
    int pos=s;
    ll disa=0,disb=0;
    for(int i=lg2[n];i>=0;i--)
    {
        if(des[pos][i]!=-1&&dis[pos][i][0]+dis[pos][i][1]<=x)
        {
            disa+=dis[pos][i][0];
            disb+=dis[pos][i][1];
            x-=(dis[pos][i][0]+dis[pos][i][1]);
            pos=des[pos][i];
        }
    }
    if(destination[pos][0]!=-1&&x>=abs(city[pos].h-city[destination[pos][0]].h))
        disa+=abs(city[pos].h-city[destination[pos][0]].h);
    return make_pair(disa,disb);
}
int main()
{
    memset(destination,-1,sizeof(destination));
    memset(des,-1,sizeof(des));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&city[i].h),city[i].id=i;
    getdes();
    init();
    work();
    scanf("%d",&x0);
    pair<ll,ll> ret;
    double ans=10000000,tmp=0;
    int anss=0;
    for(int i=1;i<=n;i++)
    {
        ret=jump(i,x0);
        if(ret.second!=0)   tmp=ret.first*1.0/ret.second;
        if(tmp<ans)
        {
            anss=i;
            ans=tmp;
        }
    }
    if(fabs(ans-10000000)<1e-6) printf("%d\n",(--s.end())->id);
    else printf("%d\n",anss);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%lld",&tx,&tc);
        ret=jump(tc,tx);
        printf("%lld %lld\n",ret.first,ret.second);
    }
}
*/
