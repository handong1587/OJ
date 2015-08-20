#include <stdio.h>
#include <math.h>

int T, S, N;
struct Location
{
    int row;
    int column;
}loc[10005];

double cost(int cover)
{
    return floor((double)(cover*cover / 2 + cover * 2 / 3 + 1)); //correct
    //return floor((double)(cover*cover / 2 + cover * 2 / 3 + 3));
}

int main()
{
    freopen("Cost_of_Plating.txt", "r", stdin);
    scanf("%d\n", &T);
    for (int t = 1; t <= T; t++){
        scanf("%d\n", &S);
        scanf("%d\n", &N);
        for (int i = 0; i < N;i++){
            scanf("%d%d", &loc[i].row, &loc[i].column);
        }
        printf("%#d\n", t);
    }

    return 0;
}
