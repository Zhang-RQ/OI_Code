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
    int l,r,val,pri;
}Treap[100000];
inline void Lrotate(int &x)
{
    int y=Treap[x].r;
    Treap[x].r=Treap[y].l;
    Treap[y].l=x;
    x=y;
}
inline void Rrotate(int &x)
{
    int y=Treap[x].l;
    Treap[x].l=Treap[y].r;
    Treap[y].r=x;
    x=y;
}

int main()
{

}
