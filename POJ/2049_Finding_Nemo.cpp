#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define max(a, b) ((a)>(b)?(a):(b))
#define MAXN 205

enum BlockType { NOTHING, WALL, DOOR };
struct Loc
{
  BlockType left;
  BlockType right;
  BlockType top;
  BlockType bottom;
};

struct Pos
{
  int x;
  int y;
  int dx;
  int dy;
  Pos(): x(0), y(0), dx(0), dy(0) {}
  Pos(int a, int b) : x(a), y(b) {}
  Pos(int a, int b, int c, int d) : x(a), y(b), dx(c), dy(d) {}
};

int M, N;
float f1, f2;
int nemo_x, nemo_y;
Loc seaMap[MAXN][MAXN];
bool visited[MAXN][MAXN];
int max_x, max_y;
Pos prev_step[MAXN][MAXN];
bool through_door[MAXN][MAXN];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

void bfs()
{
  queue<Pos> Q;
  queue<Pos> Q2;
  memset(visited, false, sizeof(visited));
  memset(through_door, false, sizeof(through_door));
  Q.push(Pos(0, 0));
  visited[0][0] = true;

  bool findNemo = false;
  while (!Q.empty() || !Q2.empty())
  {
    Pos cur_pos;
    if (!Q.empty()) { // consider not through doors
      cur_pos = Q.front();
      Q.pop();

      int x = cur_pos.x;
      int y = cur_pos.y;
      if (x == nemo_x && y == nemo_y) {
        findNemo = true;
        break;
      }

      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < max_x && ny >= 0 && ny < max_y && !visited[nx][ny]) {
          switch (i)
          {
          case 0:
            if (seaMap[x][y].left != WALL) {
              if (seaMap[x][y].left == DOOR) {
                Q2.push(Pos(x, y, dx[i], dy[i])); // if through a door: save location and direction
              }
              else {
                Q.push(Pos(nx, ny));
                visited[nx][ny] = true;
                prev_step[nx][ny] = Pos(x, y);

                //printf("nothing: (%d, %d) -> (%d, %d)\n", x, y, nx, ny);
              }
            }
            break;
          case 1:
            if (seaMap[x][y].bottom != WALL) {
              if (seaMap[x][y].bottom == DOOR) {
                Q2.push(Pos(x, y, dx[i], dy[i]));
              }
              else {
                Q.push(Pos(nx, ny));
                visited[nx][ny] = true;
                prev_step[nx][ny] = Pos(x, y);

                //printf("nothing: (%d, %d) -> (%d, %d)\n", x, y, nx, ny);
              }
            }
            break;
          case 2:
            if (seaMap[x][y].right != WALL) {
              if (seaMap[x][y].right == DOOR) {
                Q2.push(Pos(x, y, dx[i], dy[i]));
              }
              else {
                Q.push(Pos(nx, ny));
                visited[nx][ny] = true;
                prev_step[nx][ny] = Pos(x, y);

                //printf("nothing: (%d, %d) -> (%d, %d)\n", x, y, nx, ny);
              }
            }
            break;
          case 3:
            if (seaMap[x][y].top != WALL) {
              if (seaMap[x][y].top == DOOR) {
                Q2.push(Pos(x, y, dx[i], dy[i]));
              }
              else {
                Q.push(Pos(nx, ny));
                visited[nx][ny] = true;
                prev_step[nx][ny] = Pos(x, y);

                //printf("nothing: (%d, %d) -> (%d, %d)\n", x, y, nx, ny);
              }
            }
            break;
          }
        }
      }
    }
    else if (!Q2.empty()) {
      cur_pos = Q2.front();
      Q2.pop();
      int x = cur_pos.x;
      int y = cur_pos.y;
      if (x == nemo_x && y == nemo_y) {
        findNemo = true;
        break;
      }
      int nx = cur_pos.x + cur_pos.dx;
      int ny = cur_pos.y + cur_pos.dy;
      visited[nx][ny] = true;
      prev_step[nx][ny] = Pos(cur_pos.x, cur_pos.y);
      through_door[nx][ny] = true;
      Q.push(Pos(nx, ny));
      //printf("door: (%d, %d) -> (%d, %d)\n", x, y, nx, ny);
    }
  }

  if (findNemo) {
    Pos cur = Pos(nemo_x, nemo_y);
    int numDoors = 0;
    for (;;) {
      if (through_door[cur.x][cur.y] == true) {
        numDoors++;
      }
      Pos prev = prev_step[cur.x][cur.y];
      if (prev.x == 0 && prev.y == 0) {
        break;
      }
      cur.x = prev.x;
      cur.y = prev.y;
    }
    printf("%d\n", numDoors);;
  }
  else {
    printf("-1\n");
  }
}

int main()
{
  freopen("POJ\\2049_Finding_Nemo.txt", "r", stdin);
  while (scanf("%d %d", &M, &N) != EOF) {
    if (M == -1 && N == -1) {
      break;
    }
    memset(seaMap, NOTHING, sizeof(seaMap));
    max_x = -1;
    max_y = -1;
    for (int i = 0; i < M; i++) {
      int x, y, d, t;
      scanf("%d %d %d %d", &x, &y, &d, &t);
      if (d == 0) {
        for (int j = 0; j < t; j++) {
          seaMap[x + j][y].bottom = WALL;
          seaMap[x + j][y - 1].top = WALL;
        }
        max_x = max(x + t + 1, max_x);
        max_y = max(y + 1, max_y);
      }
      else {
        for (int j = 0; j < t; j++) {
          seaMap[x][y + j].left = WALL;
          seaMap[x - 1][y + j].right = WALL;
        }
        max_x = max(x + 1, max_x);
        max_y = max(y + t + 1, max_y);
      }
    }

    for (int i = 0; i < N; i++) {
      int x, y, d;
      scanf("%d %d %d", &x, &y, &d);
      if (d == 0) {
        seaMap[x][y].bottom = DOOR;
        seaMap[x][y - 1].top = DOOR;
      }
      else {
        seaMap[x][y].left = DOOR;
        seaMap[x - 1][y].right = DOOR;
      }
    }

    scanf("%f %f", &f1, &f2);
    nemo_x = (int)f1;
    nemo_y = (int)f2;
    
    // TRICK TRICK TRICK
    if (nemo_x < 0 || nemo_y < 0 || nemo_x > 199 || nemo_y > 199 || (N == 0 && M == 0)) {
      printf("0\n");
    }
    else {
      bfs();
    }
  }
  return 0;
}