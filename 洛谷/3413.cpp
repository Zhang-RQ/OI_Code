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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int P=1E9+7;
int f[1010][10][10][2],num[1010];
char s1[1010],s2[1010];
int dfs(int len,int lst,int llst,bool zero,bool lim,bool _f)
{
    if(!len) return _f;
    if(!zero&&!lim&&f[len][lst][llst][_f]!=-1) return f[len][lst][llst][_f];
    int mx=lim?num[len]:9,ret=0;;
    for(int i=0;i<=mx;i++)
        (ret+=dfs(len-1,i,zero?-1:lst,zero&&i==0,lim&&i==mx,_f||((i==lst)&&!zero)||((i==llst)&&!zero)))%=P;
    if(!lim&&!zero&&llst!=-1) f[len][lst][llst][_f]=ret%P;
    return ret%P;
}
int solve(char *s)
{
    memset(f,-1,sizeof f);
    int tot=strlen(s+1);
    for(int i=1;i<=tot;i++) num[i]=s[i]-'0';
    return dfs(tot,-1,-1,1,1,0);
}
int main()
{
    scanf("%s%s",s1+1,s2+1);
    int len1=strlen(s1+1),len2=strlen(s2+1);
    if(s1[len1]=='0')
    {
        int j=len1;
        for(j=len1;s1[j]=='0';j--)
            s1[j]='9';
        s1[j]--;
        reverse(s1+1,s1+len1+1);
        if(s1[len1]=='0') s1[len1]='\0';
    }
    else --s1[len1],reverse(s1+1,s1+len1+1);
    reverse(s2+1,s2+1+len2);
    printf("%d\n",(solve(s2)-solve(s1)+P)%P);
}
