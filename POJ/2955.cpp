#include<cstdio>
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
using namespace std;
typedef long long ll;
char s[110];
int f[110][110];
int main()
{
    while(~scanf("%s",s+1)&&s[1]!='e')
    {
        int slen=strlen(s+1);
        memset(f,0,sizeof(f));
        for(int len=2;len<=slen;len++)
            for(int l=1,r=l+len-1;r<=slen;l++,r++)
            {
                if((s[l]=='('&&s[r]==')')||(s[l]=='['&&s[r]==']'))
                    f[l][r]=max(f[l][r],f[l+1][r-1]+2);
                for(int k=l;k<r;k++)
                    f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]);
            }
        printf("%d\n",f[1][slen]);
    }
    return 0;
}
