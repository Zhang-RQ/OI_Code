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
struct node{
    int cnt;
    char str[100];
    bool operator < (node a) const
    {
        return cnt>a.cnt;
    }
}word[210];
struct Aho_Corasick_Automaton{
    int son[MAXN][26],fail[MAXN];
    int tot,cnt[MAXN],end[MAXN];
    void insert(char *s,int n)
    {
        int x=0;
        for(int i=1;s[i];i++)
        {
            if(!son[x][s[i]-'a'])
                son[x][s[i]-'a']=++tot;
            x=son[x][s[i]-'a'];
        }
        end[x]=n;
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
    void query(char *s)
    {
        int x=0;
        for(int i=1;s[i];i++)
        {
            x=son[x][s[i]-'a'];
            for(int i=x;i;i=fail[i])
                word[end[i]].cnt++;
        }
    }
    void clear()
    {
        memset(son,0,sizeof(son));
        memset(fail,0,sizeof(fail));
        memset(cnt,0,sizeof(cnt));
        memset(end,0,sizeof(end));
        tot=0;
    }
}ACM;
char str[MAXN];
int n;
int main()
{
    while(scanf("%d",&n)&&n)
    {
        ACM.clear();
        memset(word,0,sizeof(word));
        for(int i=1;i<=n;i++)
            scanf("%s",word[i].str+1),
            ACM.insert(word[i].str,i);
        ACM.get_fail();
        scanf("%s",str+1);
        ACM.query(str);
        stable_sort(word+1,word+1+n);
        printf("%d\n",word[1].cnt);
        printf("%s\n",word[1].str+1);
        for(int i=2;word[i].cnt==word[1].cnt;i++)
            printf("%s\n",word[i].str+1);
    }
}
