#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*int searchn(int N[],int l,int r,int value)//找到第一个大于等于value的数字
{
    while(l<r)
    {
        int mid=(l+r)/2;
        if(N[mid]>=value) r=mid;
        else l=mid+1;
    }
    return l;
}*/
int main()
{
    int n,N[100010],D[100100];
    while(scanf("%d",&n)!=EOF)
    {
        memset(N,0,sizeof(N));
        memset(D,0,sizeof(D));
        for(int i=1;i<=n;i++) scanf("%d",&N[i]);
        D[1]=N[1];
        int len=1;
        for(int i=2;i<=n;i++)
        {
            if(N[i]>D[len]) D[++len]=N[i];
            else{
            int pos=lower_bound(D,D+len,N[i])-D;
            D[pos]=N[i];
            }
        }
        printf("%d\n",len);
    }
}
