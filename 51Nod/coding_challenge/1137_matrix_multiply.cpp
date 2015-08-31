#include <stdio.h>
#include <string.h>

#define MAXN 105

int N;
int M1[MAXN][MAXN];
int M2[MAXN][MAXN];
int M3[MAXN][MAXN];

void solve()
{
    memset(M3, 0, sizeof(M3));
    for(int i=0; i<N; i++){
        for(int k=0; k<N; k++){
            for(int j=0; j<N; j++){
                M3[i][j] = M3[i][j] + M1[i][k] * M2[k][j];
            }
        }
    }
}

void print()
{
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d%s", M3[i][j], j==N-1?"\n":" ");
        }
    }
}

int main()
{
    freopen("1137_matrix_multiply.txt", "r", stdin);
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &M1[i][j]);
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &M2[i][j]);
        }
    }

    solve();
    print();

    return 0;
}
