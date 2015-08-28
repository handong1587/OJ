#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int N;
int a[505][505];
int dp[505][505];

void solve()
{
    for(int i=0; i<N; i++){
        dp[N-1][i] = a[N-1][i];
    }
    for(int i=N-2; i>=0; i--){
        for(int j=0; j<=i; j++){
            dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + a[i][j];
        }
    }
}

int main()
{
    freopen("1002_number_tower.txt", "r", stdin);
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        for(int j=0; j<=i; j++){
            scanf("%d", &a[i][j]);
        }
    }
    memset(dp, 0, sizeof(dp));
    solve();
    printf("%d\n", dp[0][0]);
    return 0;
}
