#include <stdio.h>

int N;
int s[50005];
int c[50005];
int maxn;

void update(int start,int end,int tgtval)
{
    for(int i=0;i<end;i++){
        if(c[i]>tgtval){
            printf("update c[%d] (%d) = (%d)\n",i,c[i],tgtval);
            c[i]=tgtval;
            return;
        }
    }
}

void update_binarysearch(int start,int end,int tgtval)
{
    int mid;
    while(end-start>1){
        mid=(start+end)/2;
        if(c[mid]>tgtval){
            end=mid;
        } else if(c[mid]<tgtval) {
            start=mid;
        } else{
             return;
        }
    }
    if(c[start]>tgtval){
        printf("update c[%d] (%d) = (%d)\n",start,c[start],tgtval);
        c[start]=tgtval;
    }
    else if(c[end]>tgtval){
        printf("update c[%d] (%d) = (%d)\n",end,c[end],tgtval);
        c[end]=tgtval;
    }
}

void solve()
{
    c[0]=s[0];
    printf("c[%d]=%d\n",0,s[0]);
    maxn=1;
    for(int i=1;i<N;i++){
        if(s[i]>c[maxn-1]){
            printf("c[%d]=%d\n",maxn,s[i]);
            c[maxn++]=s[i];
        }
        else if(s[i]<c[maxn-1]){
            //update(0,maxn,s[i]);
            update_binarysearch(0,maxn,s[i]);
        }
    }

}

int main()
{
    freopen("12_LIS_case3.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&s[i]);
    }

    solve();
    printf("%d\n",maxn);

    return 0;
}
