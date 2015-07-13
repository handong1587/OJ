#include <stdio.h>
int N;
int mat[505][505];
int dp[505][505];

#define _max_(a,b) ((a)>(b)?(a):(b))

void solve()
{
    dp[0][0]=mat[0][0];
    for(int i=1;i<N;i++){
        dp[0][i]=dp[0][i-1]+mat[0][i];
        dp[i][0]=dp[i-1][0]+mat[i][0];
    }
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
            dp[i][j]=_max_(dp[i-1][j],dp[i][j-1])+mat[i][j];
        }
    }
}

int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&mat[i][j]);
        }
    }
    solve();
    printf("%d\n",dp[N-1][N-1]);
    return 0;
}
