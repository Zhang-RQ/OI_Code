#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int MAXN=10010;
const int MAXM=200010;
const int MAXS=35;
const ld EPS=1E-8;

namespace Matrix{
	ld A[MAXS][MAXS],rA[MAXS][MAXS];

	ld det(int siz)
	{
		ld ret=1;
		for(int i=1;i<=siz;i++)
		{
			int pos=i;
			for(int j=i+1;j<=siz;j++)
				if(abs(A[pos][i])<abs(A[j][i]))
					pos=j;
			if(pos!=i)
			{
				for(int j=1;j<=siz;j++)
					swap(A[pos][j],A[i][j]);
				ret*=-1;
			}
			if(abs(A[i][i])<EPS) return 0;
			for(int j=i+1;j<=siz;j++)
			{
				double t=A[j][i]/A[i][i];
				for(int k=1;k<=siz;k++)
					A[j][k]-=t*A[i][k];
			}
		}
		for(int i=1;i<=siz;i++)
			ret*=A[i][i];
		return ret;
	}
}

struct edge_t{int u,v,w,va;}Edge[MAXM];

int n,m,id[MAXN],vis[MAXN];
int val[MAXM],fa[MAXN],siz[MAXN];
vector<edge_t> ve[MAXM],vt[MAXM],tmp;
set<int> s;
ld Ans;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void merge(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	if(siz[x]<siz[y]) swap(x,y);
	fa[y]=x;siz[x]+=siz[y];
}

int getid(int x,int now,int &idx)
{
	if(vis[x]==now) return id[x];
	else return vis[x]=now,id[x]=++idx;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].w,&Edge[i].va),val[i]=Edge[i].w;
	sort(val+1,val+1+m);
	int tot=unique(val+1,val+1+m)-val-1,tms=0; //timestamp
	for(int i=1;i<=m;i++)
	{
		Edge[i].w=lower_bound(val+1,val+1+tot,Edge[i].w)-val;
		ve[Edge[i].w].push_back(Edge[i]);
	}
	for(int i=1;i<=tot;i++)
	{
		tmp.clear();
		vector<edge_t> &vn=ve[i];
		for(size_t _=0;_<vn.size();_++)
			if(find(vn[_].u)!=find(vn[_].v))
				tmp.push_back((edge_t){find(vn[_].u),find(vn[_].v),i,vn[_].va});
		for(size_t _=0;_<vn.size();_++)
			merge(vn[_].u,vn[_].v);
		for(size_t _=0;_<tmp.size();_++)
		{
			vt[find(tmp[_].u)].push_back((edge_t){tmp[_].u,tmp[_].v,i,tmp[_].va});
			s.insert(find(tmp[_].u));
		}
		for(set<int>::iterator it=s.begin();it!=s.end();it++)
		{
			vector<edge_t> &vnn=vt[*it];
			int idx=0;++tms;
			for(size_t _=0;_<vnn.size();_++)
				vnn[_].u=getid(vnn[_].u,tms,idx),vnn[_].v=getid(vnn[_].v,tms,idx);
			memset(Matrix::rA,0,sizeof Matrix::rA);
			for(size_t _=0;_<vnn.size();_++)
			{
				Matrix::rA[vnn[_].u][vnn[_].u]++;
				Matrix::rA[vnn[_].v][vnn[_].v]++;
				Matrix::rA[vnn[_].u][vnn[_].v]--;
				Matrix::rA[vnn[_].v][vnn[_].u]--;
			}
			memcpy(Matrix::A,Matrix::rA,sizeof Matrix::A);
			ld tot=Matrix::det(idx-1);
			for(size_t _=0;_<vnn.size();_++)
			{
				memcpy(Matrix::A,Matrix::rA,sizeof Matrix::A);
				Matrix::A[vnn[_].u][vnn[_].u]--;
				Matrix::A[vnn[_].v][vnn[_].v]--;
				Matrix::A[vnn[_].u][vnn[_].v]++;
				Matrix::A[vnn[_].v][vnn[_].u]++;
				ld fafa=Matrix::det(idx-1);
				Ans+=vnn[_].va*(tot-fafa)/tot;
			}
			vnn.clear();
		}
		s.clear();
	}
	printf("%.5Lf\n",Ans);
}
