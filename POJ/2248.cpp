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
const int MAXN = 100 + 10;

int num[MAXN], n, b[MAXN], ID;

int dfs(int step)
{
    if(num[step - 1] == n) return 1;
    if(step > ID)return 0;
    register int tmp;
    for(register int i = step - 1;i >= 1;-- i)
        for(register int j = i;j >= 1;-- j)
        {
            tmp = num[i] + num[j];
            if(tmp <= num[step - 1] || b[tmp] || tmp > n)continue;
            num[step] = tmp;
            b[tmp] = 1;
            if(dfs(step + 1)) return 1;
            b[tmp] = 0;
        }
    return 0;
}

int main()
{
    num[1] = 1;
    while(scanf("%d", &n) != EOF && n)
    {
        for(register int i = 1;i <= n;++ i)
        {
            ID = i;
            memset(b, 0, sizeof(b));
            if(dfs(2))
            {
                for(register int j = 1;j <= i;++ j)
                    printf("%d ", num[j]);
                putchar('\n');
                break;
            }
        }
    }
    return 0;
}

/*int arr[20];
int n;
int ans=20;
int lg2[110];
void dfs(int pos)
{
    if(lg2[(n/arr[pos-1])]+pos-1>ans) return;
    if(pos>ans) return;
    for(int i=1;i<pos;i++)
    {
        if(arr[i]+arr[1]>n) break;
        for(int j=1;j<i;j++)
        {
            if(arr[i]+arr[j]>n) break;
            if(arr[i]+arr[j]==n) {ans=min(ans,pos);return;}
            arr[pos]=arr[i]+arr[j];
            dfs(pos+1);
        }
    }
    return ;
}
int main()
{
    for(int i=2;i<=109;i++) lg2[i]=lg2[i>>1]+1;
    while(~scanf("%d",&n)&&n)
    {
        ans=20;
        arr[1]=1;
        arr[2]=2;
        dfs(3);
        printf("%d\n",ans);
    }
}
*/
