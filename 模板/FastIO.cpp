struct FastIO{
    static const int S=1e7;
    int wpos;
    char wbuf[S];
    FastIO():wpos(0){}

    inline int xchar()
    {
        static char buf[S];
        static int len=0,pos=0;
        if(pos==len)
            pos=0,len=fread(buf,1,S,stdin);
        return buf[pos++];
    }

    inline int operator () ()
    {
        int c=xchar(),x=0,ng=0;
        while (!isdigit(c)) c=xchar(),ng|=(c=='-');
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline ll operator ! ()
    {
        int c=xchar(),ng=0;ll x=0;
        while(!isdigit(c)) c=xchar(),ng|=(c=='-');
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline void wchar(int x)
    {
        if(wpos==S) fwrite(wbuf,1,S,stdout),wpos=0;
        wbuf[wpos++]=x;
    }

    inline void operator () (ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar('\n');
    }

    inline void space(ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar(' ');
    }

    inline void nextline() {wchar('\n');}

    ~FastIO() {if(wpos) fwrite(wbuf,1,wpos,stdout),wpos=0;}
}io;