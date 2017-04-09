#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;

#define CLR(arr) memset(arr, 0, sizeof(arr))
#define MAX_N 500005

struct T
{
    int val;
    int idx;
}t[MAX_N];

int n;
int a[MAX_N];
int tree[MAX_N];

inline int LowBit(int idx)
{
    return idx & -idx;
}

void updateVal(int idx)
{
    while (idx <= MAX_N) {
        tree[idx]++;
        idx += LowBit(idx);
    }
}

int getSum(int idx)
{
    int sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= LowBit(idx);
    }
    return sum;
}

bool cmp(T a, T b)
{
    return a.val < b.val;

}

//将原数组t[]离散化到a[]
void decretize(int len)
{
    sort(t+1, t+1+len, cmp);
    for (int i=1; i<=len; i++)
        a[t[i].idx] = i;
}

int main()
{
    freopen("POJ2299_Input.txt", "r", stdin);
    while (scanf("%d", &n) && n>0) {
    for (int i=1; i<=n; i++) {
        scanf("%d", &t[i].val);
        t[i].idx = i;
    }
    CLR(tree);
    decretize(n);
    long long ans = 0;
    //每次迭代, i:当前已插入的数的个数; getSum(a[i]):小于等于a[i]的数的个数
    //则i-getSum(a[i])表示：比a[i]大的数的数目
    for (int i=1; i<=n; i++) {
        updateVal(a[i]);
        int sum = getSum(a[i]);
        ans += i - getSum(i);
        ans += i - sum;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
