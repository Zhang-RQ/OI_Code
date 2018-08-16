#include<bits/stdc++.h>

using namespace std;

const int P=2000000;
const int MAXN=14;

typedef long long ll;

char s[MAXN];
int n,m,blk[MAXN][MAXN],pw[MAXN],idx;
int tot[2],hsh[P],st[2][P],Ex,Ey;
ll val[2][P],Ans;

void init()
{
    idx=0;
    tot[0]=1;
    val[0][1]=1;
    st[0][1]=0;
    for(int i=1;i<=m;i++) pw[i]=i<<1;
}

void Hash_insert(ll v,int s)
{
//    printf("insert %lld @ %d\n",v,s);
    int x=s%P;
    while(hsh[x])
    {
        if(st[idx][hsh[x]]==s)
        {
            val[idx][hsh[x]]+=v;
            return;
        }
        if(++x==P) x=0;
    }
    ++tot[idx];
    st[idx][tot[idx]]=s;
    val[idx][tot[idx]]=v;
    hsh[x]=tot[idx];
}

void solve()
{
    for(int i=1;i<=n;i++)
    {
        for(int k=1;k<=tot[idx];k++) st[idx][k]<<=2;
        for(int j=1;j<=m;j++)
        {
            idx^=1;tot[idx]=0;ll v;
            memset(hsh,0,sizeof hsh);
            for(int k=1,s,left,up;k<=tot[idx^1];k++)
            {
                s=st[idx^1][k],v=val[idx^1][k];
                left=(s>>pw[j-1])%4;up=(s>>pw[j])%4;
                if(blk[i][j])
                {
                    if(left+up==0)
                        Hash_insert(v,s);
                }
                else if(left+up==0)
                {
                    if(blk[i+1][j]||blk[i][j+1]) continue;
                    s+=(1<<pw[j-1])+(2<<pw[j]);
                    Hash_insert(v,s);
                }
                else if(!left&&up)
                {
                    if(!blk[i][j+1]) Hash_insert(v,s); //up -> right
                    if(!blk[i+1][j]) //up -> down
                    {
                        s=s-(up<<pw[j])+(up<<pw[j-1]);
                        Hash_insert(v,s);
                    }
                }
                else if(left&&!up)
                {
                    if(!blk[i+1][j]) Hash_insert(v,s);
                    if(!blk[i][j+1])
                    {
                        s=s-(left<<pw[j-1])+(left<<pw[j]);
                        Hash_insert(v,s);
                    }
                }
                else if(left+up==2)
                {
                    for(int pos=j+1,cnt=1;pos<=m;pos++)
                    {
                        if((s>>pw[pos])%4==1) ++cnt;
                        else if((s>>pw[pos])%4==2) --cnt;
                        if(!cnt) {s-=1<<pw[pos];break;}
                    }
                    s=s-(left<<pw[j-1])-(up<<pw[j]);
                    Hash_insert(v,s);
                }
                else if(left+up==4)
                {
                    for(int pos=j-2,cnt=1;pos>=0;--pos)
                    {
                        if((s>>pw[pos])%4==1) --cnt;
                        else if((s>>pw[pos])%4==2) ++cnt;
                        if(!cnt) {s+=1<<pw[pos];break;}
                    }
                    s=s-(left<<pw[j-1])-(up<<pw[j]);
                    Hash_insert(v,s);
                }
                else if(left==2&&up==1)
                {
                    s=s-(left<<pw[j-1])-(up<<pw[j]);
                    Hash_insert(v,s);
                }
                else if(left==1&&up==2)
                {
                    if(i==Ex&&j==Ey) Ans+=v;
                }
            }
        }
    }
    cout<<Ans<<endl;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            blk[i][j]=(s[j]=='*');
            if(s[j]=='.') Ex=i,Ey=j;
        }
    }
    for(int i=0;i<=m+1;i++) blk[0][i]=blk[n+1][i]=1;
    for(int i=0;i<=n+1;i++) blk[i][0]=blk[i][m+1]=1;
    init();solve();
}
