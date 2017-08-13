#include<cstdio>
#include<queue> //STL 

using namespace std;
int n,m;

int head[2505],nxt[7000],point[7000],w[7000];
int d[2505];
int vis[2505];
int tot;
void add(int x,int y,int z){
    ++tot;
    point[tot]=y;//2.
    w[tot]=z;
    nxt[tot]=head[x];//3.
    head[x]=tot;
}
int s,t;
struct N{
    int x,w;
    friend bool operator < (N a,N b){
        return a.w>b.w;    
    }
    N(int a=0,int b=0){
        x=a;w=b;    
    }
};
priority_queue<N> q;
int main(){
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    for(int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    for(int i=1;i<=n;i++) d[i]=10000000;//0.
    d[s]=0;
    q.push(N(s,0));
    while(!q.empty()){
        int x=q.top().x;q.pop();
        if(vis[x]) continue;
        //2.
        vis[x]=1;
        for(int j=head[x];j;j=nxt[j]){
            if(!vis[point[j]]&&d[point[j]]>d[x]+w[j]){
                    d[point[j]]=d[x]+w[j];
                    q.push(N(point[j],d[point[j]]));
            }
        }    
    }
    printf("%d\n",d[t]);
    

    return 0;
}

/*
6 6
3 5
5 6
5 2
6 4
2 4
4 1
*/
