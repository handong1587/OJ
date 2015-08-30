#include <stdio.h>
#include <algorithm>
#include <climits>
using namespace std;

// implement a Range Maximum Query, Not Range Minimum Query
// case 1-11: pass, case 12-20: Runtime Error

#define MAXN 10005
int N, S[MAXN], Q;

// RMQ
int size;
int dat[MAXN * 2 - 1];

void init(int size_)
{
	size = 1;
	while (size < size_){
		size *= 2;
	}
	for (int i = 0; i<2 * size - 1; i++){
		//dat[i] = INT_MAX;
		dat[i] = -INT_MAX;
	}
}
void update(int rmq_id, int rmq_v)
{
	rmq_id += size - 1;   // locate corresponding leaf node
	dat[rmq_id] = rmq_v;  // update value
	while (rmq_id > 0){   // update value bottom-to-top
		rmq_id = (rmq_id - 1) / 2;
		//dat[rmq_id] = min(dat[rmq_id * 2 + 1], dat[rmq_id * 2 + 2]);
		dat[rmq_id] = max(dat[rmq_id * 2 + 1], dat[rmq_id * 2 + 2]);
	}
}
// [a, b)
// [l, r)
int query(int a, int b, int rmq_id, int l, int r)
{
	if (r <= a || b <= l){
		//return INT_MAX;
		return -INT_MAX;
	}
	if (a <= l && r <= b){
		return dat[rmq_id];
	}
	else{
		int vl = query(a, b, rmq_id * 2 + 1, l, (l + r) / 2);
		int vr = query(a, b, rmq_id * 2 + 2, (l + r) / 2, r);
		//return min(vl, vr);
		return max(vl, vr);
	}
}
void construct_rmq(int *lcp, int size_)
{
	init(size_);
	for (int i = 0; i < size_; i++){
		update(i, lcp[i]);
	}
}
int query_rmq(int a, int b)
{
	return query(a, b, 0, 0, size);
}
// end of RMQ

int main()
{
	freopen("51Nod/coding_challenge/1174_rmq.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &S[i]);
	}
	scanf("%d", &Q);

	construct_rmq(S, N);

	for (int q = 0; q < Q; q++)
	{
		int i, j;
		scanf("%d %d", &i, &j);
		int ans = query_rmq(i, j+1);
		printf("%d\n", ans);
	}

	return 0;
}