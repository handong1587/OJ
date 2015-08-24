// 4.7.3: suffix array

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int n,k;
int a[200005];
int rev[400005];
int sa[400005];
int sa_rank[200005];
int tmp_rank[200005];

bool compare_sa(int i, int j)
{
    if (sa_rank[i] != sa_rank[j])
    {
        return sa_rank[i] < sa_rank[j];
    }
    else
    {
        int ri = i + k <= n ? sa_rank[i + k] : -1;
        int rj = j + k <= n ? sa_rank[j + k] : -1;
        return ri < rj;
    }
}

void construct_sa(int *_rev_, int _n_, int *_sa_)
{
    for (int i = 0; i <= _n_; i++)
    {
        sa[i] = i;
        sa_rank[i] = i < _n_ ? _rev_[i] : -1;//
    }
    for (k = 1; k <= _n_; k *= 2)
    {
        sort(sa, sa + _n_ + 1, compare_sa);
        tmp_rank[sa[0]] = 0;
        for (int i = 0; i <= _n_; i++)
        {
            tmp_rank[sa[i]] = tmp_rank[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= _n_; i++)
        {
            sa_rank[i] = tmp_rank[i];
        }
    }
}

int main()
{
    freopen("3581_Sequence.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    reverse_copy(a, a + n, rev);
    construct_sa(rev, n, sa);
    int p1;
    for (int i = 0; i < n; i++)
    {
        p1 = n - sa[i];
        if (p1 >= 1 && n-p1 >= 2)
        {
            break;
        }
    }
    int m = n - p1;
    reverse_copy(a + p1, a + n, rev);
    reverse_copy(a + p1, a + n, rev + m);
    construct_sa(rev, m * 2, sa);

    int p2;
    for (int i = 0; i <= m * 2; i++)
    {
        p2 = p1 + m - sa[i];
        if (p2 - p1 >= 1 && n - p2 >= 1)
        {
            break;
        }
    }
    reverse(a, a + p1);
    reverse(a + p1, a + p2);
    reverse(a + p2, a + n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
    return 0;
}
