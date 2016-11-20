#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // init
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                dp[i][j] = matrix[i][j] - '0';
            }
        }
        // solve
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[i].size(); j++) {
                if (dp[i][j] == 1) {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                ans = max(ans, dp[i][j] * dp[i][j]);
            }
        }
        return ans;
    }
private:
    char dp[1000][1000];
};

int main()
{
    Solution s;
    vector<vector<char>> matrix = { 
        { '1', '0', '1', '0', '0' },
        { '1', '0', '1', '1', '1' },
        { '1', '1', '1', '1', '1' },
        { '1', '0', '0', '1', '0' }
    };
    int ans = s.maximalSquare(matrix);
    cout << ans << endl;
    return 0;
}