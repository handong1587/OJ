#include <stdio.h>
#include <string.h>

#define MAX_CENTS 7490
#define NUM_COIN_TYPE 5

int cents;
int coin_type[NUM_COIN_TYPE] = { 1,5,10,25,50 };
int dp[MAX_CENTS];

void make_table()
{
    dp[0] = 1;
    for (int i = 0; i < NUM_COIN_TYPE; i++) {
        for (int j = 0; j + coin_type[i] <= MAX_CENTS; j++) {
            dp[j + coin_type[i]] += dp[j];
        }
    }
}

int main()
{
    freopen("UVa\\674_Coin_Change.txt", "r", stdin);

    make_table();
    while (scanf("%d", &cents) != EOF) {
        int res = dp[cents];
        printf("%d\n", res);
    }

    return 0;
}