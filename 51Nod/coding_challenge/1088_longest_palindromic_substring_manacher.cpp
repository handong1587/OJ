#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <climits>

using namespace std;

// see: http://taop.marchtea.com/01.05.html

// 4.7.3 Suffix Array
// 51Nod_1088: 1-12: pass; 13-25: Runtime Error

#define MAX_N 1005

char str[MAX_N];
int N;
int S[MAX_N * 2];
int P[MAX_N * 2];

void init()
{
    N = strlen(str);
    S[0] = '$';
    int i, j;
    for(i=0, j=1; i<N; i++){
        S[j++] = '#';
        S[j++] = str[i];
    }
    S[j++] = '#';
    S[j] = '\0';
    memset(P, 0, sizeof(P));
}

int manacher()
{
    int mx = 0, id = 0;
    for (int i = 1; S[i] != '\0'; i++){
        P[i] = mx > i ? min(P[2 * id - i], mx - i) : 1;
        while (S[i + P[i]] == S[i - P[i]])
            P[i]++;
        if (i + P[i] > mx){
            mx = i + P[i];
            id = i;
        }
    }
    int res = 0;
    for(int i=1; i<2*N+2; i++){
         res = max(res, P[i]);
    }
    return res - 1;
}

int main()
{
    freopen("1088_longest_palindromic_substring.txt","r",stdin);
    scanf("%s", str);

    init();
    int ans = manacher();

    printf("%d\n", ans);

    return 0;
}
