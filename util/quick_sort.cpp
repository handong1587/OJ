#include <stdio.h>

#define MAXN 10000

int A[MAXN];

inline void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(int a[], int n, int l, int r)
{
	int i = l - 1;
	int pivot = a[r];  // choose rightmost element as pivot
	for (int j = l; j < r; j++) {
		// meet an element <= pivot, we substitute it to the front, index by i
		if (a[j] <= pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

void quick_sort(int a[], int n, int l, int r)
{
	if (l < r) {
		int q = partition(a, n, l, r);
		quick_sort(a, n, l, q - 1);
		quick_sort(a, n, q + 1, r);
	}
}

int main()
{
	int a[10] = { 7,3,10,9,2,1,4,6,8,5 };
	quick_sort(a, 10, 0, 9);
	for (int i = 0; i < 10; i++) {
		printf("%d\n", a[i]);
	}
	return 0;
}