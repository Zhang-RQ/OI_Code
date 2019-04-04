#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E6+10;

char s[MAXN];
int Rank[MAXN],sa[MAXN],tp[MAXN],buk[MAXN],n,height[MAXN];

void build_sa()
{
    int *Rk=Rank,*tmp=tp;
    int m=127;
    for(int i=1;i<=n;i++)
        Rk[i]=s[i],tmp[i]=i;
    for(int i=1;i<=m;i++)
        buk[i]=0;
    for(int i=1;i<=n;i++)
        buk[Rk[tmp[i]]]++;
    for(int i=1;i<=m;i++)
        buk[i]+=buk[i-1];
    for(int i=n;i;i--)
        sa[buk[Rk[tmp[i]]]--]=tmp[i];
    int p=1;
    for(int len=1;p<n;m=p,len<<=1)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++)
            tmp[++p]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]-len>0)
                tmp[++p]=sa[i]-len;
        for(int i=1;i<=m;i++)
            buk[i]=0;
        for(int i=1;i<=n;i++)
            buk[Rk[tmp[i]]]++;
        for(int i=1;i<=m;i++)
            buk[i]+=buk[i-1];
        for(int i=n;i;i--)
            sa[buk[Rk[tmp[i]]]--]=tmp[i];
        swap(Rk,tmp);
        Rk[sa[1]]=p=1;
        for(int i=2;i<=n;i++)
            Rk[sa[i]]=(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])?p:++p;
    }
    for(int i=1;i<=n;i++)
        Rank[sa[i]]=i;
    for(int i=1,j=0;i<=n;height[Rank[i++]]=j)
        for(j=j?j-1:j;s[i+j]==s[sa[Rank[i-1]]+j];j++);
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    build_sa();
    for(int i=1;i<=n;i++)
        printf("%d%c",sa[i],"\n "[i!=n]);
}
