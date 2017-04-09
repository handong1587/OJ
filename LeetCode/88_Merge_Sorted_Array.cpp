#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            const int INF = 0x7FFFFFFF;
            vector<int> tmp1;
            vector<int> tmp2;
            for (int i=0; i<m; i++) {
                tmp1.push_back(nums1[i]);
            }
            for (int i=0; i<n; i++) {
                tmp2.push_back(nums2[i]);
            }
            tmp1.push_back(INF);
            tmp2.push_back(INF);
            nums1.clear();
            int i1 = 0;
            int i2 = 0;
            for (int i=0; i<m+n; i++) {
                if (tmp1[i1] <= tmp2[i2]) {
                    nums1.push_back(tmp1[i1++]);
                }
                else {
                    nums1.push_back(tmp2[i2++]);
                }
            }
        }

        // for debug
        void output(vector<int>& nums1, int m) {
            for (int i=0; i<m; i++) {
                printf("%d\n", nums1[i]);
            }
        }
};

int main()
{
    // case 1
    /*
    int a1[] = {0,2,4,6};
    int a2[] = {1,3,5,7,9};
    vector<int> nums1(1000);
    for (int i=0;i<4;i++){
        nums1[i]=a1[i];
    }
    vector<int> nums2(a2, a2+5);
    Solution s;
    s.merge(nums1, 4, nums2, 5);
    s.output(nums1, 9);
    */

    // case 2
    int a1[] = {1};
    vector<int> nums1(1000);
    for (int i=0;i<4;i++){
        nums1[i]=a1[i];
    }
    vector<int> nums2;
    Solution s;
    s.merge(nums1, 1, nums2, 0);


    s.output(nums1, 1);

    return 0;
}
