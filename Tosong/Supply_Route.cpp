#include <stdio.h>

#define MAXN 105
#define _min_(a,b) ((a)<(b)?(a):(b))

int T;
int N;
int mat[MAXN][MAXN];
int dp[MAXN][MAXN];

void init()
{
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            dp[i][j]=0;
        }
    }
}

void solve()
{
    dp[0][0]=mat[0][0];
    for(int i=1;i<N;i++){
        dp[0][i]=dp[0][i-1]+mat[0][i];
        dp[i][0]=dp[i-1][0]+mat[i][0];
    }
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
            dp[i][j]=_min_(dp[i-1][j],dp[i][j-1])+mat[i][j];
        }
    }
}

int main()
{
    freopen("Supply_Route.txt","r",stdin);
    scanf("%d", &T);
    for(int t=1;t<=T;t++){
        init();
        scanf("%d",&N);
        char s[MAXN];
        for(int i=0;i<N;i++){
            scanf("%s",s);
            for(int j=0;j<N;j++){
                mat[i][j]=(int)(s[j]-'0');
            }
        }
        solve();
        printf("#%d %d\n",t, dp[N-1][N-1]);
    }
    return 0;
}
