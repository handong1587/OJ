#include <stdio.h>
#include <string.h>

using namespace std;

#define MAXN 30

int dp[MAXN + 5];
int sum_on_dp[MAXN + 5];

void init()
{
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    dp[2] = 3;

    sum_on_dp[0] = dp[0];
    sum_on_dp[2] = sum_on_dp[0] + dp[2];
    for (int i = 4; i <= 30; i++) {
        if (i % 2 == 1) {
            dp[i] = 0;
        }
        else {
            dp[i] = dp[i - 2] * 3 + sum_on_dp[i - 4] * 2;
            sum_on_dp[i] = sum_on_dp[i - 2] + dp[i];
        }
    }
}

void solve(int n)
{
    printf("%d\n", dp[n]);
}

int main()
{
    freopen("POJ\\2663_Tri_Tiling.txt", "r", stdin);
    int n;
	init();
    while (scanf("%d", &n) != EOF) {
        if (n == -1) {
            break;
        }
        solve(n);
    }
    return 0;
}