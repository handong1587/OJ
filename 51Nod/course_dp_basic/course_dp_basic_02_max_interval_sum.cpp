#include <stdio.h>
#define _max_(a,b) ((a)>(b)?(a):(b))
int N;
long long A[50005];
long long endmax;
long long vmax;

int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%lld",&A[i]);
    }
    endmax=A[0];
    vmax=A[0];
    for(int i=1;i<N;i++){
        endmax=_max_(endmax,0)+A[i];
        vmax=_max_(vmax,endmax);
    }
    printf("%lld\n",_max_(vmax,0));
    return 0;
}
