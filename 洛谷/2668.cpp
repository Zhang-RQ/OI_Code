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
int card[20],com[20];
const int to[20]={0,13,1,2,3,4,5,6,7,8,9,10,11,12};
//将王看为0号,1看为13号(因为可以接在K后面)
int T,n,tmp,ans;
int calc() //计算不出顺子时的最小步数
{
    memset(com,0,sizeof(com));
    int ret=0;
    for(int i=0;i<=13;i++)
        ++com[card[i]];//点数在无顺子时不用考虑，存一下单牌、对、三张相同、炸弹的数量
        //com[1]是单牌的数量，com[2]是对的数量，com[3]是3张相同的数量,com[4]是炸弹数量
    while(com[4]>0&&com[2]>1)//4带2对
        com[4]-=1,com[2]-=2,++ret;
    while(com[4]>0&&com[1]>1)//4带2单(优先出单牌)
        com[4]-=1,com[1]-=2,++ret;
    while(com[4]>0&&com[2]>0)//4带1对(相当于4带2张一样的单牌)
        com[4]-=1,com[2]-=1,++ret;
    while(com[3]>0&&com[2]>0)//3带1对
        com[3]-=1,com[2]-=1,++ret;
    while(com[3]>0&&com[1]>0)//3带1单
        com[3]-=1,com[1]-=1,++ret;
    return ret+com[4]+com[3]+com[2]+com[1];
}
void search(int step)
{
    if(step>ans) return; //当前步数劣于当前最优答案，剪枝
    ans=min(ans,step+calc());//计算如果不出顺子时的答案，并存储
    for(int i=2,pos,cnt;i<=13;i++)//枚举顺子开始的地方。因为不能从2(映射后为1)开始顺子，故从2(映射前为3)开始枚举,13为原来的1
        for(int j=1;j<=3;j++)//枚举顺子中每张的牌数
        if(card[i]>=j)
        {
            for(pos=i,cnt=0;card[pos]>=j;pos++)//找到此时最远位置
                card[pos]-=j,cnt+=j;
            --pos;
            for(;pos>=i;pos--)
            {
                if(cnt>=5)
                    search(step+1);
                card[pos]+=j;
                cnt-=j;
            }
        }
}
int main()
{
    scanf("%d%d",&T,&n);
    while(T--)
    {
        memset(card,0,sizeof(card));
        ans=100;
        for(int i=1;i<=n;i++)
            scanf("%d%*d",&tmp),++card[to[tmp]];
        search(0);
        printf("%d\n",ans);
    }
}
