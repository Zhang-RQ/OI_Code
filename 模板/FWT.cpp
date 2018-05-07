const int P=1E9+7;
const int rev=500000004;
void FWT(int *a,int n)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                int x=a[j+k],y=a[j+k+(i>>1)];
                a[i+j]=(x+y)%P,a[j+k+(i>>1)]=(x-y+P)%P;
                //xor:a[j+k]=x+y,a[j+k+(i>>1)]=x-y;
                //and:a[j+k]=x+y;a[j+k+(i>>1)]=y;
                //or:a[j+k]=x;a[j+k+(i>>1)]=x+y;
            }
}

void UFWT(int *a,int n)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                int x=a[j+k],y=a[j+k+(i>>1)];
                a[j+k]=1LL*(x+y)*rev%P,a[j+k+(i>>1)]=(1LL*(x-y)*rev%P+P)%P;
                //xor:a[j+k]=(x+y)/2,a[j+k+i]=(x-y)/2;
                //and:a[j+k]=x-y;a[j+k+i]=y;
                //or:a[j+k]=x;a[j+k+i]=y-x;
            }
}
void solve(int a[],int b[],int n)
{
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%P;
    UFWT(a,n);
}
