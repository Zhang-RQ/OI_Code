#include<bits/stdc++.h>

using namespace std;

const int MAXN=5E4+10;
const int INF=0x7fffffff;

int fa[MAXN],val[MAXN],n,K,tot,f[MAXN][101],Ans,Cs;

double Gx;

struct Circle{
    int x,y,r;
}cir[MAXN];

double get_ins(int id,int ty)
{
    double t=sqrt(1.0*cir[id].r*cir[id].r-(1.0*Gx-cir[id].x)*(1.0*Gx-cir[id].x));
    return ty?cir[id].y+t:cir[id].y-t;
}

struct Pnt{
    int id,tp;//tp=0 down tp=1 up
    Pnt(){}
    Pnt(int _,int __){id=_;tp=__;}
    bool operator < (const Pnt &rhs) const
    {
        if(id!=rhs.id) return get_ins(id,tp)<get_ins(rhs.id,rhs.tp);
        else return tp<rhs.tp;
    }
};

struct OP{
    int x,id,tp;//tp=0 appear,tp=1 disappear
    OP(){}
    OP(int _,int __,int ___){x=_;id=__;tp=___;}
    bool operator < (const OP &rhs) const {return x<rhs.x||(x==rhs.x&&id<rhs.id);}
}opr[MAXN<<1];

set<Pnt> s;
set<Pnt>::iterator it;

void solve()
{
    scanf("%d%d",&n,&K);
    memset(fa,0,sizeof fa);
    tot=Ans=0;
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",&cir[i].x,&cir[i].y,&cir[i].r,&val[i]);
    for(int i=1;i<=n;i++)
        opr[++tot]=OP(cir[i].x-cir[i].r,i,0),opr[++tot]=OP(cir[i].x+cir[i].r,i,1);
    sort(opr+1,opr+1+tot);
    for(int i=1;i<=tot;i++)
    {
        Gx=opr[i].x;
        if(!opr[i].tp)
        {
            it=s.insert(Pnt(opr[i].id,1)).first;
            if(it==s.begin()) fa[opr[i].id]=0;
            else
            {
                --it;
                if(it->tp) fa[opr[i].id]=fa[it->id];
                else fa[opr[i].id]=it->id;
            }
            s.insert(Pnt(opr[i].id,0));
        }
        else s.erase(Pnt(opr[i].id,1)),s.erase(Pnt(opr[i].id,0));
    }
    f[0][0]=INF;
    for(int i=1;i<=n;i++) f[i][0]=val[i];
    for(int j=1;j<=K;j++)
    {
        for(int i=0;i<=n;i++) f[i][j]=f[i][j-1];
        for(int i=1;i<=n;i++)
        {
            f[i][j]=min(f[i][j],f[fa[i]][j-1]);
            f[fa[i]][j]=min(f[fa[i]][j],f[i][j-1]);
        }
    }
    for(int i=1;i<=n;i++) Ans=max(Ans,val[i]-f[i][K]);
    printf("Case %d: %d\n",++Cs,Ans);
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
}
