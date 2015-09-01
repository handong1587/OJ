#include <stdio.h>

#define MAXN 1005
#define INF 0x3f3f3f3f
#define _min_(a,b) ((a)<(b)?(a):(b))

struct Point
{
    int x;
    int y;
};

struct Wormhole
{
    Point point_in;
    Point point_out;
    int cost;
};

Wormhole wormhole[10];
Point start, end;

int T;
int N,M;
int dist[MAXN][MAXN];
int cost[MAXN][MAXN];
bool visited[MAXN][MAXN];
int WormholeIn[MAXN][MAXN];
int WormholeOut[MAXN][MAXN];
int WormholeID;
int dx[2] = { 1, 0 };
int dy[2] = { 0, 1 };

int dp[MAXN][MAXN];

void init()
{
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            dist[i][j] = 0;
            dp[i][j] = INF;
        }
    }
    WormholeID=0;
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            cost[i][j] = INF;
            visited[i][j] = false;
            WormholeIn[i][j] = 0;
            if(j+1 < MAXN)
                dist[i][j+1] = 1;
            if(i+1 < MAXN)
                dist[i+1][j] = 1;
        }
    }
}

void solve()
{
    cost[0][0] = 0;
    int num = 0;
    while (true){
        int cx = -1;
        int cy = -1;
        for (int x = 0; x < N; x++){
            for (int y = 0; y < N; y++){
                if (!visited[x][y] && ((cx == -1 || cy == -1) || cost[x][y] < cost[cx][cy])){
                    cx = x;
                    cy = y;
                }
            }
        }
        if (cx == -1 || cy == -1){
            break;
        }
        visited[cx][cy] = true;

        //printf("%d: %d %d\n", num++, cx, cy);

        if(WormholeIn[cx][cy] > 0){
            int curID = WormholeIn[cx][cy];
            int out_x = wormhole[curID].point_out.x;
            int out_y = wormhole[curID].point_out.y;
            int wormhole_cost = wormhole[curID].cost;

            //printf("%d: current: cosy[%d][%d] = %d, cost[%d][%d] = %d, updated_cost[%d][%d] = %d\n",
            //    WormholeIn[cx][cy], cx, cy, cost[cx][cy],
            //    out_x, out_y, cost[out_x][out_y],
            //    out_x, out_y, cost[cx][cy] + wormhole_cost);

            cost[out_x][out_y] = _min_(cost[out_x][out_y], cost[cx][cy] + wormhole_cost);
        }
        else {
            for (int x = 0; x < 2; x++){
                int nx = cx + dx[x];
                int ny = cy + dy[x];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N){
//                     printf("cost[%d][%d] = %d, updated_cost[%d][%d] = %d\n",
//                         nx, ny, cost[nx][ny],
//                         nx, ny, cost[cx][cy] + dist[nx][ny]);
                     cost[nx][ny] = _min_(cost[nx][ny], cost[cx][cy] + dist[nx][ny]);
                }
            }
        }
    }
}

void dp_solve()
{
    dp[0][0] = 0;
    for (int x = 0; x < N; x++){
        for (int y = 0; y < N; y++){
            if (x==0&&y==0)
            {
                continue;
            }
            if (x>0 && y>0)
            {
                dp[x][y] = _min_(dp[x][y], _min_(dp[x - 1][y], dp[x][y - 1]) + 1);
            }
            else if (x>0){
                dp[x][y] = _min_(dp[x][y], dp[x - 1][y] + 1);
            }
            else if (y>0)
            {
                dp[x][y] = _min_(dp[x][y], dp[x][y-1] + 1);
            }

            if (WormholeIn[x][y] > 0){
                int curID = WormholeIn[x][y];
                int out_x = wormhole[curID].point_out.x;
                int out_y = wormhole[curID].point_out.y;
                int wormhole_cost = wormhole[curID].cost;
                dp[out_x][out_y] = _min_(dp[out_x][out_y], dp[x][y] + wormhole_cost);
            }
        }
    }
}

int main()
{
    freopen("Wormholes.txt","r",stdin);
    scanf("%d", &T);
    for(int t=1;t<=T;t++){
        init();
        scanf("%d %d",&N, &M);
        for(int i=1;i<=M;i++){
            int in_x, in_y, out_x, out_y, worm_cost;
            scanf("%d %d %d %d %d",&in_x, &in_y, &out_x, &out_y, &worm_cost);
            wormhole[i].point_in.x = in_x;
            wormhole[i].point_in.y = in_y;
            wormhole[i].point_out.x = out_x;
            wormhole[i].point_out.y = out_y;
            wormhole[i].cost = worm_cost;
            WormholeIn[wormhole[i].point_in.x][wormhole[i].point_in.y] = i;
            WormholeID++;
        }
        scanf("%d %d %d %d", &start.x, &start.y, &end.x, &end.y);

        solve();
        printf("#%d %d\n",t, cost[N-1][N-1]);
        //dp_solve();
        //printf("#%d %d\n",t, dp[N-1][N-1]);
    }
    return 0;
}
