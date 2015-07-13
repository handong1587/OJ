#include <stdio.h>

#define _abs_(a) ((a)>0?(a):-(a))

int N;
int a[105];
bool dp[105][10005];
int sum;
int mindiff;

void solve()
{
    sum=0;
    for(int i=0;i<N;i++){
        sum+=a[i];
    }
    dp[0][0]=true;
    for(int j=1;j<=sum;j++){
        dp[0][j]=false;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<=sum;j++){
            dp[i+1][j]=dp[i][_abs_(j-a[i])] || dp[i][j+a[i]];
        }
    }

    for(int j=0;j<=sum;j++){
        if(dp[N][j]==true){
            mindiff=j;
            break;
        }
    }
}

int main()
{
    freopen("course_dp_basic_07_PositiveIntegersGrouping.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }

    solve();

    printf("%d\n",mindiff);

    return 0;
}
