#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))
#define MAXN 999999
#define INF (1<<29)
int dp[MAXN];

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        for (int i = 0; i < MAXN; i++) {
            dp[i] = INF;
        }
        for (int i = 0; i*coins[0] <= amount; i++) {
            dp[i*coins[0]] = i;
        }
        for (int i = 1; i < coins.size(); i++) {
            for (int j = 0; j + coins[i] <= amount; j++) {
                dp[j + coins[i]] = min(dp[j + coins[i]], dp[j] + 1);
            }
        }
        return dp[amount] == INF ? -1 : dp[amount];
    }
};

int main()
{
    Solution s;
    vector<int> coins1 = { 1,2,5 };
    int amount = 11;
    int res = s.coinChange(coins1, amount);
    cout << res << endl;

    vector<int> coins2 = { 2 };
    amount = 3;
    res = s.coinChange(coins2, amount);
    cout << res << endl;

    vector<int> coins3 = { 2,5,10,1 };
    amount = 27;
    res = s.coinChange(coins3, amount);
    cout << res << endl;

    vector<int> coins4 = { 186,419,83,408 };
    amount = 6249;
    res = s.coinChange(coins4, amount);
    cout << res << endl;
    return 0;
}