#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int T;
int N;
char S1[505];
char S2[505];
int dp[505][505];
int maxn;

void solve()
{
    maxn=0;
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            if(i==0||j==0){
                dp[i][j]=0;

            }
            else if(S1[i-1]==S2[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
                maxn=_max_(maxn,dp[i][j]);
            }
            else{
                dp[i][j]=_max_(dp[i-1][j],dp[i][j-1]);
                maxn=_max_(maxn,dp[i][j]);
            }
        }
    }
}

int main()
{
    freopen("Image_Similarity_Check.txt","r",stdin);
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        scanf("%d",&N);
        scanf("%s",S1);
        scanf("%s",S2);
        solve();
        printf("#%d %.2f\n",t,(float)maxn/N*100);
    }
    return 0;
}
