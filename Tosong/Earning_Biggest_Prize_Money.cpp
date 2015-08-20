//case: 100/100

#include <stdio.h>

#define _max_(a,b) ((a)>(b)?(a):(b))

int T,D,N,S;
int num[6];
int maxval;

int pickmax(int arr[],int start, int end, int allmaxidx[])
{
    if (end<start)
    {
        return 0;
    }
    int maxval = arr[end];
    int nmax = 0;
    allmaxidx[nmax] = end;
    nmax++;
    for (int i = end-1; i >=start;i--)
    {
        if (arr[i]>maxval)
        {
            nmax = 0;
            allmaxidx[nmax] = i;
            maxval = arr[i];
            nmax++;
        }
        else if (arr[i]==maxval)
        {
            allmaxidx[nmax] = i;
            nmax++;
        }
    }
    return nmax;
}

bool is_sorted(int arr[])
{
    for (int i = 0; i <N-1;i++)
    {
        if (arr[i]<arr[i+1])
        {
            return false;
        }
    }
    return true;
}

int array2num(int arr[])
{
    int res = 0;
    for (int i = 0; i<N; i++)
    {
        res = res * 10 + arr[i];
    }
    return res;
}

void testprint(int arr[],int cur_depth)
{
    printf("round %d: [ ",cur_depth);
    for (int i = 0; i < N;i++)
    {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void plot(int arr[],int src,int dst)
{
    for (int i = 0; i < N;i++)
    {
        if (i==src||i==dst)
        {
            printf("[%d] ", arr[i]);
        }
        else
        {
            printf(" %d  ", arr[i]);
        }
        if (i==N-1)
        {
            printf("\n");
        }
    }
}

int locate(int arr[])
{
    for (int i = N - 1; i >= 1;i--)
    {
        if (arr[i]!=arr[i-1])
        {
            return i;
        }
    }
    return N - 1;
}

void dfs(int arr[],int start, int cur_depth,int tgt_depth)
{
    if (cur_depth==tgt_depth)
    {
        int val = array2num(arr);
        maxval = _max_(maxval, val);
        return;
    }
//     if (start == N - 1)
//     {
//         return;
//     }
    if (is_sorted(arr))
    {
        int tgtidx = locate(arr);

        //plot(arr, tgtidx - 1, tgtidx);

        int tmp = arr[tgtidx];
        arr[tgtidx] = arr[tgtidx - 1];
        arr[tgtidx - 1] = tmp;

        //plot(arr, tgtidx - 1, tgtidx);

        dfs(arr,tgtidx-1, cur_depth + 1, tgt_depth);
        tmp = arr[tgtidx];
        arr[tgtidx] = arr[tgtidx - 1];
        arr[tgtidx - 1] = tmp;
    }
    int tidxs[6];
    int nmaxidx = pickmax(arr,start, N - 1,tidxs);
    for (int i = 0; i < nmaxidx;i++)
    {
        if (tidxs[i]==start) // current start number is maximum, don't do anything. dfs remaining numbers
        {
            dfs(arr,start + 1, cur_depth, tgt_depth);
        }
        // otherwise, exchange current start number and that maximum number
        else
        {
            //plot(arr, start, tidxs[i]);

            int tmp = arr[start];
            arr[start] = arr[tidxs[i]];
            arr[tidxs[i]] = tmp;

            //plot(arr, start, tidxs[i]);

            dfs(arr, start + 1, cur_depth + 1, tgt_depth);
            tmp = arr[start];
            arr[start] = arr[tidxs[i]];
            arr[tidxs[i]] = tmp;
        }
    }
}

void solve()
{
    int arr[6];
    for (int i = 0; i < N;i++)
    {
        arr[i] = num[i];
    }
    int maxval = 0;
    for (int i = 0; i < N; i++)
    {
        dfs(arr,i, 0, S);
    }
}

int main()
{
    freopen("Earning_Biggest_Prize_Money.txt", "r", stdin);
    scanf("%d\n", &T);
    for (int t = 0; t < T;t++)
    {
        scanf("%d%d\n", &D, &S);
        N = 0;
        int tmpD = D;
        int tmpnum[6];
        for (int i = 0; i < 6;i++)
        {
            int d = tmpD % 10;
            tmpnum[i] = d;
            tmpD /= 10;
            N++;
            if (tmpD == 0)
            {
                break;
            }
        }
        for (int i = 0; i < N;i++)
        {
            num[i] = tmpnum[N - 1 - i];
        }
        maxval = -1;
        solve();
        printf("#%d %d\n", t + 1, maxval);
    }
    return 0;
}
