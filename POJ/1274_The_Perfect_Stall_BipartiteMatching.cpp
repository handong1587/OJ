#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))
#define INF 0x3f3f3f3f
#define MAXN 205
#define MAXM 205
#define MAXV (MAXN + MAXM) // ?

// bipartite graph matching: adjacency list

bool used[MAXV];
int N, M;
int V;
vector<int> G[MAXV];
int match[MAXV];
void add_edge(int u, int v)
{
  G[u].push_back(v);
  G[v].push_back(u);
}

bool dfs(int v)
{
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    int u = G[v][i];
    int w = match[u];
    if (w < 0 || !used[w] && dfs(w)) {
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
      if (dfs(v)) {
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
    for (int i = 0; i < V; ++i) {
      G[i].clear();
    }

    for (int cow_i = 0; cow_i < N; cow_i++) {
      int Si;
      scanf("%d", &Si);
      for (int i = 0; i < Si; i++) {
        int stall_i;
        scanf("%d", &stall_i);
        stall_i = stall_i + N - 1;
        add_edge(cow_i, stall_i);
      }
    }
    printf("%d\n", bipartite_matching());
  }
  return 0;
}