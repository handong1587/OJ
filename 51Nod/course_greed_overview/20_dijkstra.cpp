#include <stdio.h>
#include <algorithm>

using namespace std;

#define maxn 1005
#define INF 0x3f3f3f3f
#define _max_(a,b) ((a)>(b)?(a):(b))
#define _min_(a,b) ((a)<(b)?(a):(b))

int n,m,start,end;
int score[maxn];
int time[maxn][maxn];

bool used[maxn];

struct Room
{
    int timeTo;
    int scoreOf;
};
Room rm[maxn];

bool cmp(Room r1, Room r2)
{
    if(r1.timeTo == r2.timeTo){
        return r1.scoreOf > r2.scoreOf;
    }
    return r1.timeTo < r2.timeTo;
}

void init()
{
    for(int i=0;i<maxn;i++){
        for(int j=0;j<maxn;j++){
            time[i][j] = INF;
        }
        rm[i].timeTo = INF;
        rm[i].scoreOf = 0;
    }
}

void dijkstra()
{
    rm[start].timeTo = 0;
    rm[start].scoreOf = score[start];

    while(true){
        int v = -1;
        for(int u=0;u<n;u++){
            if(!used[u] && (v==-1 || rm[u].timeTo < rm[v].timeTo)){
                v = u;
            }
        }
        if(v==-1){
             break;
        }
        used[v] = true;
        for(int u=0;u<n;u++){
            if(rm[u].timeTo >= rm[v].timeTo + time[v][u]){
                if(rm[u].timeTo > rm[v].timeTo + time[v][u]){ // find new way, change score
                    rm[u].scoreOf = rm[v].scoreOf + score[u];
                }
                else if(rm[u].scoreOf < rm[v].scoreOf + score[u]){ // same distance, choose max score
                    rm[u].scoreOf = rm[v].scoreOf + score[u];
                }
                rm[u].timeTo = rm[v].timeTo + time[v][u];
            }
        }
    }
}

int main()
{
    freopen("20_dijkstra_case7.txt","r",stdin);
    init();
    scanf("%d %d %d %d",&n,&m,&start,&end);
    for(int i=0;i<n;i++){
        scanf("%d",&score[i]);
    }
    for(int i=0;i<m;i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        time[x][y] = z;
        time[y][x] = z;
    }

    dijkstra();
    printf("%d %d\n",rm[end].timeTo, rm[end].scoreOf);

    return 0;
}
