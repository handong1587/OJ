#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX_N 5005
struct edge
{
    int to;
    int cost;
};
typedef pair<int, int> P;
int N, R;
vector<edge> G[MAX_N];
int A, B, D;
int dist[MAX_N];
int dist2[MAX_N];

void solve()
{
    priority_queue< P, vector<P>, greater<P> > que;
    fill(dist, dist + N, INF);
    fill(dist2, dist2 + N, INF);
    dist[0] = 0;
    que.push(P(0, 0));
    while (!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.second;
        int d = p.first;
        if (dist2[v] < d)
            continue;
        for (int i = 0; i < G[v].size(); i++)
        {
            edge &e = G[v][i];
            int d2 = d + e.cost;
            if (dist[e.to] > d2)
            {
                swap(dist[e.to], d2);
                que.push(P(dist[e.to], e.to));
            }
            if (dist2[e.to] > d2 && dist[e.to] < d2)
            {
                dist2[e.to] = d2;
                que.push(P(dist2[e.to], e.to));
            }
        }
    }
    printf("%d\n", dist2[N - 1]);
}

int main()
{
    freopen("3255_Roadblocks.txt", "r", stdin);
    scanf("%d %d\n", &N, &R);
    for (int i = 0; i < R; i++)
    {
        scanf("%d %d %d\n", &A, &B, &D);
        G[A-1].push_back(edge{ B-1, D });
        G[B-1].push_back(edge{ A-1, D });
    }
    solve();
    return 0;
}
