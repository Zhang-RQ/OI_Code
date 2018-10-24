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

const int MAXN=1010;
const int Fn=233666;

int n,top,Ans;
set<char> s;
char str[233],str2[233],str3[666];

struct T{
	char c;
	int x,y;
	T(){}
	T(char _c,int _x,int _y){c=_c;x=_x;y=_y;}
}stk[MAXN];

void solve()
{
	scanf("%d%s",&n,str+1);
	s.clear();top=0;
	if(str[3]=='1') Ans=0;
	else sscanf(str+1,"O(n^%d)",&Ans);
	int Mx=0,now=0;
	int flag=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='F')
		{
			scanf("%s%s%s",str+1,str2+1,str3+1);
			int L,R;
			if(str2[1]=='n') L=Fn;
			else sscanf(str2+1,"%d",&L);
			if(str3[1]=='n') R=Fn;
			else sscanf(str3+1,"%d",&R);
			if(L>R) flag++;
			if(!flag&&L!=R&&R==Fn) ++now;
			Mx=max(Mx,now);
			stk[++top]=T(str[1],L,R);
			if(!s.insert(str[1]).second)
			{
				while(i<=n) ++i,gets(str+1);
				s.clear();top=0;
				puts("ERR");
				return;
			}
		}
		else
		{
			if(!top)
			{
				while(i<=n) ++i,gets(str+1);
				s.clear();top=0;
				puts("ERR");
				return;
			}
			if(stk[top].x>stk[top].y) --flag;
			if(!flag&&stk[top].x!=stk[top].y&&stk[top].y==Fn) --now;
			s.erase(stk[top].c);
			--top;
		}
	}
	if(top) return puts("ERR"),void();
	if(Mx!=Ans) puts("No");
	else puts("Yes");
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}