#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int Base = 1000000000;
const int Capacity = 100;
typedef long long huge;

struct BigInt {
    int Len;
    int Data[Capacity];
    BigInt() : Len(0) {}
    BigInt(const BigInt &V) : Len(V.Len) { memcpy(Data, V.Data, Len * sizeof*Data); }
    BigInt(int V) : Len(0) { for (; V>0; V /= Base) Data[Len++] = V%Base; }
    BigInt &operator=(const BigInt &V) { Len = V.Len; memcpy(Data, V.Data, Len * sizeof*Data); return *this; }
    int &operator[] (int Index) { return Data[Index]; }
    int operator[] (int Index) const { return Data[Index]; }
};
int compare(const BigInt &A, const BigInt &B) {
    if (A.Len != B.Len) return A.Len>B.Len ? 1 : -1;
    int i;
    for (i = A.Len - 1; i >= 0 && A[i] == B[i]; i--);
    if (i<0)return 0;
    return A[i]>B[i] ? 1 : -1;
}

BigInt operator+(const BigInt &A, const BigInt &B) {
    int i, Carry(0);
    BigInt R;
    for (i = 0; i<A.Len || i<B.Len || Carry>0; i++) {
        if (i<A.Len) Carry += A[i];
        if (i<B.Len) Carry += B[i];
        R[i] = Carry%Base;
        Carry /= Base;
    }
    R.Len = i;
    return R;
}

BigInt operator-(const BigInt &A, const BigInt &B) {
    int i, Carry(0);
    BigInt R;
    R.Len = A.Len;
    for (i = 0; i<R.Len; i++) {
        R[i] = A[i] - Carry;
        if (i<B.Len) R[i] -= B[i];
        if (R[i]<0) Carry = 1, R[i] += Base;
        else Carry = 0;
    }
    while (R.Len>0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

BigInt operator*(const BigInt &A, const int &B) {
    int i;
    huge Carry(0);
    BigInt R;
    for (i = 0; i<A.Len || Carry>0; i++) {
        if (i<A.Len) Carry += huge(A[i])*B;
        R[i] = Carry%Base;
        Carry /= Base;
    }
    R.Len = i;
    return R;
}
istream &operator >> (istream &In, BigInt &V) {
    char Ch;
    for (V = 0; In >> Ch;) {
        V = V * 10 + (Ch - '0');
        if (In.peek() <= ' ') break;
    }
    return In;
}
ostream &operator<<(ostream &Out, const BigInt &V) {
    int i;
    Out << (V.Len == 0 ? 0 : V[V.Len - 1]);
    for (i = V.Len - 2; i >= 0; i--) for (int j = Base / 10; j>0; j /= 10) Out << V[i] / j % 10;
    return Out;
}

#define MAXN 250
BigInt dp[MAXN + 5];

void init()
{
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 3;
    dp[3] = 5;

    for (int i = 4; i <= MAXN; i++) {
        dp[i] = dp[i - 2] * 2 + dp[i - 1];
    }
}

void solve(int n)
{
    cout << dp[n] << endl;
}

int main()
{
    freopen("POJ\\2506_Tiling.txt", "r", stdin);
    int n;
    init();
    while (scanf("%d", &n) != EOF) {
        solve(n);
    }
    return 0;
}