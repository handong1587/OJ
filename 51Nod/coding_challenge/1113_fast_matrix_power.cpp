#include <stdio.h>
#include <vector>

using namespace std;

#define Mod (1000000007)
#define MAXN 105

int N,M;
int matrix[MAXN][MAXN];

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B) //A: m*n, B: n*p
{
    mat C(A.size(), vec(B[0].size())); //C: m:p
    for (int i = 0; i < A.size(); i++)
    {
        for (int k = 0; k < B.size(); k++)
        {
            for (int j = 0; j < B[0].size(); j++)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % Mod;
            }
        }
    }
    return C;
}

mat pow(mat A, ll n)
{
    mat B(A.size(), vec(A.size()));
    for (int i = 0; i < A.size(); i++)
    {
        B[i][i] = 1;
    }
    while (n > 0)
    {
        if (n & 1)
        {
            B = mul(B, A);
        }
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

void solve()
{
    mat V(N, vec(N));
    for (int i = 0; i < V.size(); i++){
        for (int j = 0; j < V[0].size(); j++){
            V[i][j] = matrix[i][j];
        }
    }

    V = pow(V, M);
    for (int i = 0; i < V.size(); i++){
        for (int j = 0; j < V[0].size(); j++){
            printf("%lld%s", V[i][j], j==V[0].size()-1?"\n":" ");
        }
    }
}

int main()
{
    freopen("1113_fast_matrix_power.txt", "r", stdin);

    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    solve();

    return 0;
}
