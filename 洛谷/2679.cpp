#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
int F[2][210][210][2];
char a[1200],b[300];
int N,M,K;
const int P=1000000007;
int main()
{
    ios::sync_with_stdio(0);
    ll tmp;
    cin>>N>>M>>K;
    cin>>(a+1)>>(b+1);
    F[0][0][0][0]=1;
    for(int i=1;i<=N;i++)
    {
        int ops=i&1;
        F[ops][0][0][0]=1;
        for(int j=1;j<=min(i,M);j++)
            for(int k=1;k<=min(j,K);k++)
            {
                F[ops][j][k][1]=0;F[ops][j][k][0]=0;
                tmp=(ll)F[ops^1][j][k][0]+(ll)F[ops^1][j][k][1];
                F[ops][j][k][0]=tmp%P;
                if(a[i]==b[j])
                {
                    tmp=(ll)F[ops^1][j-1][k][1]+(ll)F[ops^1][j-1][k-1][0]+(ll)F[ops^1][j-1][k-1][1];
                    F[ops][j][k][1]=tmp%P;
                }
            }
    }
    cout<<(F[N&1][M][K][0]+F[N&1][M][K][1])%P<<endl;
}
