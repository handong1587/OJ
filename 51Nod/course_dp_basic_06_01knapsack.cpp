#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int N,W;
int wi[105],pi[105];
int dp[105][10005];

void solve()
{
    for(int i=0;i<N;i++){
        dp[i][j]=_max_(dp[i-1][j],dp[i-1][j-wi[i]]+pi[i]);
    }
}

int main()
{
    freopen("course_dp_basic_06_01knapsack.txt","r",stdin);

    scanf("%d %d",&N,&W);
    for(int i=0;i<N;i++){
        scanf("%d",&wi[i]);
    }

    return 0;
}
