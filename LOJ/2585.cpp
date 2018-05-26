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
#include<ctime>
#define IL __attribute__((always_inline)) inline
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=6E5+10;
const int INF=1<<30;
char B[1<<26],*S=B;int F()
{
    for(;*S<'-';S++);
    int x=*S++-'0';
    for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');
    return x;
}
int n,k,q,tots,ans[MAXN],tims[MAXN+(MAXN>>1)],cntt,rev[MAXN];
set<pair<int,int> > s[MAXN>>1];
struct shp{
    int x,tp,t,f,id; // x ,tp=type,t=time,f=flag
    shp(){}
    IL shp(const int &_,const int &__,const int &___,const int &____,const int &_____){x=_;tp=__;t=___;f=____;id=_____;}
    IL bool operator < (const shp &rhs) const
    {
        if(t!=rhs.t) return t<rhs.t;
        else return f>rhs.f;
    }
}shop[MAXN+(MAXN>>1)];
struct Query{
    int x,t,id;
    Query(){}
    IL Query(const int &_,const int &__,const int &___){x=_;t=__;id=___;}
    IL bool operator < (const Query &rhs) const 
    {
       if(t!=rhs.t) return t<rhs.t;
       return id<rhs.id;
    }
}Q[MAXN>>1];
namespace Splay{
    struct node{
        int son[2],fa;
        int mn,val;
        ll key;
        void clear(){son[0]=son[1]=fa=key=val=0;mn=INF;}
    }t[MAXN];
    int rt,cnt;
    #define ls(x) t[x].son[0]
    #define rs(x) t[x].son[1]
    #define fa(x) t[x].fa
    #define rson(x) (rs(fa(x))==x)
    IL void pushup(const int &x) {t[x].mn=min(t[x].val,min(t[ls(x)].mn,t[rs(x)].mn));}
    IL void rotate(const int &x)
    {
        int y=fa(x),z=fa(y);
        bool rsx=rson(x),rsy=rson(y);
        if(z) t[z].son[rsy]=x;
        else rt=x;
        t[y].son[rsx]=t[x].son[!rsx];
        t[x].son[!rsx]=y;
        fa(y)=x;fa(x)=z;
        fa(t[y].son[rsx])=y;
        pushup(y);pushup(x);
    }
    IL void splay(const int &x,int pos=0) // x,pos are node_num
    {
        while(fa(x)!=pos)
        {
            if(fa(fa(x))!=pos) rotate(rson(x)==rson(fa(x))?fa(x):x);
            rotate(x);
        }
    }
    IL int find(const ll &key,const bool &flg) //find key value
    {
        int x=rt;
        while(t[x].key!=key)
        {
            if(t[x].key>key)
            {
                if(ls(x)) x=ls(x);
                else break;
            }
            else
            {
                if(rs(x)) x=rs(x);
                else break;
            }
        }
        if(flg) splay(x);
        return x;
    }
    IL int pred(const int &x) // x is node_num
    {
        splay(x);
        int y=ls(rt);
        if(!y) return -1;
        while(rs(y)) y=rs(y);
        return y;
    }
    IL int succ(const int &x) // x is node_num
    {
        splay(x);
        int y=rs(rt);
        if(!y) return -1;
        while(ls(y)) y=ls(y);
        return y;
    }
    IL int get_range(const int &l,const int &r) // l,r are node_num
    {
        if(t[l].key>t[r].key) return -1;
        int _l=pred(l),_r=succ(r);
        if(_l==-1&&_r==-1) return rt;
        if(_l==-1) {splay(_r);return ls(rt);}
        if(_r==-1) {splay(_l);return rs(rt);}
        splay(_l);splay(_r,_l);
        return ls(rs(rt));
    }
    IL int lower_bound(const ll &key) // return the node_num,大于等于key的最小的点
    {
        int x=find(key,1);
        if(t[x].key>=key) return x;
        return succ(x);
    }
    IL int upper_bound(const ll &key) // return the node_num,小于等于key的最大的点
    {
        int x=find(key,1);
        if(t[x].key<=key) return x;
        return pred(x);
    }
    IL int query(const ll &l,const ll &r) //ask min_val in [l,r] (key_value)
    {
        if(l>r) return -1;
        int L=lower_bound(l),R=upper_bound(r);
        if(L==-1||R==-1) return -1;
        int rg=get_range(L,R);
        if(rg==-1) return -1;
        return t[rg].mn;
    }
    IL void insert(const ll &key,const int &val)
    {
        if(!rt)
        {
            rt=cnt=1;t[cnt].clear();
            t[cnt].key=key;
            t[cnt].val=t[cnt].mn=val;
            return;
        }
        int x=find(key,0);
        t[++cnt].fa=x;
        t[cnt].key=key;
        t[cnt].val=t[cnt].mn=val;
        t[x].son[key>t[x].key]=cnt;
        splay(cnt);
    }
    IL void remove(const ll &key)
    {
        int x=find(key,1);
        if(t[x].key!=key) return;
        splay(x);
        if(!ls(x))
        {
            rt=rs(x);t[rs(x)].fa=0;
            t[x].clear();
            return;
        }
        int tx=ls(x),ttx=pred(x);
        ls(x)=fa(tx)=0;
        splay(ttx);
        rs(ttx)=rs(x);
        fa(rs(x))=ttx;
        pushup(ttx);
        t[x].clear();
        rt=ttx;
    }
    IL void change(const ll &key,const int &val)
    {
        int x=find(key,1);
        t[x].mn=t[x].val=val;
        pushup(x);
    }
}
int main()
{
    fread(B,1,1<<25,stdin);
    Splay::t[0].mn=INF;
    n=F();k=F();q=F();
    // scanf("%d%d%d",&n,&k,&q);
    for(int i=1,x,t,a,b;i<=n;i++)
    {
        x=F();t=F();a=F();b=F();
        // scanf("%d%d%d%d",&x,&t,&a,&b);
        rev[i]=x;
        shop[++tots]=shp(x,t,a,1,i);shop[++tots]=shp(x,t,b,-1,i);
        tims[++cntt]=a;tims[++cntt]=b;
    }
    for(int i=1;i<=q;i++)
    {
        Q[i].x=F();Q[i].t=F();
        // scanf("%d%d",&Q[i].x,&Q[i].t);
        Q[i].id=i;
        tims[++cntt]=Q[i].t;
    }
    sort(tims+1,tims+1+cntt);
    cntt=unique(tims+1,tims+1+cntt)-tims-1;
    for(int i=1;i<=tots;i++) shop[i].t=lower_bound(tims+1,tims+1+cntt,shop[i].t)-tims;
    for(int i=1;i<=q;i++) Q[i].t=lower_bound(tims+1,tims+1+cntt,Q[i].t)-tims;
    for(int i=1;i<=k;i++) s[i].insert(make_pair(-INF,-1)),s[i].insert(make_pair(INF,-1)),Splay::insert(INF*300000ll+i,-INF);
    sort(shop+1,shop+1+tots);sort(Q+1,Q+1+q);
    int nows=0,l,r,_ans,mid,Que; // done
    set<pair<int,int> >::iterator it,it2;
    for(int i=1;i<=q;i++)
    {
        while(nows+1<=tots&&(shop[nows+1].t<Q[i].t||(shop[nows+1].t==Q[i].t&&shop[nows+1].f==1)))
        {
            nows++;
            if(shop[nows].f==1)
            {
                it=it2=s[shop[nows].tp].lower_bound(make_pair(shop[nows].x,shop[nows].id));
                --it;
                Splay::insert(shop[nows].x*300000ll+shop[nows].id,it->first);
                if(it2->second==-1) Splay::change(INF*300000ll+shop[nows].tp,shop[nows].x);
                else Splay::change(rev[it2->second]*300000ll+it2->second,shop[nows].x);
                s[shop[nows].tp].insert(make_pair(shop[nows].x,shop[nows].id));
            }
            else
            {
                it=it2=s[shop[nows].tp].lower_bound(make_pair(shop[nows].x,shop[nows].id));
                --it;++it2;
                Splay::remove(shop[nows].x*300000ll+shop[nows].id);
                if(it2->second==-1) Splay::change(INF*300000ll+shop[nows].tp,it->first);
                else Splay::change(rev[it2->second]*300000ll+it2->second,it->first);
                ++it;
                s[shop[nows].tp].erase(it);
            }
        }
        l=0,r=100000000,_ans=-1;
        while(l<=r)
        {
            mid=(l+r)>>1,Que=Splay::query((Q[i].x+mid+1)*300000ll,INF*350000ll);
            if(Que!=-INF&&Que>=Q[i].x-mid) r=mid-1,_ans=mid;
            else l=mid+1;
        }
        if(_ans!=-1) ans[Q[i].id]=_ans;
        else ans[Q[i].id]=-1;
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}