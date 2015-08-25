#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

// state compression DP

#define INF 0x3f3f3f3f
#define DINF 100000.0
#define min(a,b) ((a)<(b)?(a):(b))
int n, m, p, a, b;
int t[35];
int d[35][35];
double dp[1 << 10][35];

void solve()
{
    for (int i = 0; i < (1 << n); i++)
    {
        fill(dp[i], dp[i] + m, DINF);
    }
    dp[(1 << n) - 1][a - 1] = 0;
    double res = DINF;
    for (int S = (1 << n) - 1; S >= 0; S--)
    {
        res = min(res, dp[S][b - 1]);
        for (int v = 0; v < m; v++)
        {
            for (int i = 0; i < n; i++)
            {
                if ((S >> i) & 1)
                {
                    for (int u = 0; u < m; u++)
                    {
                        if (d[v][u] >= 0)
                        {
                            dp[S & ~(1 << i)][u] = min(dp[S & ~(1 << i)][u], dp[S][v] + (double)d[v][u] / t[i]);
                        }
                    }
                }
            }
        }
    }
    if (res == DINF)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%.3f\n", res);
    }
}

int main()
{
    freopen("2686_Traveling_by_Stagecoach.txt", "r", stdin);
    while (scanf("%d %d %d %d %d", &n, &m, &p, &a, &b)
        && (n || m || p || a || b))
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &t[i]);
        }
//         for (int i = 0; i < m; i++)
//         {
//             for (int j = 0; j < m; j++)
//             {
//                 d[i][j] = -1;
//             }
//         }
        memset(d, -1, sizeof(d));
        for (int i = 0; i < p; i++)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            d[x - 1][y - 1] = z;
            d[y - 1][x - 1] = z;
        }
        solve();
    }

    return 0;
}
