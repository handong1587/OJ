#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int T,N;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int t=0;
        for(int i=0; i<nums.size(); i++){
            t ^= nums[i];
            t ^= i;
        }
        t ^= nums.size();
        return t;
    }
};

int main()
{
    freopen("268_Missing_Number.txt", "r", stdin);
    scanf("%d", &T);
    for(int t=0; t<T; t++){
        Solution S;
        vector<int> vec;
        scanf("%d", &N);
        for(int i=0; i<N; i++){
            int v;
            scanf("%d", &v);
            vec.push_back(v);
        }
        printf("%d\n", S.missingNumber(vec));
    }
    return 0;
}
