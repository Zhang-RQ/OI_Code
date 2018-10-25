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

const int MAXN=1E6+10;

int n,Ans;
char str[MAXN];
vector<int> v[26];

int main()
{
	scanf("%d%s",&n,str+1);
	for(int i=1;i<=n;i++)
		v[str[i]-'a'].push_back(i);
	for(int i=0;i<26;i++)
		for(int j=0;j<26;j++)
		{
			int s=0,cnt=0,mn=0,mn2=6666666,mnv=0,p1=0,p2=0;
			while(p1<v[i].size()&&p2<v[j].size())
			{
				if(v[i][p1]<v[j][p2])
				{
					s+=1;++p1;
					if(cnt==mnv) Ans=max(Ans,s-mn2);
					else Ans=max(Ans,s-mn);
				}
				else
				{
					s-=1;cnt++;++p2;
					if(s<=mn) mn2=mn,mn=s,mnv=cnt;
					if(cnt==mnv) Ans=max(Ans,s-mn2);
					else Ans=max(Ans,s-mn);
				}
			}
			while(p1<v[i].size())
			{
				s+=1;++p1;
				if(cnt==mnv) Ans=max(Ans,s-mn2);
				else Ans=max(Ans,s-mn);
				
			}
			while(p2<v[j].size())
			{
				s-=1;cnt++;++p2;
				if(s<=mn) mn2=mn,mn=s,mnv=cnt;
				if(cnt==mnv) Ans=max(Ans,s-mn2);
				else Ans=max(Ans,s-mn);
			}
		}
	printf("%d\n",Ans);
}