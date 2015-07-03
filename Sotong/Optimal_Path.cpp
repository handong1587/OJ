// case: 100/100

#include <stdio.h>

#define _abs_(a) ((a)>0?(a):(-(a)))
#define _min_(a,b) ((a)<(b)?(a):(b))
#define MAX_N 15
int T,N;
struct Coord
{
	int x;
	int y;
};
Coord co[MAX_N];
int dist[MAX_N][MAX_N];
bool vis[MAX_N];
int cur_dist, min_dist;
int nVisitedCustomer;

void comp_dist()
{
	for (int i = 0; i < N;i++)
	{
		for (int j = i+1; j < N;j++)
		{
			if (i==j)
			{
				continue;
			}
			dist[i][j] = dist[j][i] = _abs_(co[i].x - co[j].x) + _abs_(co[i].y - co[j].y);
		}
	}
}

void init()
{
	for (int i = 0; i < MAX_N;i++)
	{
		vis[i] = false;
	}
	cur_dist = 0;
	min_dist = 0x3f3f3f3f;
	nVisitedCustomer = 0;
}

void dfs(int cur_costomer,int next_customer)
{
	
	if (cur_dist>min_dist)
	{
		return;
	}
	if (nVisitedCustomer==N-2)
	{
		cur_dist += dist[next_customer][1];

		min_dist = _min_(min_dist, cur_dist);

// 		for (int j = 0; j < nVisitedCustomer+1; j++)
// 		{
// 			printf(" ");
// 		}
// 		printf("return home: %d->%d, current dist: %d, current total dist: %d\n", next_customer, 1, dist[next_customer][1],cur_dist);

		cur_dist -= dist[next_customer][1];
		return;
	}
	for (int i = 2; i < N;i++)
	{
		if (vis[i]==false)
		{
			vis[i] = true;
			cur_dist += dist[next_customer][i];
			nVisitedCustomer++;

// 			for (int j = 0; j < nVisitedCustomer;j++)
// 			{
// 				printf(" ");
// 			}
// 			printf("%d contomers: %d->%d, current dist: %d, current total dist: %d\n", nVisitedCustomer, next_customer, i, dist[next_customer][i],cur_dist);

			dfs(next_customer, i);

			vis[i] = false;
			cur_dist -= dist[next_customer][i];
			nVisitedCustomer--;
		}
	}
}

void solve()
{
	for (int i = 2; i < N;i++)
	{
		nVisitedCustomer = 0;
		cur_dist = 0;

		vis[i] = true;
		cur_dist += dist[0][i];
		nVisitedCustomer++;

		//printf("%d contomers: %d->%d, current dist: %d, current total dist: %d\n", nVisitedCustomer, 0, i, dist[0][i],cur_dist);

		dfs(0, i);

		vis[i] = false;
		cur_dist -= dist[0][i];
		nVisitedCustomer--;
	}
}

int main()
{
	freopen("Optimal_Path.txt", "r", stdin);
	scanf("%d\n", &T);
	for (int t = 0; t < T;t++)
	{
		scanf("%d\n", &N);
		N += 2;
		for (int i = 0; i < N;i++)
		{
			scanf("%d%d", &co[i].x, &co[i].y);
		}
		init();
		comp_dist();
		solve();
		printf("#%d %d\n", t + 1,min_dist);		
	}
	return 0;
}