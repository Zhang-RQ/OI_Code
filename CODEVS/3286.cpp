#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int P=99999997;
int C[maxn];
long long ans=0;
struct a{
  int val,pos;
};
a A[maxn];
a B[maxn];
bool cmp(a A,a B)
{
  return A.val<B.val;
}
void gbpx(int l,int r);
void gb(int l,int mid,int r);
int main()
{
  int n;
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&A[i].val),A[i].pos=i;
  for(int i=1;i<=n;i++) scanf("%d",&B[i].val),B[i].pos=i;
  sort(A+1,A+1+n,cmp);
  sort(B+1,B+1+n,cmp);
  for(int i=1;i<=n;i++) C[A[i].pos]=B[i].pos;
  gbpx(1,n);
  //for(int i=1;i<=n;i++) printf("%d ",C[i]);
  ans%=P;
  printf("%lld\n",ans);
}
void gbpx(int l,int r)
{
  if(l<r)
  {
    int mid=(l+r)/2;
    gbpx(l,mid);
    gbpx(mid+1,r);
    gb(l,mid,r);
  }
}
void gb(int l,int mid,int r)
{
  int L[maxn/2],R[maxn/2];
  int lnum=mid-l+1;
  int rnum=r-mid;
  int i,j;
  for(i=0;i<lnum;i++) L[i]=C[l+i];
  for(i=0;i<rnum;i++) R[i]=C[mid+i+1];
  i=j=0;
  int k;
  for(k=l;k<r&&i<lnum&&j<rnum;k++)
  {
    if(L[i]<=R[j]) C[k]=L[i++];
    else
    {
      C[k]=R[j++];
      ans=(ans+lnum-i)%P;
    }
  }
  if(i>=lnum)
  {
    for(;k<=r;++k,++j)
    {
      C[k]=R[j];
    }
  }
  else
  {
    for(;k<=r;++k,++i)
    {
      C[k]=L[i];
    }
  }
}
