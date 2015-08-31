#include <stdio.h>

int A,B;

int gcd(int a, int b)
{
    if(b==0){
        return a;
    }
    return gcd(b, a%b);
}

int main()
{
    freopen("1011_gcd.txt", "r", stdin);

    scanf("%d %d", &A, &B);
    int ans = gcd(A, B);
    printf("%d\n", ans);

    return 0;
}
