#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, maze;
int map[405][405];
int perm[405];
int sum[405]; //sum up all 1 in each line
int cnt[405]; //sum up current number of 1 in each line at every dfs
int ans[405];
int used[405];

int isValidPerm(int col)
{
  for (int row = 0; row < n; row++) {
    // encounter first 0, check if it is a good permutation
    if (map[row][col] == 0) {
      // if no 1 encounter yet, it is okay: cnt[row] == 0
      // otherwise need to check if columns are well permuted
      if (cnt[row] > 0 && cnt[row] < sum[row]) { //the number of consecutive 1 isn't enough
        return 0;
      }
    }
  }
  // otherwise all rows are all well permuted 
  // or can still be permuted afterwards
  return 1;
}
int dfs(int prev_col)
{
  if (prev_col == maze) {
    return 1;
  }
  for (int col = 1; col < maze; col++) {
    // try permuting all non-used columns
    if (used[col] == 0 && isValidPerm(col)) {
      used[col] = 1;
      for (int row = 0; row < n; row++) {
        cnt[row] += map[row][col];
      }
      ans[prev_col] = col;
      if (dfs(prev_col + 1)) {
        return 1;
      }
      used[col] = 0;
      for (int row = 0; row < n; row++) {
        cnt[row] -= map[row][col];
      }
    }
  }
  return 0;
}

int main()
{
  freopen("POJ\\2790_Consecutive_ones.txt", "r", stdin);
  scanf("%d", &n);
  scanf("%d", &maze);
  for (int i = 0; i < n; i++) {
    char tmp[405];
    scanf("%s", tmp);
    for (int j = 0; j < maze; j++) {
      if (tmp[j] == '0') {
        map[i][j] = 0;
      }
      else {
        map[i][j] = 1;
      }
      sum[i] += map[i][j];
    }
  }
  ans[0] = 0;
  for (int i = 0; i < n; i++) {
    cnt[i] += map[i][0];
  }

  // start with second column
  dfs(1);

  for (int i = 0; i < maze; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}