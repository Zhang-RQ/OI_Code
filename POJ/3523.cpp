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

const int Lim=16*16+1;
const int mv[5][2]={{0,0},{1,0},{-1,0},{0,1},{0,-1}};

int cnt;
char mp[17][17];
int MP[26],pre[Lim][Lim][Lim],lst[Lim][Lim][Lim],Ans=1<<30,n,w,h,id[17][17];

struct st{
	int p[3][2],stp;
	st(){}
	st(int x0,int y0,int x1,int y1,int x2,int y2,int g){p[0][0]=x0;p[0][1]=y0;p[1][0]=x1;p[1][1]=y1;p[2][0]=x2;p[2][1]=y2;stp=g;}
	int* operator [](int i){return p[i];}
	void print()
	{
		for(int i=0;i<n;i++)
			printf("(%d,%d)  ",p[i][0],p[i][1]);
	}
}ori,dst,tmp,tmp2;

inline bool nok(int x,int y){return x<1||x>w||y<1||y>h||mp[x][y]=='#';}

void dfs(int x,int f[Lim][Lim][Lim],int f2[Lim][Lim][Lim],queue<st> &Q,int fla)
{
	if(Ans!=1<<30) return;
	if(x==0) tmp.stp++;
	if(x>=n)
	{
		for(int i=x;i<n;i++)
			tmp[i][0]=tmp[i][1]=tmp2[i][0]=tmp2[i][1]=0;
		bool fafa=1;
		for(int i=0;i<n;i++)
			fafa&=tmp[i][0]==tmp2[i][0]&&tmp[i][1]==tmp2[i][1];
		if(fafa) return;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j)
					if((tmp[i][0]==tmp2[j][0]&&tmp[i][1]==tmp2[j][1]&&tmp2[i][0]==tmp[j][0]&&tmp2[i][1]==tmp[j][1])||(tmp[i][0]==tmp[j][0]&&tmp[i][1]==tmp[j][1]))
						return;
		if(f2[id[tmp[0][0]][tmp[0][1]]][id[tmp[1][0]][tmp[1][1]]][id[tmp[2][0]][tmp[2][1]]]!=-1)
			return;
		if(f[id[tmp[0][0]][tmp[0][1]]][id[tmp[1][0]][tmp[1][1]]][id[tmp[2][0]][tmp[2][1]]]!=-1)
				Ans=min(Ans,tmp.stp+f[id[tmp[0][0]][tmp[0][1]]][id[tmp[1][0]][tmp[1][1]]][id[tmp[2][0]][tmp[2][1]]]);
		f2[id[tmp[0][0]][tmp[0][1]]][id[tmp[1][0]][tmp[1][1]]][id[tmp[2][0]][tmp[2][1]]]=tmp.stp;
		Q.push(tmp);
		return;
	}
	for(int i=0;i<5;i++)
	{
		int tx=tmp[x][0]+mv[i][0],ty=tmp[x][1]+mv[i][1];
		if(nok(tx,ty)) continue;
		tmp[x][0]=tx;tmp[x][1]=ty;
		dfs(x+1,f,f2,Q,fla);
		tmp[x][0]-=mv[i][0];tmp[x][1]-=mv[i][1];
	}
}

void bfs()
{
	queue<st> q1,q2;
	memset(pre,-1,sizeof pre);memset(lst,-1,sizeof lst);
	pre[id[ori[0][0]][ori[0][1]]][id[ori[1][0]][ori[1][1]]][id[ori[2][0]][ori[2][1]]]=ori.stp;
	lst[id[dst[0][0]][dst[0][1]]][id[dst[1][0]][dst[1][1]]][id[dst[2][0]][dst[2][1]]]=dst.stp;
	int dep=0;q1.push(ori);q2.push(dst);
	while(!q1.empty()||!q2.empty())
	{
		if(Ans!=1<<30) break;
		while(!q1.empty())
		{
			if(q1.front().stp!=dep) break;
			tmp2=tmp=q1.front();q1.pop();
			dfs(0,lst,pre,q1,1);
		}
		while(!q2.empty())
		{
			if(q2.front().stp!=dep) break;
			tmp2=tmp=q2.front();q2.pop();
			dfs(0,pre,lst,q2,2);
		}
		++dep;
	}
}

int main()
{
	// freopen("fafa.in","r",stdin);
	while(~scanf("%d%d%d",&w,&h,&n)&&w+h+n)
	{
		getchar();
		swap(w,h);cnt=0;
		memset(MP,-1,sizeof MP);Ans=1<<30;
		for(int i=1;i<=w;i++)
			for(int j=1;j<=h;j++)
				id[i][j]=(i-1)*h+j;
		for(int i=1;i<=w;i++)
		{
			for(int j=1;j<=h;j++)
			{
				mp[i][j]=getchar();
				if(mp[i][j]!=' '&&mp[i][j]!='#')
				{
					if(islower(mp[i][j]))
					{
						if(MP[mp[i][j]-'a']==-1)
							MP[mp[i][j]-'a']=cnt++;
						ori[MP[mp[i][j]-'a']][0]=i;
						ori[MP[mp[i][j]-'a']][1]=j;
					}
					else
					{
						if(MP[mp[i][j]-'A']==-1)
							MP[mp[i][j]-'A']=cnt++;
						dst[MP[mp[i][j]-'A']][0]=i;
						dst[MP[mp[i][j]-'A']][1]=j;	
					}
				}
			}
			getchar();
		}
		bfs();
		printf("%d\n",Ans);
	}
}