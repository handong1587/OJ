#include <stdio.h>

typedef long long ll;
int N, A[50005], Q;
ll intg[50005];

void init()
{
	intg[0] = A[0];
	for (int i = 1; i <= N; i++)
	{
		intg[i] = intg[i - 1] + A[i];
	}
}

int main()
{
	freopen("51nod/coding_challenge/1081_sub_segment_sum.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &A[i]);
	}
	init();
	scanf("%d", &Q);
	for (int q = 0; q < Q; q++)
	{
		int S, L;
		scanf("%d %d", &S, &L);
		S--;
		ll ans = intg[S + L] - intg[S];
		printf("%lld\n", ans);
	}

	return 0;
}