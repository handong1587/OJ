#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

int sticks[64];    // save sticks' length
bool used[64];
int n;            //木棍数
int len;        //木棒长度
int num;        //木棒数

/*==========================*\
idx:         current stick length
left:        current remain length
success_num: successfully spliced sticks' number
\*==========================*/
bool Sticks_DFS(int idx, int left_len, int success_num)
{
    int i;
    if (left_len == 0)    // success
    {
        if (success_num == num-2)        // after last round, only need 2 stick; count in current round, only need 1
            return true;                 // remain sticks can certainly be spliced
        for (idx=0; used[idx]; idx++)    // find stick that not used
            ;

        used[idx] = true;
        if (Sticks_DFS(idx+1, len-sticks[idx], success_num+1))    // if true: next round splice successfully
            return true;
        used[idx] = false;

        return false;    // means that if splice successfully current round, would result in failure on following rounds
    }
    else
    {
        if (idx >= n-1)
            return false;
        for (i=idx; i<n; i++)
        {
            if (used[i])
                continue;
            if (sticks[i] == sticks[i-1] && !used[i-1])    // means that last stick tried and failed, so pass
                continue;
            if (sticks[i] > left_len)
                continue;
            used[i] = true;
            if (Sticks_DFS(i, left_len-sticks[i], success_num))    // means that splice all sticks
                return true;    // 2 possibilities: 1) all spliced successfully; 2) this stick already spliced on stick
            used[i] = false;
        }
        return false;
    }
}

bool Compare(int a, int b)
{
    return a > b;
}

int main()
{
    int i, sum;
    bool finish;

    freopen("1011_Sticks.txt", "r", stdin);
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0) break;
        sum = 0;
        for (i=0; i<n; i++)
        {
            scanf("%d", &sticks[i]);
            sum += sticks[i];
        }
        std::sort(sticks, sticks+n, Compare);

        finish = false;
        for (len=sticks[0]; len<=sum/2; len++)
        {
            if (sum%len == 0)
            {
                used[0] = true;
                num = sum/len;
                if (Sticks_DFS(0, len-sticks[0], 0))    // if true: successfully spliced all sticks
                {
                    finish = true;
                    printf("%d\n", len);
                    break;
                }
                used[0] = false;
            }
        }
        if (!finish)
            printf("%d\n", sum);
        memset(used, 0, sizeof(used));
        memset(sticks, 0, sizeof(sticks));
    }
    return 0;
}
