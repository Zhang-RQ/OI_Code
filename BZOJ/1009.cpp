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

int n,m,P,nxt[25];
char str[25];

struct Matrix{
    ll val[25][25];
    ll* operator [] (const int &i) {return val[i];}
    const ll * operator [] (const int &i) const {return val[i];}
    Matrix operator *(const Matrix &a) const
    {
        Matrix ret;
        memset(ret.val,0,sizeof(ret.val));
        for(int i=0;i<=20;i++)
            for(int j=0;j<=20;j++)
                for(int k=0;k<=20;k++)
                    (ret.val[i][j]+=val[i][k]*a[k][j])%=P;
        return ret;
    }
    inline void print()
    {
        for(int i=0;i<=m+1;i++)
            for(int j=0;j<=m+1;j++)
                printf("%lld%c",val[i][j],j==m+1?'\n':' ');
        puts("");
    }
}A,B;

Matrix ksm(Matrix a,int b)
{
    Matrix ret,base=a;
    memset(ret.val,0,sizeof(ret.val));
    for(int i=0;i<=20;i++) ret.val[i][i]=1;
    while(b)
    {
        if(b&1) ret=base*ret;
        base=base*base;
        b>>=1;
    }
    return ret;
}

int main()
{
    scanf("%d%d%d",&n,&m,&P);
    scanf("%s",str+1);
    for(int i=2,j=0;i<=m;i++)
    {
    	while(j>0&&str[j+1]!=str[i]) j=nxt[j];
    	if(str[j+1]==str[i]) j++;
    	nxt[i]=j;
    }
    for(int i=0;i<m;i++)
       for(int j=0;j<=9;j++)
       {
       	    int t=i;
			while(t>0&&str[t+1]-'0'!=j)
			    t=nxt[t];
			if(str[t+1]-'0'==j) t++;
			if(t!=m) A[t][i]=(A[t][i]+1)%P;
       }
    B=ksm(A,n);
    ll ans=0;
    for(int i=0;i<m;i++) (ans+=B[i][0])%=P;
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}