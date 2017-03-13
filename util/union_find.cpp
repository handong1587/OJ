#include <stdio.h>

#define MAXN 10000

int parent[MAXN];
int rank[MAXN];

void init()
{
	for (int i = 0; i < MAXN; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
}

int find(int x)
{
	if (x == parent[x]) {
		return x;
	}
	else {
		return parent[x] = find(parent[x]);
	}
}

void unite(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) {
		return;
	}

	if (rank[x] < rank[y]) {
		parent[x] = y;
	}
	else {
		parent[y] = x;
		if (rank[x] == rank[y]) {
			rank[x]++;
		}
	}
}

bool same(int x, int y)
{
	return find(x) == find(y);
}

int main()
{
	return 0;
}