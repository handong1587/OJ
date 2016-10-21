#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define MAXM 105
#define MAXN 105

struct Pos
{
  int x;
  int y;
  int dire;
  int turn;
  Pos(int a, int b, int d, int t) : x(a), y(b), dire(d), turn(t) { }
};

int t, m, n;
// error C2365: 'y1' : redefinition; previous definition was funciton ???
// c:\program files\windows kits\10\include\10.0.10240.0\ucrt\math.h(972)
int k, x1, y_1, x2, y2;
char maze[MAXM][MAXN];
bool visited[MAXM][MAXN][4];
int num_turns[MAXM][MAXN][4];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

bool bfs()
{
  memset(visited, false, sizeof(visited));
  memset(num_turns, 0, sizeof(num_turns));
  queue<Pos> Q;
  
  // init with 4 directions
  for (int i = 0; i < 4; i++) {
    int nx = x1 + dx[i];
    int ny = y_1 + dy[i];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[ny][nx] == '.') {
      if (nx == x2 && ny == y2) {
        return true;
      }

      Q.push(Pos(nx, ny, i, 0));
      visited[ny][nx][i] = true;
    }
  }

  while (!Q.empty()) {
    Pos cur_pos = Q.front();
    Q.pop();

    int x = cur_pos.x;
    int y = cur_pos.y;
    int dire = cur_pos.dire;
    int turn = cur_pos.turn;
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[ny][nx] == '.') {
        int cur_turn = i != dire ? turn + 1 : turn;

        if (cur_turn > k) {
          continue;
        }

        // you can visit (nx, ny) several times from different direction
        // but latest visit should take fewer turns
        if (visited[ny][nx][i] && cur_turn >= num_turns[ny][nx][i]) {
          continue;
        }

        // otherwise just try
        Q.push(Pos(nx, ny, i, cur_turn));
        visited[ny][nx][i] = true;
        num_turns[ny][nx][i] = cur_turn;

        if (nx == x2 && ny == y2) {
          return true;
        }
      }
    }
  }
  return false;
}

int main()
{
  freopen("HDOJ\\1728_Ã”¿Î√‘π¨.txt", "r", stdin);
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
    scanf("%d %d %d %d %d", &k, &x1, &y_1, &x2, &y2);
    x1--;
    y_1--;
    x2--;
    y2--;

    bool ans = bfs();
    if (ans) {
      printf("yes\n");
    }
    else {
      printf("no\n");
    }
  }
  return 0;
}