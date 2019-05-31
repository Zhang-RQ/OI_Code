#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

char str[MAXN],Ans[MAXN];
int cnt[6],n,m,f[1<<6],ok[MAXN];

bool chk()
{
	for(int s=1;s<1<<6;s++)
	{
		int sum=0;
		for(int i=0;i<6;i++)
			if((s>>i)&1)
				sum+=cnt[i];
		if(sum>f[s])
			return false;
	}
	return true;
}

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++)
		cnt[str[i]-'a']++;
	scanf("%d",&m);
	for(int i=1,p;i<=m;i++)
	{
		scanf("%d%s",&p,str+1);
		int len=strlen(str+1);
		for(int j=1;j<=len;j++)
			ok[p]|=1<<(str[j]-'a');
	}
	for(int p=1;p<=n;p++)
	{
		if(!ok[p])
			ok[p]=(1<<6)-1;
		for(int s=1;s<1<<6;s++)
			if(ok[p]&s)
				f[s]++;
	}
	for(int p=1;p<=n;p++)
	{
		bool fafa=0;
		for(int s=1;s<1<<6;s++)
			if(ok[p]&s)
				f[s]--;
		for(int c=0;c<6;c++)
			if((ok[p]>>c)&1)
			{
				if(!cnt[c])
					continue;
				cnt[c]--;
				if(chk())
				{
					Ans[p]=c+'a';
					fafa=1;break;
				}
				else
					++cnt[c];
			}
		if(!fafa)
			return puts("Impossible"),0;
	}
	puts(Ans+1);
}
