#include <stdio.h>
#include <stdlib.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
int T;
char s1[105], s2[105];
int g1[105], g2[105];
int d1, d2;
int dp[105][105];
// '-':0, A:1, C:2, G:3, T:4
int w[5][5] = { { 0, -3, -4, -2, -1 },
                { -3, 5, -1, -2, -1 },
                { -4, -1, 5, -3, -2 },
                { -2, -2, -3, 5, -2 },
                { -1, -1, -2, -2, 5} };

int change(char c)
{
    switch (c)
    {
    case 'A':
        return 1;
    case 'C':
        return 2;
    case 'G':
        return 3;
    case 'T':
        return 4;
    }
    return 0;
}
int main()
{
    freopen("1080_Human_Gene_Functions.txt", "r", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %s", &d1, s1);
        scanf("%d %s", &d2, s2);
        dp[0][0] = 0;
        for (int i = 1; i <= d1; i++)
        {
            g1[i] = change(s1[i-1]);
            dp[i][0] = dp[i - 1][0] + w[g1[i]][0];
        }
        for (int i = 1; i <= d2; i++)
        {
            g2[i] = change(s2[i-1]);
            dp[0][i] = dp[0][i - 1] + w[0][g2[i]];
        }
        for (int i = 1; i <= d1; i++)
        {
            for (int j = 1; j <= d2; j++)
            {
                dp[i][j] = _max_(_max_(dp[i - 1][j - 1] + w[g1[i]][g2[j]], dp[i][j - 1] + w[0][g2[j]]),
                    dp[i - 1][j] + w[g1[i]][0]);
            }
        }
        printf("%d\n", dp[d1][d2]);
    }
    return 0;
}
