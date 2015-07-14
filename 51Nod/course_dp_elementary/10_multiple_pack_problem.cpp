#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
#define _min_(a,b) ((a)<(b)?(a):(b))

int N,W;
int wi[105],pi[105],ci[105];
long long dp[105][50005];

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
                for(int k=0;k<=_min_(j/wi[i],ci[i]);k++){
                    dp[i+1][j]=_max_(dp[i+1][j],dp[i][j-k*wi[i]]+k*pi[i]);
                    //printf("k=%d: dp[%d][%d]=%lld, dp[%d][%d]=%lld, wi[%d]=%d, pi[%d]=%d\n",k,i,j,dp[i][j],i+1,j,dp[i+1][j],k,wi[k],k,pi[k]);
                }
            }
        }
    }
}

int main()
{
    freopen("10_multiple_pack_problem.txt","r",stdin);
    scanf("%d %d",&N,&W);
    for(int i=0;i<N;i++){
        scanf("%d %d %d",&wi[i],&pi[i],&ci[i]);
    }
    solve();
    printf("%lld\n",dp[N][W]);

    //for(int i=0;i<=N;i++){
    //    for(int j=0;j<=W;j++){
    //        printf("dp[%d][%d]=%lld%s",i,j,dp[i][j],j==W?"\n":" ");
    //    }
    //}

    return 0;
}
