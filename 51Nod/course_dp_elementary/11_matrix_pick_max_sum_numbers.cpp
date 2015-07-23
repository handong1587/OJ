#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int M,N,S;
int A[205][205];
long long dp[2][205][205];
long long maxv;

void solve()
{
    dp[0][0][0]=A[0][0];
    for(int step=1;step<=S;step++){
        for(int x1=0;x1<M;x1++){
            for(int x2=0;x2<M;x2++){
                int y1=step-x1;
                int y2=step-x2;
                if(y1<0 || y2<0 || y1>N || y2>N){
                    continue;
                }
                if(x1>0 && x2>0){
                    maxv = _max_(dp[0][x1-1][x2-1],
                            _max_(dp[0][x1-1][x2], dp[0][x1][x2-1]));
                    maxv = _max_(maxv, dp[0][x1][x2]);
                } else if(x1>0){
                    maxv = _max_(dp[0][x1][x2], dp[0][x1-1][x2]);
                } else if(x2>0){
                    maxv = _max_(dp[0][x1][x2], dp[0][x1][x2-1]);
                } else{
                    maxv = dp[0][x1][x2];
                }

                if(x1==x2){
                    dp[1][x1][x2] = maxv + A[y1][x1]; // CAUTION: NOT A[x1][y1]!
                } else {
                    dp[1][x1][x2] = maxv + A[y1][x1] + A[y2][x2];
                }
            }
        }
        for(int x1=0;x1<M;x1++){
            for(int x2=0;x2<M;x2++){
                dp[0][x1][x2]=dp[1][x1][x2];
            }
        }

    }
}

int main()
{
    freopen("11_matrix_pick_max_sum_numbers_case20.txt","r",stdin);
    scanf("%d %d",&M,&N);
    S=N+M-2;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&A[i][j]);
        }
    }
    solve();

    printf("%lld\n",dp[1][M-1][M-1]);

    return 0;
}
