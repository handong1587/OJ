#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// 51Nod_1088: 1-12: pass; 13-25: Runtime Error

#define MAX_N 1005

char str[MAX_N];

// RMQ
int size;
int dat[MAX_N * 2 - 1];

void init(int size_)
{
    size = 1;
    while(size < size_){
        size *= 2;
    }
    for(int i=0; i<2*size-1; i++){
        dat[i] = INT_MAX;
    }
}
void update(int rmq_id, int rmq_v)
{
    rmq_id += size - 1;
    dat[rmq_id] = rmq_v;
    while(rmq_id > 0){
        rmq_id = (rmq_id - 1) / 2;
        dat[rmq_id] = min(dat[rmq_id * 2 + 1], dat[rmq_id * 2 + 2]);
    }
}
// [a, b)
// [l, r)
int query(int a, int b, int rmq_id, int l, int r)
{
    if(r <= a || b <= l){
        return INT_MAX;
    }
    if(a <= l && r <= b){
        return dat[rmq_id];
    }else{
        int vl = query(a, b, rmq_id*2+1, l, (l+r)/2);
        int vr = query(a, b, rmq_id*2+2, (l+r)/2, r);
        return min(vl, vr);
    }
}
void construct_rmq(int *lcp, int size_)
{
    init(size_);
    for(int i=0; i<size_; i++){
         update(i, lcp[i]);
    }
}
int query_rmq(int a, int b)
{
    return query(a, b, 0, 0, size);
}
// end of RMQ

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

void solve(string S)
{
    int n = S.length();
    string T = S;
    reverse(T.begin(), T.end());
    S += '$' + T;

    construct_sa(S, sa);
    construct_lcp(S, sa, lcp);
    for(int i = 0; i<=S.length(); i++){
         sa_rank[sa[i]] = i;
    }
    construct_rmq(lcp, S.length() + 1);

    int ans = 0;

    for(int i = 0; i<n; i++){
         int j = n*2 - i;
         int l = query_rmq(min(sa_rank[i], sa_rank[j]), max(sa_rank[i], sa_rank[j]));
         ans = max(ans, 2 * l -1);
    }
    for(int i = 0; i<n; i++){
         int j = n*2 - i + 1;
         int l = query_rmq(min(sa_rank[i], sa_rank[j]), max(sa_rank[i], sa_rank[j]));
         ans = max(ans, 2 * l);
    }
    printf("%d\n", ans);
}

int main()
{
    freopen("51Nod\\coding_challenge\\1088_longest_palindromic_substring.txt","r",stdin);
    scanf("%s", str);

    string S(str);
    solve(S);

    return 0;
}
