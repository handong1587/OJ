#include <stdio.h>

#define _MOD_ (1000000007)
int N;
int a[100005];
int dp[100005];
int have[100005];

void solve()
{
    dp[0]=1;
    for(int i=1;i<=N;i++){
        dp[i]=dp[i-1]*2;

        printf("a[%2d]=%3d, dp[%2d]=%6d\n",i,a[i],i,dp[i]);

        if(have[a[i]]>0){
            if(dp[i] < dp[have[a[i]]-1]){
                dp[i] += _MOD_;
            }
            dp[i]-=dp[have[a[i]]-1];

            printf("\nlast a[%d] is at %d\n\n",i,have[a[i]]);
            printf("a[%2d]=%3d, dp[%2d]=%6d\n",i,a[i],i,dp[i]);
        }
        dp[i] %= _MOD_;
        have[a[i]]=i;
    }
}

int main()
{
    freopen("15_number_of_sub_sequences_case3.txt","r",stdin);
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%d",&a[i]);
    }
    solve();
    printf("%d\n",dp[N]-1);
    return 0;
}
