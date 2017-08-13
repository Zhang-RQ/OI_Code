#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
  int A[100],n;
  scanf("%d",&n);
  printf("Hello World\n");
  for(int i=1;i<=n;i++) scanf("%d",&A[i]);
  sort(A,A+n+1);
  for(int i=1;i<=n;i++) printf("%d\n",A[i]);
  return 0;
}
