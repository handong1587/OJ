#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// force search

int n, nc;
char s[16000005];
char e[16000005];
char c[260];
int cnt;
int main()
{
    freopen("1200_Crazy_Search.txt", "r", stdin);
    scanf("%d %d", &n, &nc);
    scanf("%s", s);
    int l = strlen(s);
    memset(c, 0, sizeof(c));
    cnt = 0;
    for (int i = 0; i < l; i++)
    {
        if (c[s[i]] == 0)
        {
            c[s[i]] = ++cnt;
        }
        if (cnt==nc)
        {
            break;
        }
    }
    int k = l - n;
    int sum;
    cnt = 0;
    for (int i = 0; i <= k; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += sum*nc + c[s[i + j]];
        }
        if (e[sum] == 0)
        {
            e[sum] = 1;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
