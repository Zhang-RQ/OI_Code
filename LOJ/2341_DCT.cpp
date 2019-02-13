#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

void play(int n, int T, int dataType);

namespace Grader{
	static const int MAXN = 300005;

	static void wrong(const char *msg) {
		printf("%s\n", msg);
		exit(0);
	}

	static void wrong(const char *msg, int x) {
		printf(msg, x);
		printf("\n");
		exit(0);
	}

	static int n, T, dataType;

	struct Edge {
		Edge *next;
		int to;
	};

	static Edge *firstEdge[MAXN], edges[MAXN * 2], *lastEdge = edges;

	static void addEdge(int u, int v) {
		*(++lastEdge) = (Edge){firstEdge[u], v};
		firstEdge[u] = lastEdge;
	}

	static int fa[MAXN];
	static int dTime[MAXN], fTime[MAXN];
	static int dfsSeq[MAXN];

	static int cntExploreCalls = 0;

	static int *childArrStart[MAXN];
	static int childArr[MAXN];

	static void dfs() {
		static int stack[MAXN];
		int top = 1;
		int nowTime = 0;
		stack[1] = 1;
		while (top) {
			int u = stack[top];
			if (dTime[u]) {
				fTime[u] = nowTime;
				--top;
				continue;
			}
			dTime[u] = ++nowTime;
			dfsSeq[nowTime] = u;
			int lastTop = top;
			for (Edge *e = firstEdge[u]; e; e = e->next) {
				int v = e->to;
				if (v == fa[u]) continue;
				fa[v] = u;
				stack[++top] = v;
			}
			for (int i = lastTop + 1, j = top; i < j; i++, j--) {
				int tmp = stack[i];
				stack[i] = stack[j];
				stack[j] = tmp;
			}
		}
	}

	static bool discovered[MAXN];

	static unsigned int seed;

	inline static int nextInt() {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;

		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;

		return (seed << 2) >> 2;
	}

	static void init() {
		scanf("%u", &seed);
		for (int i = 0; i < 10; i++) {
			nextInt();
		}
		scanf("%d%d%d", &n, &T, &dataType);
		n ^= nextInt();
		T ^= nextInt();
		T=1<<30;
		dataType ^= nextInt();
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			u ^= nextInt();
			v ^= nextInt();
			addEdge(u, v);
			addEdge(v, u);
		}
		fa[1] = 0;
		dfs();
		int *childArrPointer = childArr;
		for (int i = 1; i <= n; i++) {
			childArrStart[i] = childArrPointer;
			for (Edge *e = firstEdge[i]; e; e = e->next) {
				int j = e->to;
				if (j == fa[i]) continue;
				*(childArrPointer++) = dTime[j];
			}
		}
		childArrStart[n + 1] = childArrPointer;
		memset(discovered, 0, sizeof(discovered));
		discovered[1] = true;
	}

	int explore(int x, int y) {
		if (++cntExploreCalls > T) {
			wrong("explore: too many calls");
		}
		if (x < 1 || x > n) {
			wrong("explore: argument x (%d) not in [1, n]", x);
		}
		if (y < 1 || y > n) {
			wrong("explore: argument y (%d) not in [1, n]", y);
		}
		if (x == y) {
			wrong("explore: argument x = y = %d", x);
		}
		if (!discovered[x]) {
			wrong("explore: node x (%d) not discovered", x);
		}
		int z = fa[x];
		if (dTime[x] < dTime[y] && fTime[x] >= fTime[y]) {
			int *A = childArrStart[x];
			int N = childArrStart[x + 1] - A;
			int val = dTime[y];
			while (N > 1) {
				int mid = N >> 1;
				if (val < A[mid]) {
					N = mid;
				} else {
					A += mid;
					N -= mid;
				}
			}
			z = dfsSeq[A[0]];
		}
		discovered[z] = true;
		return z;
	}

	static void check() {
		for (int i = 1; i <= n; i++) {
			if (!discovered[i]) {
				wrong("node %d not discovered after the game", i);
			}
		}
		printf("13cae2f046fbc4c80ead95e423cc697f\n");
		#ifdef DEBUG
		printf("# of explore calls = %d\n", cntExploreCalls);
		#endif
	}

	int main() {
		init();
		play(n, T, dataType);
		check();
		return 0;
	}
}

using Grader::explore;

const int MAXN=3E5+10;
const double Alpha=0.7;

vector<int> g[MAXN],t[MAXN];
bool ok[MAXN],vis[MAXN];
int sizt[MAXN],ord[MAXN];//Tree
int siz[MAXN],jmp[MAXN][20],dep[MAXN],rt,mx_rt,Rt;//DCT
int stk[MAXN];

void find_rt(int x,int fa,int sz)
{
	int mx=0;
	sizt[x]=1;
	for(int v:t[x])
		if(v!=fa&&ok[v])
		{
			find_rt(v,x,sz);
			mx=max(mx,sizt[v]);
			sizt[x]+=sizt[v];
		}
	mx=max(sz-sizt[x],mx);
	if(mx<mx_rt) mx_rt=mx,rt=x;
	if(!fa) assert(sizt[x]==sz);
}

void build(int x,int sz)
{
	ok[x]=0;dep[x]=dep[jmp[x][0]]+1;siz[x]=1;
	for(int j=1;(1<<j)<=dep[x];j++) jmp[x][j]=jmp[jmp[x][j-1]][j-1];
	for(int v:t[x])
		if(ok[v])
		{
			mx_rt=1<<30;
			find_rt(v,0,sizt[x]>sizt[v]?sizt[v]:sz-sizt[x]);
			jmp[rt][0]=x;g[x].push_back(rt);
			int _rt=rt;
			build(rt,sizt[x]>sizt[v]?sizt[v]:sz-sizt[x]);
			siz[x]+=siz[_rt];
		}
}

void dfs(int x)
{
	ok[x]=1;
	for(int v:g[x])
		dfs(v);
	g[x].clear();
}

void rebuild(int x)
{
	dfs(x);mx_rt=1<<30;
	find_rt(x,0,siz[x]);
	if(x!=Rt)
	{
		jmp[rt][0]=jmp[x][0];
		for(int &v:g[jmp[x][0]])
			if(v==x) {v=rt;break;}
	}
	else Rt=rt,memset(jmp[rt],0,sizeof jmp[rt]);
	build(rt,siz[x]);
}

void insert(int x,int y)//y is fa
{
	vis[x]=1;
	t[y].push_back(x);
	t[x].push_back(y);
	g[y].push_back(x);
	jmp[x][0]=y;
	dep[x]=dep[y]+1;
}

int find_nxt(int x,int y)// y is fa
{
	int stp=dep[x]-dep[y]-1;
	for(int j=19;~j;j--) if((stp>>j)&1) x=jmp[x][j];
	return x;
}

void solve_bt(int n)
{
	for(int i=2;i<=n;i++)
		if(!vis[i])
		{
			int x=1;
			while(x!=i) x=explore(x,i),vis[x]=1;
		}

}

void solve_chain(int n)
{
	srand((ull)new char);
	vis[1]=1;
	int L=1,R=1;
	for(int i=1;i<=n;i++) ord[i]=i;
	random_shuffle(ord+2,ord+1+n);
	for(int i=2;i<=n;i++)
	{
		int v=ord[i];
		if(vis[v]) continue;
		int x=explore(L,v);
		if(!vis[x])
		{
			while(x!=v)	vis[x]=1,x=explore(x,v);
			vis[v]=1;L=v;
		}
		else
		{
			x=explore(R,v);
			while(x!=v)	vis[x]=1,x=explore(x,v);
			vis[v]=1;R=v;
		}
	}
}

void play(int n, int T, int dataType)
{
	if(dataType==2) return solve_bt(n);
	if(dataType==3) return solve_chain(n);
	srand((ull)new char);
	vis[1]=1;Rt=1;siz[1]=1;
	for(int i=1;i<=n;i++) ord[i]=i;
	random_shuffle(ord+1,ord+1+n);
	for(int _=1;_<=n;_++)
		if(!vis[ord[_]])
		{
			int x=Rt,top=0,fir=1<<30;
			while(x!=ord[_])
			{
				stk[++top]=x;
				int y=explore(x,ord[_]);
				if(!vis[y]) fir=min(fir,top+1),insert(y,x),x=y;
				else x=find_nxt(y,x);
			}
			stk[++top]=ord[_];
			for(int i=top;i>=fir;i--) siz[stk[i]]=top-i+1;
			for(int i=fir-1;i;i--) siz[stk[i]]+=top-fir+1;
			for(int i=1;i<top;i++)
				if(siz[stk[i]]*Alpha<siz[stk[i+1]])
					{rebuild(stk[i]);break;}
		}
}

int main() {Grader::main();}