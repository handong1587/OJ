#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

// Longest Common substring

#define MAX_N 10005

int N;
char str1[MAX_N], str2[MAX_N];

// suffix array
int sa_length;
int k;
int sa_rank[MAX_N + 1];
int tmp[MAX_N + 1];
int sa[MAX_N + 1];
int lcp[MAX_N];

bool compare_sa(int i, int j)
{
    if (sa_rank[i] != sa_rank[j]){
        return sa_rank[i] < sa_rank[j];
    }
    else{
        int ri = i + k <= sa_length ? sa_rank[i + k] : -1;
        int rj = j + k <= sa_length ? sa_rank[j + k] : -1;
        return ri < rj;
    }
}
void construct_sa(string S, int *sa)
{
    sa_length = S.length();
    for (int i = 0; i <= sa_length; i++){
        sa[i] = i;
        sa_rank[i] = i < sa_length ? S[i] : -1;
    }
    for (k = 1; k <= sa_length; k *= 2){
        sort(sa, sa + sa_length + 1, compare_sa);
        tmp[sa[0]] = 0;
        for (int i = 0; i <= sa_length; i++){
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= sa_length; i++){
            sa_rank[i] = tmp[i];
        }
    }
}
// end of suffix array<Plug>

// LCP array: Longest Common Prefix array
void construct_lcp(string S, int *sa, int *lcp)
{
    int n = S.length();
    for(int i = 0; i <= n; i++){
        sa_rank[sa[i]] = i;
    }

    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; i++){
        int j = sa[sa_rank[i] - 1];

        if(h > 0){
            h--;
        }
        for(; j + h < n && i + h < n; h++){
            if(S[j + h] != S[i + h]){
                break;
            }
        }

        lcp[sa_rank[i] - 1] = h;
    }
}
// end of LCP array

int solve(string S, string T)
{
    int sl = S.length();
    S += '\0' + T;

    construct_sa(S, sa);
    construct_lcp(S, sa, lcp);

    int ans = 0;
    for(int i=0; i<S.length(); i++){
        if((sa[i] < sl) != (sa[i + 1] < sl)){
            ans = max(ans, lcp[i]);
        }
    }
    return ans;
}

int main()
{
    freopen("2217_Secretary.txt", "r", stdin);

    scanf("%d\n", &N);
    for(int n=0; n<N; n++){
        // weird scanf trick: read one line include whitespace exclude '\n'
        scanf("%[^\n]%*c", str1);
        scanf("%[^\n]%*c", str2);
        string S(str1);
        string T(str2);
        int ans = solve(S, T);
        printf("Nejdelsi spolecny retezec ma delku %d.\n", ans);
    }

    return 0;
}
