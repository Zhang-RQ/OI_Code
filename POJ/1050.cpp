#include<cstdio>
using namespace std;
int M[10010][10010];
int main()
{
    int n;
    int temp=-1;
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&M[i][j]);
            if(temp<0) temp=M[i][j];
            else temp+=M[i][j];
            if(temp>ans) ans=temp;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            temp=-1;
            for(int k=1;k<=n;k++)
            {
                M[i][k]+=M[j][k];
                if(temp<0) temp=M[i][k];
                else temp+=M[i][k];
                if(temp>ans) ans=temp;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
