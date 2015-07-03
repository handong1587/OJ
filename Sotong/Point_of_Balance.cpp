// case: 100/100

#include <stdio.h>

#define MAX_N 15
//#define ERR (1e-9)
#define ERR (1e-12)
#define _abs_(a) ((a)>0.0?(a):-(a))

enum ForceType
{
	LEFT_FORCE,RIGHT_FORCE
};

int T,N;
int coor[MAX_N], mass[MAX_N];

double left_pos;
double right_pos;
double pos;
bool balanced;
double left_force, right_force;
double res[MAX_N];

double force(int m,double d)
{
	return (double)m / (double)(d*d);
}

double calc_force(double pos,ForceType force_type)
{
	double sum=0.0;
	if (force_type==LEFT_FORCE)
	{
		for (int i = 0; i < N; i++)
		{
			if (coor[i]>pos)
				break;
			sum += force(mass[i], pos - coor[i]);
		}
	}	
	else if (force_type==RIGHT_FORCE)
	{
		for (int i = N-1; i >=0; i--)
		{
			if (coor[i] < pos)
				break;
			sum += force(mass[i], coor[i] - pos);
		}
	}
	return sum;
}

void solve()
{
	for (int i = 0; i < N-1;i++)
	{
		left_pos = (double)coor[i];
		right_pos = (double)coor[i+1];

		balanced = false;
		pos = (double)(left_pos + right_pos) / 2;

		double last_pos = pos;

		while (!balanced)
		{
			left_force = calc_force(pos, LEFT_FORCE);
			right_force = calc_force(pos, RIGHT_FORCE);

			if (left_force>right_force)
			{
				left_pos = pos;
				pos = (pos + right_pos) / 2;
			}
			else if (left_force<right_force)
			{
				right_pos = pos;
				pos = (left_pos + pos) / 2;
			}

			if (_abs_(pos - last_pos) <= ERR&&_abs_(pos - last_pos) >= -ERR)
			{
				balanced = true;
			}
			last_pos = pos;
		}
		res[i] = pos;
	}
}

int main()
{
	freopen("Point_of_Balance.txt", "r", stdin);
	scanf("%d\n", &T);
	for (int t = 0; t < T;t++)
	{
		scanf("%d\n", &N);
		for (int i = 0; i < N;i++)
		{
			scanf("%d", &coor[i]);
		}
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &mass[i]);
		}
		solve();
		printf("#%d ", t + 1);
		for (int i = 0; i < N - 1;i++)
		{
			printf("%.10f%s", res[i], (i == N - 2 ? "\n" : " "));
		}
	}

	return 0;
}