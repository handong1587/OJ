#include <stdio.h>

//#define INF 0x3f3f3f3f3f3f3f3f
#define D_INF (1.79769e+308)
#define MAXN 1005
#define _min_(a,b) ((a)<(b)?(a):(b))

int T;
int N;
struct Coord
{
    int x;
    int y;
};
Coord cd[MAXN];
double E;
double cost[MAXN][MAXN];
double mincost[MAXN];
bool used[MAXN];

long long dist(Coord c1, Coord c2)
{
    return (long long)(c1.x - c2.x)*(c1.x - c2.x) + (long long)(c1.y - c2.y)*(c1.y - c2.y);
}

void init()
{
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cost[i][j] = D_INF;
        }
        mincost[i] = D_INF;
        used[i] = false;
    }
}

void calcCost()
{
    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            long long len2 = dist(cd[i], cd[j]);
            cost[i][j] = E * len2;
            cost[j][i] = cost[i][j];
        }
    }
}

long long prim()
{
    double res = 0.0;
    mincost[0] = 0;

    while (true){
        int v = -1;
        for (int u = 0; u < N; u++){
            if (!used[u]){
                if (v == -1)
                    v = u;
                else if (mincost[u] < mincost[v])
                    v = u;
            }
        }
        if (v == -1){
            break;
        }
        used[v] = true;
        res += mincost[v];

        for (int u = 0; u < N; u++){
            mincost[u] = _min_(mincost[u], cost[v][u]);
        }
    }

    return (long long)(res + 0.5);
}

int main()
{
    freopen("Tosong\\Hanaro.txt","r",stdin);
    scanf("%d", &T);
    for (int t = 1; t <= T; t++){
        scanf("%d", &N);
        init();
        for (int i = 0; i < N; i++){
            scanf("%d", &cd[i].x);
        }
        for (int i = 0; i < N; i++){
            scanf("%d", &cd[i].y);
        }
        scanf("%lf", &E);
        calcCost();
        long long res = prim();
        printf("#%d %lld\n", t, res);
    }
    return 0;
}
