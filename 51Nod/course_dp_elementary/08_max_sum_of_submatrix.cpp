#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int M,N;
long long mat[505][505];
long long dp[505];
long long maxsum;

void solve()
{
    maxsum=mat[0][0];
    for(int i=0;i<M;i++){
        for(int j=i;j<M;j++){
            for(int k=0;k<N;k++){
                dp[k]=0;
            }
            for(int k=0;k<N;k++){
                dp[k]=(j==i)?mat[k][i]:(dp[k]+mat[k][j]);
                printf("i=%d, j=%d, dp[%d]=%lld\n",i,j,k,dp[k]);
            }
            long long tmpmax = dp[0];
            long long endmax = dp[0];
            for(int k=1;k<N;k++){
                endmax=_max_(endmax,0)+dp[k];
                tmpmax=_max_(tmpmax,endmax);
            }
            //printf("i=%d, j=%d, tmpmax=%lld\n",i,j,tmpmax);
            maxsum=_max_(maxsum,tmpmax);
        }
    }
}

int main()
{
    freopen("08_max_sum_of_submatrix.txt","r",stdin);
    scanf("%d %d",&M,&N);
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%lld",&mat[i][j]);
        }
    }
    solve();
    printf("%lld\n",_max_(0,maxsum));

    return 0;
}
