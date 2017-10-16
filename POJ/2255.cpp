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
void Deal(const char* Preorder, const char* Inorder, int Length)
{
    switch(Length)
    {
    case 0:
        break;
    case 1 :
        cout << (*Preorder);
        break;
    default:
        const char Root = Preorder[0];
        const char* RootIndex = find(Inorder, Inorder + Length, Root);
        int Index = RootIndex - Inorder;
        Deal(Preorder + 1, Inorder, Index);
        Deal(Preorder + 1 + Index, RootIndex + 1, Length - Index - 1);
        cout << Root;
        break;
    }



}

int main()
{
    string Preorder;
    string Inorder;
    while(cin >> Preorder)
    {
        cin >> Inorder;
        Deal(Preorder.c_str(), Inorder.c_str(), Preorder.size());
        cout << endl;
    }
    return 0;
}
