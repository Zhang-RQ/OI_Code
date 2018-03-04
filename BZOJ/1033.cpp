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
#include<bitset>
using namespace std;
typedef long long ll;
#define MAXN 10
int mv[10][5]={
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {0,-1, 0},
    {0, 0,-1},
    {0, 1, 0},
    {0, 0, 1},
    {0,-1, 0},
    {0, 0,-1}
};
struct Map{
    bool blocked[MAXN][MAXN];
    int info[MAXN][MAXN];
    int n,m,time_now;
    bool cake_lost;
    inline void init();
    inline void first_update();//1秒开始时的更新
    inline void tower_attack();
    inline void last_update();//1秒结束时的更新
}game_map;
struct Ant{
    int x,y;
    int birth_time,HP;
    bool got_cake;
    bool operator <(Ant &a) const
    {
        return birth_time<a.birth_time;
    }
    bool operator == (Ant a)
    {
        return x==a.x&&y==a.y&&birth_time==a.birth_time;
    }
    inline void move();
};
vector<Ant> ant;
struct Tower{
    int x,y;
    int damage,range,targetx,targety;
    inline void choose();
    inline double dis(int x,int y);
    inline void attack();
    inline bool check(Ant a);
}tower[25];
inline double Tower::dis(int ax,int ay)
{
    return sqrt(abs(x-ax)*abs(x-ax)+abs(y-ay)*abs(y-ay));
}
inline void Tower::choose()
{
    if(game_map.cake_lost)
        for(int i=0;i<(signed)ant.size();i++)
            if(ant[i].got_cake&&dis(ant[i].x,ant[i].y)<=range*1.0)
                {targetx=ant[i].x;targety=ant[i].y;return;}
    double mindis=range;
    int tx=-1,ty,tyear=0;
    for(int i=0;i<(signed)ant.size();i++)
        if(dis(ant[i].x,ant[i].y)<mindis)
        {
            tx=ant[i].x;
            ty=ant[i].y;
            mindis=dis(ant[i].x,ant[i].y);
            tyear=game_map.time_now-ant[i].birth_time+1;
        }
        else if(game_map.time_now-ant[i].birth_time+1>tyear)
        {
            tx=ant[i].x;
            ty=ant[i].y;
            mindis=dis(ant[i].x,ant[i].y);
            tyear=game_map.time_now-ant[i].birth_time+1;
        }
    targetx=tx;
    targety=ty;
    return;
}
inline bool Tower::check(Ant l)
{
    double k,b,a,b_,c;
    k=(x-l.x)/(y-l.y);
    b=y-k*x;
    
}
inline void Tower::attack()
{
    if(targetx==-1) return;
    for(int i=0;i<(signed)ant.size();i++)
    {

    }
}
inline void Map::init()
{
    memset(blocked,0,sizeof(blocked));
    memset(info,0,sizeof(info));
    n=m=cake_lost=0;
    time_now=1;
}
inline bool inside(int x,int y)
{
    return 0<=x&&x<=game_map.n&&0<=y&&y<=game_map.m;
}
inline void del_ant(Ant a)
{
    ant.erase(remove(ant.begin(),ant.end(),a),ant.end());
}
inline void Map::first_update()
{
    if((signed)ant.size()<6)
    {
        Ant tmp;
        tmp.x=tmp.y=tmp.got_cake=0;
        tmp.birth_time=game_map.time_now;
        tmp.HP=4*pow(1.1,(game_map.time_now-1)/6+1);
        ant.push_back(tmp);
    }
    for(int i=0;i<(signed)ant.size();i++)
    {
        if(ant[i].got_cake) info[ant[i].x][ant[i].y]+=5;
        else info[ant[i].x][ant[i].y]+=2;
        ant[i].move();
    }
    return;
}
inline void Map::last_update()
{
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            if(!info[i][j]) --info[i][j];
    sort(ant.begin(),ant.end());
    ++time_now;
    return;
}
inline void Ant::move()
{
    int x_,y_,toward;
    int max_info=0,tx=-1,ty;
    for(int i=1;i<=4;i++)
    {
        x_=x+mv[i][1];
        y_=y+mv[i][2];
        if(!game_map.blocked[x_][y_]&&inside(x_,y_)&&game_map.info[x_][y_]>max_info)
            tx=x_,ty=y_,max_info=game_map.info[x_][y_],toward=i;
    }
    if(!(game_map.time_now-birth_time+1)%5&&tx!=-1)
    {
        toward+=4;
        do{
            --toward;
            x_=x+mv[toward][1];
            y_=y+mv[toward][2];
        }while(!(!game_map.blocked[x_][y_]&&inside(x_,y_)));
        tx=x_,ty=y_;
    }
    if(tx==-1) return;
    else game_map.blocked[x][y]=0,x=tx,y=ty;
    game_map.blocked[x][y]=1;
    if(x==game_map.n&&y==game_map.m)
    {
        game_map.cake_lost=1;
        got_cake=1;
        HP*=1.5;
    }
    return;
}
int main()
{

}
