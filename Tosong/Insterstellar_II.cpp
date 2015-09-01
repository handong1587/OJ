#include <stdio.h>

#define MAXN 1005
#define INF 0x3f3f3f3f
#define _min_(a,b) ((a)<(b)?(a):(b))
#define _abs_(a) ((a)<0?-(a):(a))

struct Gate
{
    int x;
    int y;
};

struct Wormhole
{
    Gate A;
    Gate B;
    int time;
};

Wormhole wormhole[10];
Gate start, end;

int T;
int N;
int dist[MAXN][MAXN];
int cost[MAXN][MAXN];
bool visited[MAXN][MAXN];
int GateA[MAXN][MAXN];
int GateB[MAXN][MAXN];
int WormholeID;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

bool used[20];

void init()
{
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            dist[i][j] = 0;
        }
    }
    WormholeID=0;
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            cost[i][j] = INF;
            visited[i][j] = false;
            GateA[i][j] = 0;
            GateB[i][j] = 0;
        }
    }
}

void preprocess()
{
    cost[start.x][start.y] = 0;
    cost[end.x][end.y] = _abs_(end.x - start.x) + _abs_(end.y - start.y);
    for (int i = 1; i <= N; i++)
    {
        int A_x = wormhole[i].A.x;
        int A_y = wormhole[i].A.y;
        int B_x = wormhole[i].B.x;
        int B_y = wormhole[i].B.y;
        cost[A_x][A_y] = _abs_(A_x - start.x) + _abs_(A_y - start.y);
        cost[B_x][B_y] = _abs_(B_x - start.x) + _abs_(B_y - start.y);

        GateA[A_x][A_y] = i;
        GateB[B_x][B_y] = i;
    }
}

Gate findOutGate(int wormhole_id, Gate inGate)
{
    if (wormhole[wormhole_id].A.x == inGate.x &&
        wormhole[wormhole_id].A.y == inGate.y)
    {
        return wormhole[wormhole_id].B;
    }
    else{
        return wormhole[wormhole_id].A;
    }
}

void solve()
{
    cost[start.x][start.y] = 0;
    int num = 0;
    while (true){
        int cx = -1;
        int cy = -1;
        for (int i = 1; i <= N;i++)
        {
            // find min time wormhole
            int A_x = wormhole[i].A.x;
            int A_y = wormhole[i].A.y;
            int B_x = wormhole[i].B.x;
            int B_y = wormhole[i].B.y;
            if (!visited[A_x][A_y])
            {
                if ((cx == -1 || cy == -1) || cost[A_x][A_y] < cost[cx][cy])
                {
                    cx = A_x;
                    cy = A_y;
                }
            }
            if (!visited[B_x][B_y])
            {
                if ((cx == -1 || cy == -1) || cost[B_x][B_y] < cost[cx][cy])
                {
                    cx = B_x;
                    cy = B_y;
                }
            }
        }
        if (cx == -1 || cy == -1){
            break;
        }
        visited[cx][cy] = true;

        for (int i = 1; i <= N; i++)
        {
            int curWormholeID = GateA[cx][cy];
            Gate inGate;
            inGate.x = cx;
            inGate.y = cy;
            Gate outGate = findOutGate(curWormholeID, inGate);
            int out_x = outGate.x;
            int out_y = outGate.y;
            int wormhole_cost = wormhole[curWormholeID].time;

            cost[out_x][out_y] = _min_(cost[out_x][out_y], cost[cx][cy]+wormhole_cost);
            // update to dst
            int new_cost = _abs_(out_x - end.x) + _abs_(out_y - end.y);
            cost[end.x][end.y] = _min_(cost[end.x][end.y], cost[out_x][out_y] + new_cost);
            // update to other wormhole
            for (int i = 1; i <= N; i++)
            {
                Gate A = wormhole[i].A;
                Gate B = wormhole[i].B;
                int cost_cx_A = _abs_(cx - A.x) + _abs_(cy - A.y);
                cost[A.x][A.y] = _min_(cost[A.x][A.y], cost[cx][cy] + cost_cx_A);
                new_cost = _abs_(A.x - end.x) + _abs_(A.y - end.y);
                cost[end.x][end.y] = _min_(cost[end.x][end.y], cost[A.x][A.y] + new_cost);

                int cost_cx_B = _abs_(cx - B.x) + _abs_(cy - B.y);
                cost[B.x][B.y] = _min_(cost[B.x][B.y], cost[cx][cy] + cost_cx_B);
                new_cost = _abs_(B.x - end.x) + _abs_(B.y - end.y);
                cost[end.x][end.y] = _min_(cost[end.x][end.y], cost[B.x][B.y] + new_cost);
            }
        }
    }
}

int main()
{
    freopen("Insterstellar_II.txt","r",stdin);
    scanf("%d", &T);
    for(int t=1;t<=T;t++){
        init();
        scanf("%d",&N);
        scanf("%d %d %d %d", &start.x, &start.y, &end.x, &end.y);
        for(int i=1;i<=N;i++){
            int A_x, A_y, B_x, B_y, worm_time;
            scanf("%d %d %d %d %d",&A_x, &A_y, &B_x, &B_y, &worm_time);
            wormhole[i].A.x = A_x;
            wormhole[i].A.y = A_y;
            wormhole[i].B.x = B_x;
            wormhole[i].B.y = B_y;
            wormhole[i].time = worm_time;
            GateA[A_x][A_y] = i;
            GateA[B_x][B_y] = i;
            WormholeID++;
        }
        preprocess();
        solve();
        printf("#%d %d\n",t, cost[end.x][end.y]);
    }
    return 0;
}
