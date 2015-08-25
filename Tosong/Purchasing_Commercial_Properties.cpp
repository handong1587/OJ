#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int T;
int N, K;
struct Rect
{
    int x1;
    int y1;
    int x2;
    int y2;
};
struct Point
{
    int x;
    int y;
};

Rect rect[100005];
int prop[3005][3005];

void init()
{
    memset(prop, 0, sizeof(prop));
    for (int i = 1; i <= N; i++)
    {
        for (int x = rect[i].x1; x <= rect[i].x2; x++)
        {
            for (int y = rect[i].y1; y <= rect[i].y2; y++)
            {
                prop[x][y] = i;
            }
        }
    }
}
bool cmp(Rect r1, Rect r2)
{
    if (r1.x1 == r2.x1)
    {
        return r1.y1 < r2.y1;
    }
    return r1.x1 < r2.x1;
}

bool judge(Point start, int sideLen)
{
    int curX1 = start.x;
    int curY1 = start.y;
    // check not-purchased land
    for (int x = curX1; x < curX1 + sideLen; x++)
    {
        for (int y = curY1; y < curY1 + sideLen; y++)
        {
            if (prop[x][y] == 0)
            {
                return false;
            }
        }
    }
    int borderX = curX1 + sideLen - 1;
    int borderY = curY1 + sideLen - 1;
    // check not-completely used land
    for (int x = curX1; x < borderX; x++)
    {
        int curProp = prop[x][borderY];
        Rect curRect = rect[curProp];
        if (curRect.x2 > borderX ||
            curRect.y2 > borderY)
        {
            return false;
        }
    }
    for (int y = curY1; y < borderY; y++)
    {
        int cur_prop = prop[borderX][y];
        Rect cur_rect = rect[cur_prop];
        if (cur_rect.x2 > borderX ||
            cur_rect.y2 > borderY)
        {
            return false;
        }
    }
    return true;
}

int decide(Point start)
{
    int curProp = prop[start.x][start.y];
    int curX1 = rect[curProp].x1;
    int curY1 = rect[curProp].y1;
    int curX2 = rect[curProp].x2;
    int curY2 = rect[curProp].y2;
    int curW = curX2 - curX1 + 1;
    int curH = curY2 - curY1 + 1;
    int curSideLen = 0;
    if (curW == curH)
    {
        if (judge(start, curW))
        {
            curSideLen = max(curSideLen, curW);
        }
    }
    int nextRightX = curX2;
    int nextDownY = curY2;
    if (curW < curH)
    {
        nextRightX = curX2 + 1;
    }
    else
    {
        nextDownY = curY2 + 1;
    }

    while (nextRightX <= K && nextDownY <= K)
    {
        int nextRightProp = prop[nextRightX][curY1];
        int nextDownProp = prop[curX1][nextDownY];
        if (rect[nextRightProp].y1 < curY1 ||
            rect[nextDownProp].x1 < curX1)
        {
            break;
        }
        int nextW = rect[nextRightProp].x2 - curX1 + 1;
        int nextH = rect[nextDownProp].y2 - curY1 + 1;
        if (nextW == nextH)
        {
            if (judge(start, nextW))
            {
                curSideLen = max(curSideLen, nextW);
            }
        }
        if (nextW < nextH)
        {
            nextRightX = rect[nextRightProp].x2 + 1;
        }
        else
        {
            nextDownY = rect[nextDownProp].y2 + 1;
        }
    }
    return curSideLen;
}

int solve()
{
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        Point start;
        start.x = rect[i].x1;
        start.y = rect[i].y1;

        int res = decide(start);
        ans = max(ans, res);
    }
    return ans;
}

int main()
{
    freopen("Purchasing_Commercial_Properties.txt", "r", stdin);
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
    {
        scanf("%d %d", &N, &K);
        for (int i = 1; i <= N; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
            rect[i].x1 = x1;
            rect[i].y1 = y1;
            rect[i].x2 = x2-1;
            rect[i].y2 = y2-1;
        }
        sort(rect + 1, rect + N + 1, cmp);
        init();
        int ans = solve();
        printf("#%d %d\n", t, ans);
    }
    return 0;
}
