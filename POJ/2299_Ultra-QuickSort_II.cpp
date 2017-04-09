#include <stdio.h>
#include <stdlib.h>

int n;
int a[500005], c[500005];
long long cnt = 0;

//归并排序求逆序数
void MergeSort(int l, int r) {
    int mid, i, j, tmp;
    if (r > l+1) {
        mid = (l+r)/2;
        MergeSort(l, mid);
        MergeSort(mid, r);
        tmp = l;
        for (i=l, j=mid; i<mid && j<r; ) {   //将a合并到暂存向量c中，合并完成后再复制回a中
            if (a[i] > a[j]) {               //i: a[l, mid-1], j: a[mid, r-1]
                c[tmp++] = a[j++];
                cnt += mid-i;                //因为只要a[i]>a[j]，a[i, mid-1]的数字对于a[j]都是逆序的
            }
            else
                c[tmp++] = a[i++];
        }
        if (j < r) {
            for ( ; j<r; ++j)
                c[tmp++] = a[j];
        }
        else {
            for ( ; i<mid; ++i)
                c[tmp++] = a[i];
        }

        for (i=l; i<r; ++i) {
            a[i] = c[i];
        }
    }
}

int main()
{
    //freopen("POJ2299_Input.txt", "r", stdin);
    while (scanf("%d", &n), n) {
        cnt = 0;
        for (int i=0; i<n; i++) {
            scanf("%d", &a[i]);
        }
        MergeSort(0, n);
        printf("%I64d\n", cnt);
    }
    return 0;
}
