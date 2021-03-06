#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _TEST_TIME_ 1
#include <sys/time.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
#define _min_(a,b) ((a)<(b)?(a):(b))

int N,W;
int wi[105],pi[105],ci[105];
long long dp[105][50005];
int ngroup[256];
int groups[256][9];

int N2;
long long **dp2;
int wi2[805],pi2[805];
#define _MEM_OPT_ 1
long long dp3[2][50005];

void slow_solve()
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
                }
            }
        }
    }
}

int grouping(int n, int g[])
{
    int ng = 0;
    if (n == 0){
        return 0;
    }
    g[0]=0;
    int k = 1;
    while(n > 0) {
        ng++;
        if (n > k) {
            g[ng] = k;
        } else {
            g[ng] = n;
        }
        n -= k;
        k *= 2;
    }
    return ng;
}

void preprocess()
{
    for (int i=0;i<205;i++) {
        ngroup[i] = grouping(i, groups[i]);
    }
    int cnt=0;
    for(int i=0;i<N;i++){
        int ng=ngroup[ci[i]];
        for(int k=1;k<=ng;k++){
            wi2[cnt+k-1] = groups[ci[i]][k] * wi[i];
            pi2[cnt+k-1] = groups[ci[i]][k] * pi[i];
        }
        cnt+=ng;
    }
    N2 = cnt;
#if !_MEM_OPT_
    dp2 = (long long**)malloc(sizeof(long long *) * (N2+5));
    for (int i=0;i<(N2+5);i++) {
        dp2[i] = (long long *)malloc(sizeof(long long) * 50005);
        memset(dp2[i],0,sizeof(long long) * 50005);
    }
#endif
}

void solve_by_01pack()
{
    for(int j=0;j<=W;j++){
        dp2[0][j]=0;
    }
    for(int i=0;i<N2;i++){
        for(int j=0;j<=W;j++){
            if(j<wi2[i]){
                dp2[i+1][j]=dp2[i][j];
            }
            else{
                dp2[i+1][j]=_max_(dp2[i][j],dp2[i][j-wi2[i]]+pi2[i]);
            }
        }
    }
}

void solve_by_01pack_memoryoptimized()
{
    for(int j=0;j<=W;j++){
        dp3[0][j]=0;
    }
    for(int i=0;i<N2;i++){
        for(int j=0;j<=W;j++){
            if(j<wi2[i]){
                dp3[1][j]=dp3[0][j];
            }
            else{
                dp3[1][j]=_max_(dp3[0][j],dp3[0][j-wi2[i]]+pi2[i]);
            }
        }
        memcpy(dp3[0], dp3[1], sizeof(long long)*50005);
    }
}

int main()
{
    freopen("10_multiple_pack_problem_case12.txt","r",stdin);
    scanf("%d %d",&N,&W);
    for(int i=0;i<N;i++){
        scanf("%d %d %d",&wi[i],&pi[i],&ci[i]);
    }

#if _TEST_TIME_
    struct timeval start,end;
    gettimeofday(&start,NULL);
#endif

#define _FAST_SOLVE_ 1
#if _FAST_SOLVE_
    preprocess();
#if !_MEM_OPT_
    solve_by_01pack();
    printf("%lld\n",dp2[N2][W]);
#else
    solve_by_01pack_memoryoptimized();
    printf("%lld\n",dp3[1][W]);
#endif
#else
    slow_solve();
    printf("%lld\n",dp[N][W]);
#endif

#if _TEST_TIME_
    gettimeofday(&end,NULL);
    long long timeuse = 1000000 * ( end.tv_sec - start.tv_sec  ) + end.tv_usec -start.tv_usec;
    printf("time: %lld us\n",timeuse);

    printf("N2=%d\n",N2);
#endif


    //for(int i=0;i<=N2;i++){
    //    for(int j=0;j<=W;j++){
    //        printf("%lld%s",dp2[i][j], j==W?"\n":" ");
    //    }
    //}

    return 0;
}
