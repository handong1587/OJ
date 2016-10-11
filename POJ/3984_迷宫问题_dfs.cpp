#include <stdio.h>
#include <stack>

using namespace std;

// CAUTION: DFS cannot guarantee the shortest path, need to use BFS

#define MAXN 5

struct Loc
{
  int x;
  int y;
  Loc(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
};

int maze[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

stack<Loc> path;

void print_path()
{

}

bool dfs(int x, int y)
{
  if (x == 4 && y == 4) {
    print_path();
    return true;
  }
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (!visited[nx][ny] && maze[nx][ny] == 0 && nx >= 0 && nx < MAXN && ny >= 0 && ny < MAXN) {
      visited[nx][ny] = true;
      path.push(Loc(nx, ny));
      if (dfs(nx, ny)) {
        return true;
      }
      visited[nx][ny] = false;
      path.pop();
    }
  }
  return false;
}

int main()
{
  freopen("POJ\\3984_ÃÔ¹¬ÎÊÌâ.txt", "r", stdin);
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      scanf("%d", &maze[i][j]);
      visited[i][j] = false;
    }
  }

  visited[0][0] = true;
  path.push(Loc(0, 0));
  dfs(0, 0);

  return 0;
}