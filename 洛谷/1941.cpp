#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define INF 400123456
#define maxn 10010

using namespace std;

int u[maxn],v[maxn],x[maxn],y[maxn],f[2][maxn];
int n,m,k;

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
		u[i]=0;v[i]=m+1;
	}
	for (int i=1;i<=k;i++){
			int W,D,T;
			scanf("%d%d%d",&W,&D,&T);
			u[W]=D;v[W]=T;
			}
	int now=1;
	int cnt=0;
	for (int i=0;i<=m;i++)
		f[0][i]=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			f[now][j]=INF;
		for (int j=1;j<=m;j++)
			if (j-x[i]>0){
				f[now][j]=min(f[now][j],min(f[now][j-x[i]]+1,f[now^1][j-x[i]]+1));
			}
		for (int j=1;j<=m;j++)
			if (j+y[i]<=m)
				f[now][j]=min(f[now][j],f[now^1][j+y[i]]);
		if (v[i]==m+1){
            for (register int j=1;j<=x[i];++j)
            for (register int k=1;k*x[i]<m+j;++k)
                if (f[now][m]>f[now^1][m+j-k*x[i]]+k){
                    f[now][m]=f[now^1][m+j-k*x[i]]+k;
                }
        }
		for (int j=1;j<=u[i];j++) f[now][j]=INF;
		for (int j=v[i];j<=m;j++) f[now][j]=INF;

		int flag=0;
		for (int j=u[i]+1;j<v[i];j++)
			if (f[now][j]!=INF){
				flag=1;break;
			}
		if (!flag) {
			printf("0\n%d\n",cnt);
			return 0;
		}
		if (v[i]!=m+1) cnt++;
	now^=1;
	}
	int MIN=INF;
	for (int i=u[n]+1;i<v[n];i++)
		MIN=min(MIN,f[now^1][i]);
	printf("1\n%d\n",MIN);
	return 0;
}
