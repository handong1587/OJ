#include <stdio.h>
#include <string.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

typedef enum{TGT,LFT,TOP} FromType;
char ftype[3][10]={"TGT","LFT","TOP"};

struct LocInfo
{
//    bool isTgt;
//    int prevx;
//    int prevy;
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
                //printf("s1[%d]==s[%d]==%c\n",i,j,s1[i-1]);
                dp[i][j]=dp[i-1][j-1]+1;
                maxn=_max_(maxn,dp[i][j]);

                //loc[i][j].isTgt=true;
                //loc[i][j].prevx=i-1;
                //loc[i][j].prevy=j-1;
                loc[i][j].ft=TGT;

                finalx=i;
                finaly=j;

            }
            else{
                dp[i][j]=_max_(dp[i-1][j],dp[i][j-1]);
                maxn=_max_(maxn,dp[i][j]);

                //loc[i][j].isTgt=false;
                if(dp[i-1][j]>dp[i][j-1]){
                    //loc[i][j].prevx=i-1;
                    //loc[i][j].prevy=j;
                    loc[i][j].ft=LFT;
                }
                else {
                    //loc[i][j].prevx=i-1;
                    //loc[i][j].prevy=j;
                    loc[i][j].ft=TOP;
                }
            }
        }
    }

    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            printf("(%s,%s)%s",ftype[loc[i][j].ft],loc[i][j].ft==TGT?"Y":"N",j==n2?"\n":" ");
        }
    }

    int curx=finalx,cury=finaly;
    //printf("finalx=%d,finaly=%d\n",finalx,finaly);
    int tgtn=0;
    char revs[1005];
    while(curx>=1&&cury>=1){
        if(loc[curx][cury].ft==TGT){
            revs[tgtn++]=s1[curx-1];
            printf("curx=%d,cury=%d,%c\n",curx,cury,s1[curx-1]);
        }
        //int tmpx=loc[curx][cury].prevx;
        //int tmpy=loc[curx][cury].prevy;
        //curx=tmpx;
        //cury=tmpy;
        if(loc[curx][cury].ft==TGT){
            curx--;
            cury--;
        }
        else if(loc[curx][cury].ft==LFT){
            curx--;
            //cury--;
        }
        else{
            cury--;
        }
        printf("curx=%d,cury=%d\n",curx,cury);
    }
    //printf("tgtn=%d\n",tgtn);
    //printf("revs=%s\n",revs);
    for(int i=0;i<tgtn;i++){
        maxs[i]=revs[tgtn-1-i];
    }
}

int main()
{
    freopen("course_dp_basic_04_LCS.txt","r",stdin);;
    scanf("%s",s1);
    scanf("%s",s2);

    n1=strlen(s1);
    n2=strlen(s2);

    //printf("n1=%d\n",n1);
    //printf("n2=%d\n",n2);
    printf("%s\n",s1);
    printf("%s\n",s2);

    solve();
    //printf("%d\n",maxn);
    printf("%s\n",maxs);

    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            printf("%d%s",dp[i][j],j==n2?"\n":" ");
        }
    }

    return 0;
}
