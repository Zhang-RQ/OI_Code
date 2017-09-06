#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int H,W,D,R;
int mp[2010][2010]={0};
int ans=0x3f3f3f3f;
int step[2010][2010][2];
struct state{
    int x,y;
    bool flag;
};
state add(int x,int y,bool flag)
{
    state ret;
    ret.x=x;
    ret.y=y;
    ret.flag=flag;
    return ret;
}
void bfs()
{
    memset(step,0x3f,sizeof(step));
    queue<state> q;
    state tmp;
    tmp.x=1,tmp.y=1;
    tmp.flag=true;
    step[1][1][1]=0;
    q.push(tmp);
    while(!q.empty())
    {
        //printf("%d  %d  %d   %d\n",tmp.x,tmp.y,tmp.flag,step[tmp.x][tmp.y][tmp.flag]);
        tmp=q.front();
        q.pop();
        if(tmp.x==H&&tmp.y==W) continue;
        if(mp[tmp.x][tmp.y+1]&&step[tmp.x][tmp.y][tmp.flag]+1<step[tmp.x][tmp.y+1][tmp.flag])
            q.push(add(tmp.x,tmp.y+1,tmp.flag)),step[tmp.x][tmp.y+1][tmp.flag]=step[tmp.x][tmp.y][tmp.flag]+1;
        if(tmp.y-1>0&&mp[tmp.x][tmp.y-1]&&step[tmp.x][tmp.y][tmp.flag]+1<step[tmp.x][tmp.y-1][tmp.flag])
            q.push(add(tmp.x,tmp.y-1,tmp.flag)),step[tmp.x][tmp.y-1][tmp.flag]=step[tmp.x][tmp.y][tmp.flag]+1;
        if(mp[tmp.x+1][tmp.y]&&step[tmp.x][tmp.y][tmp.flag]+1<step[tmp.x+1][tmp.y][tmp.flag])
            q.push(add(tmp.x+1,tmp.y,tmp.flag)),step[tmp.x+1][tmp.y][tmp.flag]=step[tmp.x][tmp.y][tmp.flag]+1;
        if(tmp.x-1>0&&mp[tmp.x-1][tmp.y]&&step[tmp.x][tmp.y][tmp.flag]+1<step[tmp.x-1][tmp.y][tmp.flag])
            q.push(add(tmp.x-1,tmp.y,tmp.flag)),step[tmp.x-1][tmp.y][tmp.flag]=step[tmp.x][tmp.y][tmp.flag]+1;
        if((tmp.x+D>0)&&(tmp.y+R>0)&&tmp.flag&&mp[tmp.x+D][tmp.y+R]&&step[tmp.x+D][tmp.y+R][0]>step[tmp.x][tmp.y][1]+1)
            q.push(add(tmp.x+D,tmp.y+R,false)),step[tmp.x+D][tmp.y+R][0]=step[tmp.x][tmp.y][1]+1;
    }
    return;
}
int main()
{
    char tmp,ttt;
    scanf("%d%d%d%d",&H,&W,&D,&R);
    scanf("%c",&ttt);
    for(int i=1;i<=H;i++)
    {
        for(int j=1;j<=W;j++)
        {
            scanf("%c",&tmp);
            if(tmp=='.') mp[i][j]=1;
            if(tmp=='#') mp[i][j]=0;
        }
        scanf("%c",&ttt);
    }
    bfs();
    if(step[H][W][0]==0x3f3f3f3f&&step[H][W][1]==0x3f3f3f3f) puts("-1\n");
    else printf("%d\n",min(step[H][W][0],step[H][W][1]));
    return 0;
}
