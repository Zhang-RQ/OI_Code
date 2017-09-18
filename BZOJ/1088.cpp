#include <cstdio>
#include <cstring>
#define MAXN 10010
int l1[MAXN],l2[MAXN],n;
int check()
{
    int i,j;
    for(i=2;i<=n;i++)
        l1[i+1]=l2[i]-l1[i]-l1[i-1];
    if(l1[n+1]) return 0;
    return 1;
}
int main()
{
    int i,j,cnt=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&l2[i]);
    for(i=0;i<=l2[1];i++)
    {
        memset(l1,0,sizeof(l1));  
        l1[1]=i;
        l1[2]=l2[1]-i;
        if(check()) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
