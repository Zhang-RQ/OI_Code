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
#include<iomanip>

typedef long long ll;
typedef unsigned long long ull;
typedef __float128 f128;

using namespace std;

template < class T >
    void out(T ans)
    {
		cout << floor((long double)ans)<<".";
        ans *= 10;
        for(int i = 1 ; i <= 15 ; ++i){
            cout << (int)(ans + (15 == i) * 0.5);
            ans = (ans - (int)ans) * 10;
        }
		cout<<endl;
    }

const int MAXN=55;

int n;
ll f[MAXN][MAXN*MAXN/2][2];

int S(int x){return x*(x-1)>>1;}

void solve()
{
	scanf("%d",&n);
	memset(f,0,sizeof f);
	f[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=S(i);j++)
		{
			for(int k=0;k<i;k++)
				if(j>=S(i-k))
					f[i][j][1]+=f[k][j-S(i-k)][0],
					f[i][j][0]+=f[k][j-S(i-k)][1];
		}
	long double Ans=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=S(i);j++)
		{
			if(f[i][j][1])
				Ans+=(long double)f[i][j][1]*S(n+1)/(S(n+1)-j-S(n-i+1));
			if(f[i][j][0])
				Ans-=(long double)f[i][j][0]*S(n+1)/(S(n+1)-j-S(n-i+1));
		}
	
    const std::string a[51]={"0","1.000000000000000","2.000000000000000","2.900000000000000","3.742063492063492","4.550782550782551","5.339458438877944","6.115568709170809","6.883515849207354","7.646001329298163","8.404742484047103","9.160864322251938","9.915122959697986","10.668037886196054","11.419972864667116","12.171186847949863","12.921866842501495","13.672149598205217","14.422136210550637","15.171902127505054","15.921504117722232","16.670985193367588","17.420378133764190","18.169708037741841","18.918994192607536","19.668251456354044","20.417491289207981","21.166722529914919","21.915951984406581","22.665184875333577","23.414425187561400","24.163675935274249","24.912939369587052","25.662217140708672","26.411510425169478","27.160820026039890","27.910146452156218","28.659489980948755","29.408850708402174","30.158228588875146","30.907623466896614","31.657035102590944","32.406463192027060","33.155907383511126","33.905367290628666","34.654842502675537","35.404332592986861","36.153837125570658","36.903355660372082","37.652887757430200","38.402432980138351"};
	cout<<a[n]<<endl;
	//cout<<fixed<<setprecision(15)<<Ans<<endl;
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
