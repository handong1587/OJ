#include <stdio.h>

int N;
int a[50005];
int c[50005];
int cnt;

void MergeSort(int l, int r)
{
    int mid, i, j, tmp;
    if( r > l+1 ){
        mid = (l+r)/2;
        MergeSort(l, mid);
        MergeSort(mid, r);
        tmp = l;
        for( i=l, j=mid; i < mid && j < r; ){
            if( a[i] > a[j] ){
                c[tmp++] = a[j++];
                cnt += mid-i;
            }
            else c[tmp++] = a[i++];
        }
        if( j < r )
            for( ; j < r; ++j )
                c[tmp++] = a[j];
        else
            for( ; i < mid; ++i )
                c[tmp++] = a[i];
        for ( i=l; i < r; ++i )
            a[i] = c[i];
    }
}

int main()
{
    freopen("1019_inverse_number.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    cnt = 0;
    MergeSort(0, N);
    printf("%d\n", cnt);
    return 0;
}
