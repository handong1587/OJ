#include <stdio.h>
#include <stdlib.h>

#define MAXK 100005

int N, K;
int D[MAXK], X[MAXK], Y[MAXK];

//union-find
int parent[MAXK];
int rank[MAXK];

void init(int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x)
{
    if (parent[x] == x) {
        return x;
    }
    else {
        return find(parent[x]);
    }
}

void unite(int x, int y)
{
    int px = find(x);
    int py = find(y);
    if (px == py) {
        return;
    }

    if (rank[px] < rank[py]) {
        parent[px] = py;
    }
    else {
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }
}

bool same(int x, int y)
{
    return find(x) == find(y);
}

int main()
{
    //freopen("poj1182_Ê³ÎïÁ´.txt", "r", stdin);
    scanf("%d %d\n", &N, &K);
    init(N * 3);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d\n", &D[i], &X[i], &Y[i]);
        int d = D[i];
        int x = X[i] - 1;
        int y = Y[i] - 1;
        if (x < 0 || x >= N || y < 0 || y >= N) {
            ans++;
            continue;
        }

        if (d == 1) {
            if (same(x, y + N) || same(x, y + N * 2)) {
                ans++;
            }
            else {
                unite(x, y);
                unite(x + N, y + N);
                unite(x + N * 2, y + N * 2);
            }
        }
        else {
            if (same(x, y) || same(x, y + N * 2)) {
                ans++;
            }
            else {
                unite(x, y + N);
                unite(x + N, y + N * 2);
                unite(x + N * 2, y);
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}