#include<cstdio>
#include<algorithm>
#include<queue>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=480;

int n,cnt,son[MAXN][26],fail[MAXN],finalP;
short dis[MAXN][1<<12],ed[MAXN],prep[MAXN][1<<12];
char s[MAXN],Ans[MAXN];
short pre1[MAXN][1<<12],pre2[MAXN][1<<12];

void insert(int id)
{
	int x=0;
	for(int i=1;s[i];i++)
	{
		if(!son[x][s[i]-'A']) son[x][s[i]-'A']=++cnt;
		x=son[x][s[i]-'A'];
	}
	ed[x]|=1<<(id-1);
}

void build()
{
	queue<int> q;
	for(int i=0;i<26;i++)
		if(son[0][i])
			q.push(son[0][i]);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		ed[x]|=ed[fail[x]];
		for(int i=0;i<26;i++)
			if(son[x][i])
				fail[son[x][i]]=son[fail[x]][i],q.push(son[x][i]);
			else son[x][i]=son[fail[x]][i];
	}
}

void BFS()
{
	queue<pair<int,int> > q;
	q.push(make_pair(0,0));
	int ful=(1<<n)-1;
	while(!q.empty())
	{
		int x=q.front().first,s=q.front().second;q.pop();
		if(s==ful) {finalP=x;break;}
		for(int i=0;i<26;i++)
		{
			if(son[x][i]&&!dis[son[x][i]][s|ed[son[x][i]]])
			{
				pre1[son[x][i]][s|ed[son[x][i]]]=x;
				pre2[son[x][i]][s|ed[son[x][i]]]=s;
				prep[son[x][i]][s|ed[son[x][i]]]=i;
				dis[son[x][i]][s|ed[son[x][i]]]=dis[x][s]+1;
				q.push(make_pair(son[x][i],s|ed[son[x][i]]));
			}
		}
	}
	int x=finalP,s=ful;
	for(int i=dis[x][s];i;i--)
	{
		Ans[i]=prep[x][s]+'A';
		int tx=x;
		x=pre1[tx][s];s=pre2[tx][s];
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s+1),insert(i);
	build();BFS();puts(Ans+1);
}