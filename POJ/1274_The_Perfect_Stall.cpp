#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f
#define MAXV (200 * 2 + 16) // ?

// bipartite graph matching: Ford-Fulkerson, adjacency list
// <挑战程序设计> page-212

struct edge
{
  int to;
  int cap;
  int rev;
  edge(int to, int cap, int rev) {
    this->to = to;
    this->cap = cap;
    this->rev = rev;
  }
};

vector<edge> G[MAXV];
bool used[MAXV];
int N, M;
int can_milk[MAXV][MAXV];

// solution 1
void add_edge(int from, int to, int cap)
{
  edge e1(to, cap, G[to].size());
  G[from].push_back(e1);
  edge e2(from, 0, G[from].size() - 1);
  G[to].push_back(e2);
}

int dfs(int v, int t, int f)
{
  if (v == t) {
    return f;
  }
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if (!used[e.to] && e.cap > 0) {
      int d = dfs(e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t)
{
  int flow = 0;
  for (;;) {
    memset(used, 0, sizeof(used));
    int f = dfs(s, t, INF);
    if (f == 0) {
      return flow;
    }
    flow += f;
  }
}

// cow:   0 ~ N-1
// stall: N ~ N+M-1
void solve()
{
  int s = N + M;
  int t = s + 1;
  // cow
  for (int i = 0; i < N; i++) {
    add_edge(s, i, 1);
  }
  // stall
  for (int i = 0; i < M; i++) {
    add_edge(N + i, t, 1);
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (can_milk[i][j]) {
        add_edge(i, N + j, 1);
      }
    }
  }
  printf("%d\n", max_flow(s, t));
}

// solution 2
int V;
vector<int> G_2[MAXV];
int match[MAXV];
void add_edge_2(int u, int v)
{
  G_2[u].push_back(v);
  G_2[v].push_back(u);
}

bool dfs_2(int v)
{
  used[v] = true;
  for (int i = 0; i < G_2[v].size(); i++) {
    int u = G_2[v][i];
    int w = match[u];
    if (w < 0 || !used[w] && dfs_2(w)) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

int bipartite_matching()
{
  int res = 0;
  memset(match, -1, sizeof(match));
  for (int v = 0; v < V; v++) {
    if (match[v] < 0) {
      memset(used, 0, sizeof(used));
      if (dfs_2(v)) {
        res++;
      }
    }
  }
  return res;
}

int main()
{
  freopen("POJ\\1274_The_Perfect_Stall.txt", "r", stdin);
  while (scanf("%d %d", &N, &M) != EOF) {
    V = N + M;
    // init
    memset(can_milk, 0, sizeof(can_milk));
    for (int i = 0; i < MAXV; i++) {
      G[i].clear();
      G_2[i].clear();
    }
    for (int cow_i = 0; cow_i < N; cow_i++) {
      int num;
      scanf("%d", &num);
      for (int i = 0; i < num; i++) {
        int stall_i;
        scanf("%d", &stall_i);
        stall_i--;
        can_milk[cow_i][stall_i] = 1;

        //
        add_edge_2(cow_i, stall_i + N);
      }
    }
    // solution 1
    //solve();
    // solution 2
    printf("%d\n", bipartite_matching());
  }
  return 0;
}