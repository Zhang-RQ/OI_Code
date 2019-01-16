#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

int n;
char s[233];

int ask(int x,int y)
{
    printf("%d %d\n",x,y);
    fflush(stdout);
    scanf("%s",s+1);
    return s[1]=='b';
}

int main()
{
    scanf("%d",&n);
    int l=1,r=1E9,c1=ask(0,1);
    for(int i=2;i<=n;i++)
    {
        int Mid=(l+r)>>1,c2=ask(Mid,1);
        if(c1==c2) l=Mid;
        else r=Mid;
    }
    printf("%d 0 %d 2\n",l,r);
}