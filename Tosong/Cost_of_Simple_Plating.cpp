#include <stdio.h>
#include <math.h>

// case: 100/100

int T, S, N;
struct Location
{
    int row;
    int column;
};
Location loc[10005];
int resN;
struct PlateSolution
{
    Location loc;
    int cover;
};
PlateSolution ps[10005];
char plate[105][105];
int curCost, minCost;

int cost(int cover)
{
    return (int)floor((double)(cover*cover / 2 + cover * 2 / 3 + 1)); //correct
    //return floor((double)(cover*cover / 2 + cover * 2 / 3 + 3));
}

void init_plate()
{
    for (int i = 1; i < 105;i++)
    {
        for (int j = 1; j < 105;j++)
        {
            plate[i][j] = '.';
        }
    }
    for (int i = 0; i < N;i++)
    {
        plate[loc[i].row][loc[i].column] = 'A';
    }
}

void plot_plate()
{
    for (int i = 1; i <= S; i++)
    {
        for (int j = 1; j <= S; j++)
        {
            printf("%c%s", plate[i][j],j==S?"\n":"");
        }
    }
}

void initCost()
{
    curCost = N*cost(1);
    resN = N;
    for (int i = 0; i < resN;i++)
    {
        ps[i].loc.row = loc[i].row;
        ps[i].loc.column = loc[i].column;
        ps[i].cover = 1;
    }
}

void updateCost()
{

}

void naive_solve()
{
    initCost();

}

int main()
{
    freopen("Cost_of_Simple_Plating.txt", "r", stdin);
    scanf("%d\n", &T);
    for (int t = 1; t <= T; t++)
    {
        scanf("%d\n", &S);
        scanf("%d\n", &N);
        for (int i = 0; i < N; i++)
        {
            scanf("%d%d", &loc[i].row, &loc[i].column);
        }

        init_plate();
        //plot_plate();

        naive_solve();

        printf("#%d %d ", t,resN);
        for (int i = 0; i < resN;i++)
        {
            printf("%d %d %d%s", ps[i].loc.row, ps[i].loc.column, ps[i].cover, i == resN - 1 ? "\n" : " ");
        }
    }

    return 0;
}
