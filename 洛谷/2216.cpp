#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int minn[1010][1010],maxn[1010][1010],mp[1010][1010];//maxn表示mp[i-k][j-k]--mp[i][k]最小值
deque<int> maxv;
deque<int> minv;
int main()
{
    int a,b,n;
    scanf("%d%d%d",&a,&b,&n);
    for(int i=1;i<=a;i++)
        for(int j=1;j<=b;j++)
        scanf("%d",&mp[i][j]);
    for(int i=1;i<=a;i++)//处理行
    {
        maxv.clear();
        minv.clear();
        maxn[i][0]=0;
        minn[i][0]=0x3f3f3f3f;
        for(int j=1;j<=b;j++)
        {
            while(!maxv.empty()&&(j-maxv.front()+1>n)) maxv.pop_front();
            while(!maxv.empty()&&(mp[i][maxv.back()]<=mp[i][j])) maxv.pop_back();
            maxv.push_back(j);
            maxn[i][j]=mp[i][maxv.front()];
            ///////////////////////////////////////////////////////////
            while(!minv.empty()&&(j-minv.front()+1>n)) minv.pop_front();
            while(!minv.empty()&&(mp[i][minv.back()]>=mp[i][j])) minv.pop_back();
            minv.push_back(j);
            minn[i][j]=mp[i][minv.front()];
        }
    }
    int ans=0x3f3f3f3f;
    for(int j=n;j<=b;j++)//j枚举列
    {
        maxv.clear();
        minv.clear();
        for(int i=1;i<=a;i++)
        {
            while(!maxv.empty()&&(i-maxv.front()+1>n)) maxv.pop_front();
            while(!maxv.empty()&&(maxn[maxv.back()][j]<=maxn[i][j])) maxv.pop_back();
            maxv.push_back(i);
            ///////////////////////////////////////////////////////////
            while(!minv.empty()&&(i-minv.front()+1>n)) minv.pop_front();
            while(!minv.empty()&&(minn[minv.back()][j]>=minn[i][j])) minv.pop_back();
            minv.push_back(i);
            if(i>=n) ans=min(ans,maxn[maxv.front()][j]-minn[minv.front()][j]);
        }
    }
    printf("%d\n",ans);
}
