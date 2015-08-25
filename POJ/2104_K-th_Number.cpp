#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

// sqrt decomposition

#define B_SIZE 1000
int n, m;
int a[100005], ai[5005], aj[5005], ak[5005];
int as[100005]; //sorted a[]
vector<int> bucket[100];

int main()
{
    freopen("2104_K-th_Number.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        as[i] = a[i];
        bucket[i / B_SIZE].push_back(a[i]);
    }
    sort(as, as + n);
    for (int i = 0; i < 100; i++)
    {
        sort(bucket[i].begin(), bucket[i].end());
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &ai[i], &aj[i], &ak[i]);
//         ai[i]--;
//         aj[i]--;
    }

    for (int i = 0; i < m; i++)
    {
        //int l = ai[i], r = aj[i] + 1, k = ak[i];
        int l = ai[i] - 1, r = aj[i], k = ak[i];
        int lb = -1, ub = n - 1;
        while (ub - lb > 1)
        {
            int mid = (lb + ub) / 2;
            int x = as[mid];
            int c = 0;
            int tl = l, tr = r;

            while (tl < tr && tl%B_SIZE != 0)
            {
                if (a[tl++] <= x)
                {
                    c++;
                }
            }
            while (tl < tr && tr%B_SIZE != 0)
            {
                if (a[--tr] <= x)
                {
                    c++;
                }
            }

            while (tl < tr)
            {
                int b = tl / B_SIZE;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += B_SIZE;
            }

            if (c >= k)
            {
                ub = mid;
            }
            else
            {
                lb = mid;
            }
        }
        printf("%d\n", as[ub]);
    }
    return 0;
}
