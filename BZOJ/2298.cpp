#include<bits/stdc++.h>

using namespace std;

const int MAXN=1E5+10;

struct line{
    int l,r,val;
    bool operator == (const line &rhs) const {return l==rhs.l&&r==rhs.r;}
    bool operator < (const line &rhs) const {return r<rhs.r||(r==rhs.r&&l<rhs.l);}
}l1[MAXN],l[MAXN];

vector<line> v[MAXN];
int n,tot,f[MAXN],cnt;

int main()
{
    scanf("%d",&n);
    for(int i=1,a,b;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        if(a+1>n-b) continue;
        l1[++cnt].l=a+1;l1[cnt].r=n-b;l1[cnt].val=1;
    }
    sort(l1+1,l1+1+cnt);
    for(int i=1;i<=cnt;i++)
    {
        if(l1[i]==l[tot]) l[tot].val++;
        else l[++tot]=l1[i];
    }
    for(int i=1;i<=tot;i++) l[i].val=min(l[i].val,l[i].r-l[i].l+1);
    for(int i=1;i<=tot;i++) v[l[i].r].push_back(l[i]);
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1];
        for(int j=0;j<v[i].size();j++)
            f[i]=max(f[i],f[v[i][j].l-1]+v[i][j].val);
    }
    printf("%d\n",n-f[n]);
}
