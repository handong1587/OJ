#include <stdio.h>

int N;
long long s[50005];
long long dp[50005];
long long c[50005];
int maxn;

void update(int start,int end,int tgtval)
{
    for(int i=0;i<end;i++){
        if(c[i]>tgtval){
            c[i]=tgtval;
            return;
        }
    }
}

void solve()
{
    c[0]=s[0];
    maxn=1;
    for(int i=1;i<N;i++){
        if(s[i]>c[maxn-1]){
            c[maxn++]=s[i];
        }
        else if(s[i]<c[maxn-1]){
            update(0,maxn,s[i]);
        }
    }

}

int main()
{
    freopen("course_dp_basic_05_LIS.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%lld",&s[i]);
    }

    solve();
    printf("%d\n",maxn);

    return 0;
}
