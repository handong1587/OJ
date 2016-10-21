#include <stdio.h>
#include <string.h>

#define MAXM 105
#define MAXN 105

int t, m, n;
int k, x1, y1, x2, y2;
char maze[MAXM][MAXN];
bool visited[MAXM][MAXN];

int num_turns[MAXM][MAXN];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

bool dfs(int x, int y, int dire, int& turn)
{
  if (turn > k) {
    return false;
  }
  if (x == x2 && y == y2) {
    return true;
  }

  num_turns[y][x] = turn;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[ny][nx] && maze[ny][nx] == '.') {
      if (i != dire) {
        turn++;

        // pruning
        // have tried to turn around from (x,y) -> (nx,ny)
        if (num_turns[ny][nx] != -1 && turn > num_turns[ny][nx]) {
          // don't take this turn
          turn--;
          continue;
        }
        else {
          num_turns[ny][nx] = turn;
        }
      }
      else {
        num_turns[ny][nx] = num_turns[y][x];
      }

      visited[ny][nx] = true;
      if (dfs(nx, ny, i, turn)) {
        //printf("(%d, %d) -> (%d, %d), turn = %d\n", x, y, nx, ny, turn);
        return true;
      }

      visited[ny][nx] = false;
      if (i != dire) {
        turn--;
      }
    }
  }
  return false;
}

void solve()
{
  memset(visited, false, sizeof(visited));
  memset(num_turns, -1, sizeof(num_turns));
  bool ans = false;
  for (int i = 0; i < 4; i++) {
    int turn = 0;
    if (dfs(x1, y1, i, turn)) {
      ans = true;
      break;
    }
  }
  if (ans == true) {
    printf("yes\n");
  }
  else {
    printf("no\n");
  }
}

int main()
{
  freopen("HDOJ\\1728_ÌÓÀëÃÔ¹¬.txt", "r", stdin);
  scanf("%d", &t);
  for (int t_i = 0; t_i < t; t_i++) {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
      char str[MAXN];
      scanf("%s", str);
      for (int j = 0; j < n; j++) {
        maze[i][j] = str[j];
      }
    }
    scanf("%d %d %d %d %d", &k, &x1, &y1, &x2, &y2);
    x1--;
    y1--;
    x2--;
    y2--;

    solve();
  }
  return 0;
}