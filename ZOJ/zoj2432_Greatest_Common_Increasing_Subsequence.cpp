#include <stdio.h>
#include <string.h>

#define MAXN 505

int T,M1,M2,A1[MAXN],A2[MAXN];
int f[MAXN][MAXN], dp[MAXN];
int res[MAXN];

int gcis(int a[], int la, int b[], int lb, int ans[])
{ // a[1…la], b[1…lb]
    int i, j, k, mx;
    memset(f, 0, sizeof(f));
    memset(dp, 0, sizeof(dp));
    for(i = 1; i <= la; i++) {
        memcpy(f[i], f[i-1], sizeof(f[0]));
        for(k = 0, j = 1; j <= lb; j++) {
            if(b[j-1] < a[i-1] && dp[j] > dp[k])
                k = j;
            if(b[j-1] == a[i-1] && dp[k] + 1 > dp[j]) {
                dp[j] = dp[k] + 1,
                f[i][j] = i * (lb + 1) + k;
            }
        }
    }
    for(mx = 0, i = 1; i <= lb; i++)
        if(dp[i] > dp[mx]) mx = i;
    for(i=la*lb+la+mx, j=dp[mx]; j; i=f[i/(lb+1)][i%(lb+1)],j--)
        ans[j-1] = b[i % (lb + 1) - 1];
    return dp[mx];
}

int main()
{
  freopen("zoj2432_Greatest_Common_Increasing_Subsequence.txt","r",stdin);

  scanf("%d\n",&T);
  for(int t=1;t<=T;t++){
    scanf("%d",&M1);
    for(int i=0;i<M1;i++){
      scanf("%d",&A1[i]);
    }
    scanf("%d",&M2);
    for(int i=0;i<M2;i++){
      scanf("%d",&A2[i]);
    }

    int len = gcis(A1, M1, A2, M2, res);

    printf("%d\n",len);
    for(int i=0;i<len;i++){
         printf("%d%s",res[i],i==len-1?"\n":" ");
    }
  }

  return 0;
}
