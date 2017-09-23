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
struct node{
    string job;
    bool turn;
}P[100010];
int main()
{
    int n,z;
    int a,b;
    ios::sync_with_stdio(0);
    cin>>n>>z;
    for(int i=1;i<=n;i++)
        cin>>P[i].turn>>P[i].job;
    int pos=1;
    for(int i=1;i<=z;i++)
    {
        cin>>a>>b;
        if(P[pos].turn)
        {
            if(a) pos=(pos-b+n)%n;
            else pos=(pos+b)%n;
            if(!pos)  pos+=n;
        }
        else
        {
            if(a) pos=(pos+b)%n;
            else pos=(pos-b+n)%n;
            if(!pos) pos+=n;
        }
    }
    cout<<P[pos].job<<endl;
}
