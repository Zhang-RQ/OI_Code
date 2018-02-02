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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=5E5+5;
int son[MAXN][3],par[MAXN],mx[MAXN],f[MAXN];
int lst=1,root=1,cnt=1,n,m,L,R,ans  ;
char str[MAXN];
deque<int> Q;
void insert(int x)
{
    x-='0';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x])
        son[p][x]=np,p=par[p];
    if(!p)
        par[np]=root;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
bool check(int x)
{
    int u=root,l=0,len=0;
    f[0]=f[1]=0;
    Q.clear();
    for(int i=1;str[i];i++)
    {
        ++len;
        while(u!=root&&!son[u][str[i]-'0'])
            u=par[u],l=mx[u];
        if(son[u][str[i]-'0']) l++,u=son[u][str[i]-'0'];
        else l=0,u=root;
        f[i]=f[i-1];
        while(i>=x&&Q.size()&&(f[Q.back()]-Q.back())<=f[i-x]-(i-x)) Q.pop_back();
        if(i>=x) Q.push_back(i-x);
        while(Q.size()&&Q.front()<i-l) Q.pop_front();
        if(Q.size()) f[i]=max(f[i],f[Q.front()]+i-Q.front());
    }
    return (10ll*f[len]>=9ll*len);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",str+1);
        for(int j=1;str[j];j++)
            insert(str[j]);
        insert('2');
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        L=0;R=strlen(str+1);
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check(mid)) ans=mid,L=mid+1;
            else R=mid-1;
        }
        printf("%d\n",ans);
    }
}
