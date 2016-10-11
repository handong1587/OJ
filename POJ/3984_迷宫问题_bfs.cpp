#include <stdio.h>
#include <queue>
#include <stack>

using namespace std;

struct Loc
{
  int x;
  int y;

  // fix build error: no appropriate default constructor available
  Loc(): x(0), y(0) {}

  Loc(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
};

int maze[5][5];
bool visited[5][5];
Loc prev_step_map[5][5];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

void print_path()
{
  stack<Loc> path;
  path.push(Loc(4, 4));
  int x = 4;
  int y = 4;
  for (;;) {
    Loc prev_step = prev_step_map[x][y];
    path.push(Loc(prev_step.x, prev_step.y));
    x = prev_step.x;
    y = prev_step.y;
    if (x == 0 && y == 0) {
      break;
    }
  }

  while (!path.empty()) {
    Loc cur_loc = path.top();
    path.pop();
    printf("(%d, %d)\n", cur_loc.x, cur_loc.y);
  }
}

void bfs()
{
  queue<Loc> q;
  q.push(Loc(0, 0));
  visited[0][0] = true;
  while (!q.empty())
  {
    Loc cur_loc = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nx = cur_loc.x + dx[i];
      int ny = cur_loc.y + dy[i];
      if (!visited[nx][ny] && maze[nx][ny] == 0 && nx >= 0 && nx < 5 && ny >= 0 && ny < 5) {
        visited[nx][ny] = true;
        q.push(Loc(nx, ny));
        prev_step_map[nx][ny] = Loc(cur_loc.x, cur_loc.y);
        if (nx == 4 && ny == 4) {
          break;
        }
      }
    }
  }
}

int main()
{
  freopen("POJ\\3984_ÃÔ¹¬ÎÊÌâ.txt", "r", stdin);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      scanf("%d", &maze[i][j]);
      visited[i][j] = false;
    }
  }

  bfs();
  print_path();

  return 0;
}