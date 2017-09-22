#include<cstdio>
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
typedef set<int> Set;
#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())
struct cmp{
    bool operator () (const Set &x,const Set &y)
    {
        if(x.size()!=y.size()) return x.size()<y.size();
        else{
            Set::iterator itx=x.begin();
            Set::iterator ity=y.begin();
            while(itx!=x.end()&&*itx==*ity) itx++,ity++;
            if(itx==x.end()) return false;
            return *itx<*ity;
        }
    }
};
map<Set,int,cmp> mp;
vector<Set> v;
stack<int> s;

char str[10];

int id(Set x)
{
    if(mp[x]!=0) return mp[x];
    v.push_back(x);
    return mp[x]=v.size()-1;
}



int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",str);
        if(str[0]=='P') s.push(id(Set()));
        else if(str[0]=='D') s.push(s.top());
        else{
            Set x1=v[s.top()]; s.pop();
            Set x2=v[s.top()]; s.pop();
            Set y;
            if(str[0]=='U') set_union(ALL(x1),ALL(x2),INS(y));
            else if(str[0]=='I') set_intersection(ALL(x1),ALL(x2),INS(y));
            else if(str[0]=='A') {
                y=x2;
                y.insert(id(x1));
            }
            s.push(id(y));
        }
        printf("%d\n",v[s.top()].size());
    }
}
