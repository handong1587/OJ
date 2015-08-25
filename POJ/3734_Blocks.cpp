#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// matrix power

#define M 10007
int t, n;

typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

mat mul(mat &A, mat &B) //A: m*n, B: n*p
{
    mat C(A.size(), vec(B[0].size())); //C: m:p
    for (int i = 0; i < A.size(); i++)
    {
        for (int k = 0; k < B.size(); k++)
        {
            for (int j = 0; j < B[0].size(); j++)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
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
    mat A(3, vec(3));
    A[0][0] = 2; A[0][1] = 1; A[0][2] = 0;
    A[1][0] = 2; A[1][1] = 2; A[1][2] = 2;
    A[2][0] = 0; A[2][1] = 1; A[2][2] = 2;
    A = pow(A, n);
    printf("%d\n", A[0][0]);
}

int main()
{
    freopen("3734_Blocks.txt", "r", stdin);
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        solve();
    }
    return 0;
}
