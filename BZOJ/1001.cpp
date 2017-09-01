#include<bits/stdc++.h>
using namespace std;
int nm;
int s,t,n,m;
#define M 2000001
int alist[M];
struct Node{
	int val,nxt,v;
}Edge[M*4];
int cnt=0;
void add(int u,int v,int val)
{
	Edge[++cnt].nxt=alist[u];
	Edge[cnt].v=v;
	Edge[cnt].val=val;
	alist[u]=cnt;
	Edge[++cnt].nxt=alist[v];
	Edge[cnt].v=u;
	Edge[cnt].val=val;
	alist[v]=cnt;
}
void init(void)
{
    int x;
    for(int j=1;j<m;j++)
	{
		scanf("%d",&x);
		add(j,nm+1,x);
	}
	for(int i=1;i<n-1;i++)
	{
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			add((i<<1)*(m-1)+j,((i<<1)-1)*(m-1)+j,x);
	    }
	}
	for(int j=1;j<m;j++)
	{
		scanf("%d",&x);
		add(0,((n<<1)-3)*(m-1)+j,x);
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			if(j==1)add(0,(i<<1)*(m-1)+m,x);
			else if(j==m)add((i<<1|1)*(m-1),nm+1,x);
			else add((i<<1)*(m-1)+j-1,(i<<1)*(m-1)+j+m-1,x);
		}
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			add((i<<1|1)*(m-1)+j,(i<<1)*(m-1)+j,x);
		}
	}
}
void init_mine(void)
{
	int tmp;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m-1;j++)
		{
			scanf("%d",&tmp);
			int u,v;
			if(i==1)	u=j*2,v=t;/*add(j*2,t,tmp);*/
			else if(i==n) u=(n-2)*(m-1)*2+j*2-1,v=s;/*add((n-1)*(m-1)*2+j*2-1,s,tmp);*/
			else u=(i-1)*(m-1)*2+j*2,v=(i-2)*(m-1)*2+(j-1)*2+1;/*add((i-1)*(m-1)*2+j*2,(i-2)*(m-1)*2+(j-1)*2+1,tmp);*/
			add(u,v,tmp);
			//printf("%d %d %d\n",u,v,tmp);
		}
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m;j++)
		{
			int u,v;
			scanf("%d",&tmp);
			if(j==1)	u=s,v=(i-1)*2*(m-1)+1;/*add(s,(i-1)*2+1,tmp);*/
			else if(j==m) u=i*(m-1)*2,v=t;/*add(i*(m-1)*2,t,tmp);*/
			else u=(i-1)*(m-1)*2+(j-1)*2,v=(i-1)*(m-1)*2+(j-1)*2+1;/*add((i-1)*(m-1)*2+(j-1)*2,(i-1)*(m-1)*2+(j-1)*2+1,tmp);*/
			add(u,v,tmp);
			//printf("%d %d %d\n",u,v,tmp);
		}
	for(int i=1;i<=n-1;i++)
		for(int j=1;j<=m-1;j++)
		{
			scanf("%d",&tmp);
			int u,v;
			u=(i-1)*(m-1)*2+j*2-1,v=(i-1)*(m-1)*2+j*2;
			/*add((i-1)*(m-1)*2+j*2-1,(i-1)*(m-1)*2+j*2,tmp);*/
			add(u,v,tmp);
			//printf("%d %d %d\n",u,v,tmp);
		}

}
queue<int> q;
int dis[M];
bool inq[M];
void spfa()
{
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	inq[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int tmp=q.front();
		q.pop();
		inq[tmp]=false;
		for(int i=alist[tmp];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(dis[v]>dis[tmp]+Edge[i].val)
			{
				dis[v]=dis[tmp]+Edge[i].val;
				if(!inq[v])
				{
					q.push(v);
					inq[v]=true;
				}
			}
		}
	}
}
int main()
{
	int tmp;
	int Min=1000000;
	scanf("%d%d",&n,&m);
	s=0;
	t=3000009;
	nm=(n*m-m-n+1)<<1;
	if(n==1)
	{
		for(int i=1;i<=m-1;i++)
		{
			scanf("%d",&tmp);
			Min=min(tmp,Min);
		}
		printf("%d\n",Min);
		return 0;
	}
	if(m==1)
	{
		for(int i=1;i<=n-1;i++)
		{
			scanf("%d",&tmp);
			Min=min(tmp,Min);
		}
		printf("%d\n",Min);
		return 0;
	}
	init();
	spfa();
	printf("%d\n",dis[nm+1]);
	return 0;
}
