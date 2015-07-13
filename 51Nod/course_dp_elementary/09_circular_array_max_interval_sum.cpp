#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
#define _min_(a,b) ((a)<(b)?(a):(b))

int N;
long long a[50005],b[50005];
long long sum,maxsum,minsum,res;

void solve()
{
    //int mid=N/2;
    int tmpmaxsum=a[0];
    int tmpendmax=a[0];
    for(int i=1;i<N;i++){
        tmpendmax=_max_(tmpendmax,0)+a[i];
        tmpmaxsum=_max_(tmpmaxsum,tmpendmax);
    }

    int tmpminsum=b[0];
    int tmpendmin=b[0];
    for(int i=1;i<N;i++){
        tmpendmin=_min_(tmpendmax,0)+b[i];
        tmpminsum=_min_(tmpminsum,tmpendmin);
    }
    tmpminsum*=-1;
    res=_max_(tmpmaxsum, sum-tmpminsum);
    res=_max_(0,res);
}

int main()
{
    freopen("09_circular_array_max_interval_sum.txt","r",stdin);
    scanf("%d",&N);

    sum=0;
    for(int i=0;i<N;i++){
        scanf("%lld",&a[i]);
        sum+=a[i];
        b[i]=-a[i];
    }
    solve();
    printf("%lld\n",res);
    return 0;
}
