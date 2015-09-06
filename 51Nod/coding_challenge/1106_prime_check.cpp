#include <stdio.h>

int N;
int S[1005];

bool is_prime(int n)
{
	for (int i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return n != 1;
}

int main()
{
	freopen("51Nod/coding_challenge/1106_prime_check.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &S[i]);
		bool isPrime = is_prime(S[i]);
		printf("%s\n", isPrime == true ? "YES" : "NO");
	}
	return 0;
}