int n,m;//n为变量个数 m为方程个数
bitset<MAXN> a[MAXN];

void gauss() //高斯约当消元
{
    int now=1;
    for(int i=1;i<=n;i++)
    {
        int pos=now;
        while(pos<=m&&!a[pos][i]) ++pos;
        if(pos>m) continue;
        swap(a[pos],a[now]);
        for(int j=1;j<=m;j++)
            if(j!=now&&a[j][i])
                a[j]^=a[now];
        ++now;
    }
}