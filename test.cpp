#include<bits/stdc++.h>
using namespace std;
//ABCDEFGHI JKLMNOPQRS TUVWXYZ
//123456789 0123456789 0123456
int into[26]={10,3,6,4,6,3,3,7,5,4,7,12,9,1,8,2,3,2,8,2,3,4,4,7,9,1};
bool cmp(int a,int b){
return into[a]<into[b];
}
int main(){
char ZTB233[100]={"LAMLZDBKTCIS"};
int transformer[100];
for(int i=0;i<strlen(ZTB233);i++)
transformer[i]=ZTB233[i]-'A';
sort(transformer,transformer+strlen(ZTB233),cmp);
for(int i=0;i<strlen(ZTB233);i++)
ZTB233[i]=transformer[i]+'A';
puts(ZTB233);
return 0;
}
