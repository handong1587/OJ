#include <stdio.h>

#define MAXN 105
#define INF 0x3f3f3f3f
#define _min_(a,b) ((a)<(b)?(a):(b))

int T;
int N;
int mat[MAXN][MAXN];
int cost[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

void init()
{
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            cost[i][j] = INF;
            visited[i][j] = false;
        }
    }
}

void solve()
{
    cost[0][0] = 0;
    while (true){
        int cx = -1;
        int cy = -1;
        for (int x = 0; x < N; x++){
            for (int y = 0; y < N; y++){
                if (!visited[x][y] && ((cx == -1 || cy == -1) || cost[x][y] < cost[cx][cy])){
                    cx = x;
                    cy = y;
                }
            }
        }
        if (cx == -1 || cy == -1){
            break;
        }
        visited[cx][cy] = true;
        for (int x = 0; x < 4; x++){
            int nx = cx + dx[x];
            int ny = cy + dy[x];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N){
                cost[nx][ny] = _min_(cost[nx][ny], cost[cx][cy] + mat[nx][ny]);
            }
        }
    }
}

int main()
{
    freopen("Supply_Route.txt","r",stdin);
    scanf("%d", &T);
    for(int t=1;t<=T;t++){
        init();
        scanf("%d",&N);
        char s[MAXN];
        for(int i=0;i<N;i++){
            scanf("%s",s);
            for(int j=0;j<N;j++){
                mat[i][j]=(int)(s[j]-'0');
            }
        }
        solve();
        printf("#%d %d\n",t, cost[N-1][N-1]);
    }
    return 0;
}
