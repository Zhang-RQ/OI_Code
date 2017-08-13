#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int DP[2010][2010];
bool flag[2010];
int maxn(int a,int b)
{
    if(a<b) return b;
    else return a;
}
struct Node{
    int val,gou;
}decoration[2010];
bool cmp(Node a,Node b)
{
    return a.gou>b.gou;
}
int main()
{
    int ans=-10000;
    int n;
    memset(DP,-1000000,sizeof(DP));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&decoration[i].gou,&decoration[i].val);
    sort(decoration+1,decoration+1+n,cmp);
    DP[0][1]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            DP[i][j]=maxn(DP[i-1][j],DP[i-1][maxn(j-decoration[i].gou,0)+1]+decoration[i].val);
            if(i==n&&DP[n][j]>ans) ans=DP[n][j];
        }
    }
    printf("%d\n",ans);
}
/*
题解：我表示这道题是在老师和同学耗尽心思的讲解中才勉强懂了一点却因为输入输出调了十遍RE。。。

不过很开心的是这道题在他人的讲解和我看题解的过程中让我对动归的理解比以前稍微好了一点（虽然还是很菜），希望能有更多提升。

好啦看题目，这道题其实就是背包的容量在不停的变化，用f[i][j]来表示挂完第i个物品后还剩j个挂钩，那么转移方程为f[i][j]=max(f[i-1][j],f[i-1][max(j-a[i],0)+1]+b[i]);

为什么这么写呢？解释一下：首先f[i][j]=f[i-1][j]很好懂就是指现在这个物品不挂，可取得的喜悦值,那么f[i-1][max(j-a[i],0)+1]是什么意思呢，我们先看j-a[i]+1,这是指上一次的挂钩值，那么后面的这个式子意思是把这个饰件挂上的喜悦值+上一次的喜悦值，但是j-a[i]是有可能小于0的，即如果第i个物品挂上去的话这次不可能就j个挂钩，这个时候我们就假设上一次只剩了一个挂钩，这样j个挂钩都是现在第i个物品带来的，即使j-a[i]<0,也可以当做我们把多余j的挂钩给舍去了。为什么我们要假设上一次只剩了一个挂钩呢？因为当前物品如果能挂上去，说明上一次多出的挂钩数一定大于等于1，却不能保证大于1，所以我们至多只能设上次只剩了一个挂钩（只有一是能被确定的），这就是这个式子让我当时最不理解的地方。。。。。

好啦，第二个重点，在做动归前我们需要将a数组排一下序，为何因为我们会发现如果不排序的话我们这次挂上这个饰品，即使j是负数也并不是不合法的，因为挂饰间可以互换位置，只要后面挂饰的挂钩能够把j在最后补成自然数就可以了，那样就会导致动归的循环不确定，没法一步步推，所以要进行排序。
http://www.cnblogs.com/2014nhc/p/6231288.html
*/
