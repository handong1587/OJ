#include <stdio.h>

int N;

int loop_result[10][4] = {
    0,0,0,0, //0
    1,1,1,1, //1
    2,4,8,6, //2: 2,4,8,16
    3,9,7,1, //3: 3,9,27,81
    4,6,4,6, //4: 4,16
    5,5,5,5, //5
    6,6,6,6, //6
    7,9,3,1, //7: 7,49,343,2401
    8,4,2,6, //8: 8,64,512,4096
    9,1,9,1, //9: 9,81
};

int solve()
{
    int last_digit = N % 10;
    int loop_digit = N % 4;
    return loop_result[last_digit][(loop_digit+4-1)%4];
}

int main()
{
    freopen("1004_last_digit_of_n_expo_n.txt", "r", stdin);
    scanf("%d", &N);

    int ans = solve();
    printf("%d\n", ans);

    return 0;
}
