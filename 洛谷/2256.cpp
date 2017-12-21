#include<cstdio>
using namespace std;
typedef unsigned long long ull;
const int MAXN=20010;
const ull P=1000107;
ull Hash(char *t,ull ret=0)
{
    for(;*t;ret=(*(t++)+ret*131)%P);
    return ret;
}
ull tmp;
char s1[1001],s2[1001];
int fa[P];
int n,m,k;
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<P;i++)
        fa[i]=i;
    for(int i=1;i<=n;i++)
        scanf("%*s");
    for(int i=1;i<=m;i++)
    {
        scanf("%s%s",s1,s2);
        fa[find(Hash(s1))]=fa[find(Hash(s2))];
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%s%s",s1,s2);
        if(find(Hash(s1))==find(Hash(s2)))
            puts("Yes.");
        else puts("No.");
    }
}
