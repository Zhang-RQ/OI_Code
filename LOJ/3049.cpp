#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=7E5+10;
const int MAXM=2E6+10;

char str[MAXN];
int lst=1,rt=1,cnt=1,totp,m,lena[MAXN],lenb[MAXN],ida[MAXN],Pt[MAXN];
int son[MAXN][26],mx[MAXN],par[MAXN],pnt[MAXN],n,na,nb,jmp[MAXN][20],pntb[MAXN];
vector<int> p[MAXN],Suf[MAXN];

void clear()
{
    for(int i=1;i<=cnt;i++)
        memset(son[i],0,sizeof son[i]),
        memset(jmp[i],0,sizeof jmp[i]),
		p[i].clear(),Suf[i].clear(),
		mx[i]=par[i]=pnt[i]=pntb[i]=0;
    lst=rt=cnt=1;totp=0;
    n=na=nb=m=0;
}

int append(int x)
{
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x])
        son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
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
            memcpy(son[nq],son[q],sizeof son[q]);
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p];
        }
    }
    return lst=np;
}

namespace DAG{
    vector<int> G[MAXM];
    int d[MAXM],val[MAXM];
    ll f[MAXM];
    
    void clear()
    {
        for(int i=0;i<=totp;i++)
            val[i]=d[i]=f[i]=0,
            G[i].clear();
    }
    
    void add(int u,int v)
    {
        G[u].push_back(v);
        d[v]++;
    }
    
    void solve()
    {
        queue<int> q;
        for(int i=1;i<=totp;i++)
            if(!d[i]) q.push(i);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            f[x]+=val[x];
            for(int v:G[x])
            {
                f[v]=max(f[v],f[x]);
                if(!--d[v]) q.push(v);
            }
        }
        for(int i=1;i<=totp;i++)
            if(d[i]) return puts("-1"),void();
        ll Ans=0;
        for(int i=1;i<=totp;i++)
            Ans=max(Ans,f[i]);
        printf("%lld\n",Ans);
    }
}

void solve()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    reverse(str+1,str+1+n);
    for(int i=1;i<=n;i++)
        pnt[i]=append(str[i]-'a'); //prefix [i]
    reverse(pnt+1,pnt+1+n);
    for(int i=1;i<=cnt;i++)
        jmp[i][0]=par[i];
    for(int j=1;j<=19;j++)
        for(int i=1;i<=cnt;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    totp=cnt;
	for(int i=1;i<=cnt;i++)
		Pt[i]=++totp;
    scanf("%d",&na);
    for(int i=1,l,r;i<=na;i++)
    {
        scanf("%d%d",&l,&r);
        int x=pnt[l];
        for(int j=19;~j;j--)
            if(mx[jmp[x][j]]>=r-l+1)
                x=jmp[x][j];
		p[x].push_back(i);
		lena[i]=r-l+1;
		ida[i]=++totp;
		DAG::val[totp]=r-l+1;
    }
    scanf("%d",&nb);
    for(int i=1,l,r;i<=nb;i++)
    {
        scanf("%d%d",&l,&r);
        int x=pnt[l];
        for(int j=19;~j;j--)
            if(mx[jmp[x][j]]>=r-l+1)
                x=jmp[x][j];
        pntb[i]=x;lenb[i]=r-l+1;
    }
    scanf("%d",&m);
	for(int i=1;i<=cnt;i++)
	{
		if(!p[i].size())
		{
			DAG::add(i,Pt[i]);
			continue;
		}
		sort(p[i].begin(),p[i].end(),[](int x,int y){return lena[x]<lena[y];});
		for(int v:p[i])
		{
			++totp;
			DAG::add(totp,ida[v]);
			Suf[i].push_back(totp);
		}
		DAG::add(i,Suf[i][0]);
		if(Suf[i].size()>1)
			for(int j=Suf[i].size()-2;~j;j--)
				DAG::add(Suf[i][j],Suf[i][j+1]);
		DAG::add(Suf[i].back(),Pt[i]);
	}
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
		vector<int> &V=p[pntb[y]];
		if(!V.size())
		{
			DAG::add(ida[x],pntb[y]);
			continue;
		}
		int L=0,R=V.size()-1,Ans=-1;
		while(L<=R)
		{
			int Mid=(L+R)>>1;
			if(lenb[y]<=lena[V[Mid]]) R=Mid-1,Ans=Mid;
			else L=Mid+1;
		}
		if(~Ans) DAG::add(ida[x],Suf[pntb[y]][Ans]);
		else DAG::add(ida[x],Pt[pntb[y]]);
	}
    for(int i=2;i<=cnt;i++)
		DAG::add(Pt[par[i]],i);
    DAG::solve();
    DAG::clear();clear();
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
}
