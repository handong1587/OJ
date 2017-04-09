/**
 * Definition for singly-linked list.
 * struct ListNode {
 *    int val;
 *    ListNode *next;
 *    ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* retLN = new ListNode(0); // you need to new a pointer first so headLN can have a non-NULL pointer to capture
        ListNode* headLN = retLN;

        const int INF = 0x7FFFFFFF;

        int loop_cnt = 0;
        while (1) {
            int null_cnt = 0;
            int min_val = INF;
            int minLNIdx = -1;
            ListNode* minLN = NULL;
            for (int i=0; i<lists.size(); i++) {
                ListNode* head = lists[i];
                if (head == NULL) {
                    null_cnt++;
                    continue;
                }
                if (head->val < min_val) {
                    min_val = head->val;
                    minLNIdx = i;
                    minLN = head;
                }
            }
            if (null_cnt == lists.size()) {
                break;
            }

            ListNode* tmpLN = new ListNode(min_val);
            retLN->next = tmpLN;
            retLN = retLN->next;
            lists[minLNIdx] = minLN->next;
        }

        // the very first pointer keep a dummy value
        return headLN->next;
    }
};
