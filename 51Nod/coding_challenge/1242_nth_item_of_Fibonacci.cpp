#include <stdio.h>
#include <vector>

using namespace std;

#define M 1000000009

typedef long long ll;
ll n;

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
    mat A(2, vec(2));
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 0;
    A= pow(A, n);
    printf("%lld\n", A[1][0]);
}

int main()
{
    freopen("1242_nth_item_of_Fibonacci.txt", "r", stdin);
    scanf("%lld", &n);

    solve();

    return 0;
}
