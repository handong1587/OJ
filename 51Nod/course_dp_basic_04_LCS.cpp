#include <stdio.h>
#include <string.h>

#define _DEBUG_ 0
#define _max_(a,b) ((a)>(b)?(a):(b))

typedef enum{TGT,LFT,TOP} FromType;
char ftype[3][10]={"TGT","LFT","TOP"};

struct LocInfo
{
    FromType ft;
};

char s1[1005];
char s2[1005];
int dp[1005][1005];
LocInfo loc[1005][1005];
int n1,n2,maxn;
char maxs[1005];
int finalx,finaly;

void solve()
{
    maxn=0;
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            if(i==0||j==0){
                dp[i][j]=0;

                //loc[i][j].prevx=0;
                //loc[i][j].prevy=0;

            }
            else if(s1[i-1]==s2[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
                if(dp[i][j]>maxn){
                    finalx=i;
                    finaly=j;
#if _DEBUG_
                    printf("finalx=%d,finaly=%d\n",finalx,finaly);
#endif
                }
                maxn=_max_(maxn,dp[i][j]);

                loc[i][j].ft=TGT;
            }
            else{
                dp[i][j]=_max_(dp[i-1][j],dp[i][j-1]);
                maxn=_max_(maxn,dp[i][j]);

                if(dp[i-1][j]>dp[i][j-1]){
                    loc[i][j].ft=LFT;
                }
                else {
                    loc[i][j].ft=TOP;
                }
            }
        }
    }

#if _DEBUG_
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            printf("(%s,%s)%s",ftype[loc[i][j].ft],loc[i][j].ft==TGT?"Y":"N",j==n2?"\n":" ");
        }
    }
#endif

    int curx=finalx,cury=finaly;
#if _DEBUG_
    printf("finalx=%d,finaly=%d\n",finalx,finaly);
#endif
    int tgtn=0;
    char revs[1005];
    while(curx>=1&&cury>=1){
        if(loc[curx][cury].ft==TGT){
            revs[tgtn++]=s1[curx-1];
        }
#if _DEBUG_
        if(loc[curx][cury].ft==TGT){
            printf("curx=%d,cury=%d,%c\n",curx,cury,s1[curx-1]);
        }
        else{
            printf("curx=%d,cury=%d\n",curx,cury);
        }
#endif
        if(loc[curx][cury].ft==TGT){
            curx--;
            cury--;
        }
        else if(loc[curx][cury].ft==LFT){
            curx--;
        }
        else{
            cury--;
        }
    }
    for(int i=0;i<tgtn;i++){
        maxs[i]=revs[tgtn-1-i];
    }
    maxs[maxn]='\0';
}

int main()
{
    freopen("course_dp_basic_04_LCS.txt","r",stdin);;
    scanf("%s",s1);
    scanf("%s",s2);

    n1=strlen(s1);
    n2=strlen(s2);

#if _DEBUG_
    //printf("n1=%d\n",n1);
    //printf("n2=%d\n",n2);
    printf("%s\n",s1);
    printf("%s\n",s2);
#endif
    solve();
    //printf("%d\n",maxn);
    printf("%s\n",maxs);

#if _DEBUG_
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            printf("%d%s",dp[i][j],j==n2?"\n":" ");
        }
    }
#endif

    return 0;
}
