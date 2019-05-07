#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E7+19;
const int MAXQ=1E5+10;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

struct opt{
	int tp,pos,val;
}op[MAXQ];

int n,q,t,A[MAXQ],B[MAXQ],pos[MAXQ],cnt,tim[MAXQ],global_T,lst;
ll inv[P],a[MAXQ];

void update(int pos)
{
	if(tim[pos]<global_T) tim[pos]=global_T,a[pos]=lst;
}

void Cover(int val)
{
	++global_T;
	lst=val;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&op[i].tp);
		if(op[i].tp==1) scanf("%d%d",&op[i].pos,&op[i].val),pos[++cnt]=op[i].pos;
		else if(op[i].tp==5) scanf("%d",&op[i].pos),pos[++cnt]=op[i].pos;
		else if(op[i].tp!=6) scanf("%d",&op[i].val);
		op[i].val=(op[i].val%P+P)%P;
	}
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
		scanf("%d%d",&A[i],&B[i]);
	inv[1]=1;
	for(int i=2;i<P;i++)
		inv[i]=Sub(P,(P/i))*inv[P%i]%P;
	sort(pos+1,pos+1+cnt);
	cnt=unique(pos+1,pos+1+cnt)-pos-1;
	for(int i=1;i<=q;i++)
		if(op[i].pos)
			op[i].pos=lower_bound(pos+1,pos+1+cnt,op[i].pos)-pos;
	ll tagm=1,taga=0,s=0,Ans=0;
	for(int i=1;i<=t;i++)
		for(int j=1;j<=q;j++)
		{
			int id=(A[i]+1ll*j*B[i])%q+1;
			if(op[id].tp==1)
			{
				update(op[id].pos);
				Dec(s,a[op[id].pos]);
				a[op[id].pos]=Sub(op[id].val,taga)*inv[tagm]%P;
				Inc(s,a[op[id].pos]);
			}
			else if(op[id].tp==2)
				Inc(taga,op[id].val);
			else if(op[id].tp==3)
			{
				if(op[id].val!=0)
					tagm=tagm*op[id].val%P,
					taga=taga*op[id].val%P;
				else
				{
					tagm=1;taga=s=0;
					Cover(0);
				}
			}
			else if(op[id].tp==4)
			{
				s=1ll*n*op[id].val%P;
				taga=0;tagm=1;
				Cover(op[id].val);
			}
			else if(op[id].tp==5)
			{
				update(op[id].pos);
				Inc(Ans,(a[op[id].pos]*tagm+taga)%P);
			}
			else if(op[id].tp==6)
				Inc(Ans,(s*tagm+1ll*n*taga)%P);
		}
	printf("%lld\n",Ans);
}
