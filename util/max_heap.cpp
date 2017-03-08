#include <stdio.h>

#define MAXN 10000

int H;             // heap size
int a[MAXN + 1];   // heap array

void max_heapify(int i)
{
	int largest_node = i;
	int left_node = 2 * i + 1;
	int right_node = 2 * i + 2;

	if (left_node <= H && a[left_node] > a[i]) {
		largest_node = left_node;
	}
// 	else {
// 		largest_node = i;
// 	}
	if (right_node <= H && a[right_node] > a[largest_node]) {
		largest_node = right_node;
	}

	// swap current node to largest node
	if (largest_node != i) {
		int largest = a[largest_node];
		a[largest_node] = a[i];
		a[i] = largest;

		max_heapify(largest_node);
	}
}

void build_max_heap()
{
	for (int i = H / 2 - 1; i >= 0; i--) {
		max_heapify(i);
	}
}

int main()
{
	H = 10;
	int test[10] = { 8, 5, 1, 10, 6, 4, 7, 9, 3, 2 };
	for (int i = 0; i < 10; i++) {
		a[i] = test[i];
	}
	build_max_heap();
	for (int i = 0; i < 10; i++) {
		printf("%d\n", a[i]);
	}

	return 0;
}