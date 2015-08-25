#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int n, k, m;

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
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % m;
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

int main()
{
    freopen("3233_Matrix_Power_Series.txt", "r", stdin);
    scanf("%d %d %d", &n, &k, &m);
    mat A(n, vec(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    mat B(n * 2, vec(n * 2));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = A[i][j];
        }
        B[n + i][i] = B[n + i][n + i] = 1;
    }
    B = pow(B, k + 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a = B[n + i][j] % m;
            if (i == j)
            {
                a = (a + m - 1) % m;
            }
            printf("%d%c", a, j + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
