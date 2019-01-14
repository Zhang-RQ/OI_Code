#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int MAXN=2010;
const ld EPS=1E-12;

struct dat{
    ld x;
    int y,z;
    
    dat(ld _x=0,int _y=0,int _z=0){x=_x;y=_y;z=_z;}
    dat operator + (const dat &rhs) const {return dat(x+rhs.x,y+rhs.y,z+rhs.z);}
    bool operator < (const dat &rhs) const {return x<rhs.x||(abs(x-rhs.x)<EPS&&y<rhs.y)||(abs(x-rhs.x)<EPS&&y==rhs.y&&z<rhs.z);} 
}f[MAXN];

int n,u,v;
ld a[MAXN],b[MAXN],Ans;

void solve(ld Mid1,ld Mid2)
{
    for(int i=1;i<=n;i++)
        f[i]=max({f[i-1],f[i-1]+dat(a[i]-Mid1,1,0),f[i-1]+dat(b[i]-Mid2,0,1),f[i-1]+dat(a[i]+b[i]-a[i]*b[i]-Mid1-Mid2,1,1)});
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>u>>v;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    ld L1=0,R1=1,L2=0,R2=1;
    for(int i=1;i<=60;i++)
    {
        ld Mid1=(L1+R1)*.5;
        L2=0,R2=1;
        for(int i=1;i<=60;i++)
        {
            ld Mid2=(L2+R2)*.5;
            solve(Mid1,Mid2);
            if(f[n].z<=v) R2=Mid2;
            else L2=Mid2;
        }
        solve(Mid1,R2);
        if(f[n].y<=u) R1=Mid1;
        else L1=Mid1;
    }
    solve(R1,R2);
    cout<<fixed<<setprecision(10)<<f[n].x+u*R1+v*R2<<endl;
}