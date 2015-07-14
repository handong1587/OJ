#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))
#define _min_(a,b) ((a)<(b)?(a):(b))

int N;
long long a[50005],b[50005];
long long sum,res;

void solve()
{
    //int mid=N/2;
    long long maxsum=a[0];
    long long endmax=a[0];
    for(int i=1;i<N;i++){
        endmax=_max_(endmax,0)+a[i];
        maxsum=_max_(maxsum,endmax);
    }

    long long maxsum2=b[0];
    long long endmax2=b[0];
    for(int i=1;i<N;i++){
        endmax2=_max_(endmax2,0)+b[i];
        maxsum2=_max_(maxsum2,endmax2);
    }

    //printf("sum=%lld, maxsum=%lld, maxsum2=%lld\n",sum,maxsum,maxsum2);

    long long minsum = maxsum2 * -1;
    //printf("%minsun=lld\n",minsum);
    res=_max_(maxsum, sum-minsum);
    res=_max_(0,res);
}

int main()
{
    freopen("09_circular_array_max_interval_sum_case16.txt","r",stdin);
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
