#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct Line{
    int l,r,id;

    bool operator < (const Line &rhs) const {return l<rhs.l;}
}a[MAXN*2],b[MAXN*2];

int n,m,cnt,id[MAXN];
int jmp[MAXN*2][21],L[MAXN];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,l,r;i<=n;i++)
    {
        scanf("%d%d",&l,&r);L[i]=l;
        if(l<=r) ++cnt,b[cnt]=(Line){l,r,cnt},id[i]=cnt,++cnt,b[cnt]={l+m,r+m,cnt};
        else ++cnt,b[cnt]=(Line){l,r+m,cnt},id[i]=cnt,++cnt,b[cnt]=(Line){l+m,2*m,cnt};
    }
    for(int i=1;i<=cnt;i++)
        a[i]=b[i];
    sort(b+1,b+1+cnt);
    int ptr=0;
    for(int i=1;i<=cnt;i++)
    {
        while(ptr<cnt&&b[i].r>=b[ptr+1].l)
            ++ptr;
        jmp[b[i].id][0]=b[ptr].id;
    }
    for(int j=1;j<=20;j++)
        for(int i=1;i<=cnt;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    for(int i=1;i<=n;i++)
    {
        int x=id[i],Ans=0;
        for(int j=20;~j;j--)
            if(a[jmp[x][j]].r<L[i]+m)
                x=jmp[x][j],Ans+=1<<j;
        printf("%d%c",Ans+2,"\n "[i!=n]);
    }
}
