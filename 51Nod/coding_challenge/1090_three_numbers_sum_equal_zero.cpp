#include <stdio.h>
#include <algorithm>

using namespace std;

int N;
int A[1005];

bool cmp(int a, int b)
{
	return a < b;
}

bool findTargetNum(int targetNum, int start, int end)
{
	int l = start;
	int r = end;
	if (l == r)
	{
		return A[l] == targetNum;
	}
	if (r - l == 1)
	{
		return (A[l] == targetNum || A[r] == targetNum);
	}
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		if (A[mid] == targetNum)
		{
			return true;
		}
		else if (A[mid] > targetNum)
		{
			r = mid;
		}
		else
		{
			l = mid;
		}
	}
	if (r - l == 1)
	{
		return (A[l] == targetNum || A[r] == targetNum);
	}
	return false;
}

void solve()
{
	sort(A, A + N, cmp);
	int ansNum = 0;
	int start = 0;
	int end = N - 1;
	for (int start = 0; start < N - 2; start++)
	{
		for (int end = N - 1; end >= start + 2; end--)
		{
			int targetNum = -(A[start] + A[end]);
			bool findAns = findTargetNum(targetNum, start + 1, end - 1);
			if (findAns)
			{
				ansNum++;
				printf("%d %d %d\n", A[start], targetNum, A[end]);
			}
		}
	}
	if (ansNum == 0)
	{
		printf("No Solution\n");
	}
}

int main()
{
	freopen("51Nod/coding_challenge/1090_three_numbers_sum_equal_zero.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &A[i]);
	}
	solve();
	return 0;
}