%:pragma GCC optimize(2)
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
typedef unsigned long long ull;
const int MAXN=1000005;
struct Aho_Corasick_Automaton{
    int son[MAXN][26],fail[MAXN];
    int tot,cnt[MAXN];
    void insert(char *s)
    {
        int x=0;
        for(int i=1;s[i];i++)
        {
            if(!son[x][s[i]-'a'])
                son[x][s[i]-'a']=++tot;
            x=son[x][s[i]-'a'];
        }
        cnt[x]++;
    }
    void get_fail()
    {
        queue<int> q;
        for(int i=0;i<26;i++)
            if(son[0][i])
                fail[son[0][i]]=0,
                q.push(son[0][i]);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=0;i<26;i++)
                if(son[x][i])
                    fail[son[x][i]]=son[fail[x]][i],q.push(son[x][i]);
                else son[x][i]=son[fail[x]][i];
        }
    }
    int query(char *s)
    {
        int ret=0,x=0;
        for(int i=1;s[i];i++)
        {
            //printf("%d %c\n",x,s[i]);
            x=son[x][s[i]-'a'];
            for(int i=x;i&&~cnt[i];i=fail[i])
                if(cnt[i])
                    ret+=cnt[i],cnt[i]=-1;
        }
        return ret;
    }
}ACM;
char str[1000005];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str+1),
        ACM.insert(str);
    ACM.get_fail();
    scanf("%s",str+1);
    printf("%d\n",ACM.query(str));
}
