#include<bits/stdc++.h>
using namespace std;
int s,t,n,m;
int alist[1000010];
struct Node{
	int val,nxt,v;
}Edge[9000010];
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
void inti(void)
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
int dis[2000010];
bool inq[2000010];
void spfa()
{
	memset(dis,1236547,sizeof(dis));
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
	int min=1000000;
	scanf("%d%d",&n,&m);
	s=0;
	t=1000009;
	if(n==1)
	{
		for(int i=1;i<=m-1;i++)
		{
			scanf("%d",&tmp);
			min=std::min(tmp,min);
		}
		printf("%d\n",min);
		return 0;
	}
	if(m==1)
	{
		for(int i=1;i<=n-1;i++)
		{
			scanf("%d",&tmp);
			min=std::min(tmp,min);
		}
		printf("%d\n",min);
		return 0;
	}
	inti();
	spfa();
	printf("%d\n",dis[t]);
	return 0;
}
