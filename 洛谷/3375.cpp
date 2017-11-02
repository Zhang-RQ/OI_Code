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
char s1[1000010],s2[1000010];
int nxt[1000010];
int nxt1[1000010];
vector<int> ans;
void getnxt()//kmp
{
    int len=strlen(s2);
    int k=nxt[0]=-1,pos=0;
    while(pos<len-1)
        if(k==-1||s2[pos]==s2[k])
            if(s2[++pos]!=s2[++k])
                nxt[pos]=k;
            else
                nxt[pos]=nxt[k];
        else k=nxt[k];
}
void get_nxt()//mp
{
    int len=strlen(s2);
    int k=nxt1[0]=-1,pos=0;
    while(pos<len)
        if(k==-1||s2[pos]==s2[k])
            nxt1[++pos]=++k;
        else k=nxt1[k];
}
void kmp()
{
    int i=0,j=0;
    int len1=strlen(s1),len2=strlen(s2);
    while(i<len1)
    {
        if(j==-1||s1[i]==s2[j])
            ++i,++j;
        else j=nxt[j];
        if(j==len2)
            ans.push_back(i-j),
            --i,
            j=0;
    }
}
int main()
{
    scanf("%s%s",s1,s2);
    getnxt();
    get_nxt();
    kmp();
    for(int i=0;i<(signed)ans.size();i++)
        printf("%d\n",ans[i]+1);
    int t=strlen(s2);
    for(int i=1;i<=t;i++)
        printf("%d ",nxt1[i]);
    puts("");
}
