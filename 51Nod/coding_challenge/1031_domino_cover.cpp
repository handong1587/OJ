#include <stdio.h>

#define MAXN 1005
#define M 1000000007
int N;
long long dp[MAXN];

int naive_solve(int start, int n)
{
    if(start > n){
        return 0;
    }
    else if(start == n){
        return 1;
    }
    int res = 0;
    res += naive_solve(start + 1, n) + naive_solve(start + 2, n);
    return  res % M;
}

int solve(int n)
{
    dp[n] = 1;
    dp[n - 1] = 2;
    for(int i = n-2; i>=1; i--){
        dp[i] = (dp[i+1] + dp[i+2]) % M;
    }
    return dp[1];
}

int main()
{
    freopen("1031_domino_cover.txt","r",stdin);
    scanf("%d",&N);
    int res = solve(N);
    printf("%d\n", res);
    return 0;
}
