#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<windows.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
char s[110];
char tmp[120]="mkdir ";
char filename[120];
int n,a;
int flag;
int range[110];
int main()
{
    cout<<"请输入题目名称(英文):"<<endl;
    cin>>s;
    system("g++ std.cpp -o std.exe -O2");
    system("g++ maker.cpp -o maker.exe -O2");
    strcat(tmp,s);
    system(tmp);
    cout<<"请输入测试组数:"<<endl;
    cin>>n;
    cout<<"请输入每组的数据范围:"<<endl;
    for(int i=1;i<=n;i++)
        cin>>range[i];
    cout<<"是否生成空的val.cpp?(0/1)"<<endl;
    cin>>a;
    cout<<"是否删除垃圾文件?(0/1)"<<endl;
    cin>>flag;
    for(int i=1;i<=n;i++)
    {
        char t[120];
        sprintf(t,"maker %d > %s/%s%d.in",range[i],s,s,i);
        system(t);
        sprintf(t,"std < %s/%s%d.in > %s/%s%d.out",s,s,i,s,s,i);
        system(t);
    }
    if(a)
    {
        FILE *VAL=fopen("val.cpp","w");
        fprintf(VAL,"int main()\n{\n\treturn 0;\n}");
        sprintf(tmp,"copy val.cpp \"%s/\"",s);
        system(tmp);
        if(flag) system("del val.cpp");
    }
    sprintf(tmp,"copy std.cpp \"%s/\"",s);
    system(tmp);
    system("del std.exe");
    system("del maker.exe");
    if(flag)
    {
        system("del std.cpp");
        system("del maker.cpp");
    }
}
