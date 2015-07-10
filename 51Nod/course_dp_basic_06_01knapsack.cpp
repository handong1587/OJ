#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int N,W;
int wi[105],pi[105];
int dp[105][10005];

void solve()
{
    for(int j=0;j<=W;j++){
        dp[0][j]=0;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<=W;j++){
            if(j<wi[i]){
                dp[i+1][j]=dp[i][j];
            }
            else{
                dp[i+1][j]=_max_(dp[i][j],dp[i][j-wi[i]]+pi[i]);
            }
        }
    }
}

int main()
{
    freopen("course_dp_basic_06_01knapsack.txt","r",stdin);

    scanf("%d %d",&N,&W);
    for(int i=0;i<N;i++){
        scanf("%d %d",&wi[i],&pi[i]);
    }

    solve();

    printf("%d\n",dp[N][W]);

    return 0;
}
