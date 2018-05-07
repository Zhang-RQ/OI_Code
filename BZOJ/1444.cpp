#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const double EPS=1e-10;
const int N=10+5;
const int M=105;
int n,l,m,ch[M][26],tail=0,root=0,isw[M],fail[M],cnt=0,loc[N];
queue<int> Q;
double P[26],C[M][M];
char str[N];
int insert()
{
    int len=strlen(str); int tmp=root; bool flag=0;
    for(int i=0;i<len;i++)
    {
        int c=str[i]-'A'; if(P[c]<=EPS) flag=1;
        if(!ch[tmp][c]) ch[tmp][c]=++tail;
        tmp=ch[tmp][c];
    }
    isw[tmp]=1; if(flag) cnt++;
    return tmp;
}
void getfail()
{
    for(int i=0;i<m;i++) if(ch[root][i]) Q.push(ch[root][i]),fail[ch[root][i]]=root; else ch[root][i]=root;
    while(!Q.empty())
    {
        int top=Q.front(); Q.pop();
        for(int i=0;i<m;i++)
        if(!ch[top][i]) ch[top][i]=ch[fail[top]][i];
        else
        {
            int u=ch[top][i];
            fail[u]=ch[fail[top]][i];
            isw[u]|=isw[fail[u]];
            Q.push(u);
        }
    }
}
void gauss()
{
    for(int i=0;i<=tail;i++)
    {
        int pos=-1;
        for(int j=i;j<=tail;j++)
        if(fabs(C[j][i])>EPS){pos=j;break;}
        if(pos==-1) continue;
        for(int j=0;j<=tail+1;j++) swap(C[i][j],C[pos][j]);
        for(int j=0;j<=tail;j++)
        {
            if(i==j||fabs(C[j][i])<=EPS) continue;
            double r=C[j][i]/C[i][i];
            for(int k=0;k<=tail+1;k++) C[j][k]-=C[i][k]*r;
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&l,&m);
    for(int i=0;i<m;i++)
    {
        int p,q; scanf("%d%d",&p,&q);
        P[i]=(double)p/q;
    }
    for(int i=1;i<=n;i++) scanf("%s",str),loc[i]=insert();
    if(cnt==n) {for(int i=1;i<=n;i++) printf("0.00\n"); return 0;}
    getfail();
    for(int i=0;i<=tail+1;i++) for(int j=0;j<=tail+1;j++)
    if(i==j&&i!=tail+1) C[i][j]=-1; else C[i][j]=0.0;
    C[0][0]=1; C[0][tail+1]=1;
    for(int i=0;i<=tail;i++)
    {
        if(isw[i]) continue;
        for(int c=0;c<m;c++)
        {
            int j=ch[i][c];
            if(j==root) C[root][i]-=P[c];
            else C[j][i]+=P[c];
        }
    }
    gauss();
    for(int i=1;i<=n;i++)
    {
        double ans=C[loc[i]][tail+1]/C[loc[i]][loc[i]];
        if(fabs(ans)<=EPS) printf("0.00\n");
        else printf("%0.2lf\n",ans);
    }
    return 0;
}
