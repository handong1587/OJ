#include <stdio.h>
#include <string.h>

#define _min_(a,b) ((a)<(b)?(a):(b))

char s1[1005],s2[1005];
int n1,n2;
int dp[1005][1005];

int same(int i, int j)
{
    if(s1[i]==s2[j])
        return 0;
    else
        return 1;
}

void solve()
{
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            if(i==0&&j==0){
                dp[i][j]=0;
            }
            else if(i==0){
                dp[i][j]=j;
            }
            else if(j==0){
                dp[i][j]=i;
            }
            else{
                dp[i][j]=_min_(dp[i-1][j-1]+same(i-1,j-1),_min_(dp[i-1][j]+1,dp[i][j-1]+1));
            }
        }
    }
}

int main()
{
    freopen("course_dp_basic_03_EditDistance.txt","r",stdin);
    scanf("%s",s1);
    scanf("%s",s2);
    n1=strlen(s1);
    n2=strlen(s2);

    solve();

    printf("%d\n",dp[n1][n2]);

    return 0;
}
