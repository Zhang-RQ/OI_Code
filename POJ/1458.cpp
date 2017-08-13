#include<cstdio>
#include<memory>
#include<cstring>
using namespace std;
char in1[1010],in2[1010];
int F[1010][1010];
int maxi(int a,int b)
{
    if(a>b) return a;
    else return b;
}
void DP(int len1,int len2)
{
    memset(F,0,sizeof(F));
    for(int i=0;i<len1;i++)
    {
        for(int j=0;j<len2;j++)
        {
            if(in1[i]==in2[j]) F[i][j]=F[i-1][j-1]+1;
            else F[i][j]=maxi(F[i][j-1],F[i-1][j]);
        }
    }
}
int main()
{
    while(scanf("%s%s",&in1,&in2)!=EOF)
    {

        DP(strlen(in1),strlen(in2));
        printf("%d\n",F[strlen(in1)-1][strlen(in2)-1]);
    }
}
