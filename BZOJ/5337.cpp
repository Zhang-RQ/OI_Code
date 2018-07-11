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

typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int P=1E9+7;
const int MAXN=1E4+10;
const int MAXK=101;

int k,nxt[MAXN],len,lenn;
ll f[MAXK][MAXN];
char s[MAXN],str[MAXN];

void get_nxt()
{
    lenn=strlen(s+1);
    for(int i=1,j=0;i<lenn;i++)
    {
        while(j&&s[i+1]!=s[j+1]) j=nxt[j];
        if(s[i+1]==s[j+1]) nxt[i+1]=++j;
    }
}

int main()
{
    scanf("%d",&k);
    scanf("%s",str+1);len=strlen(str+1);
    for(int i=0;i<=len;i++) f[0][i]=1;
    for(int i=1;i<=k;i++)
    {
        int t;
        scanf("%d",&t);
        while(t--)
        {
            scanf("%s",s+1);get_nxt();
            int j=0;
            for(int l=1;l<=len;l++)
            {
                while(j&&s[j+1]!=str[l]) j=nxt[j];
                if(s[j+1]==str[l]) ++j;
                if(j==lenn) (f[i][l]+=f[i-1][l-lenn])%=P;
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=len;i++) (ans+=f[k][i])%=P;
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}