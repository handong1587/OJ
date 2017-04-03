/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// https://leetcode.com/problems/invert-binary-tree
// Accepted

class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
            if (root == NULL) {
                return NULL;
            }
            if (root->left != NULL) {
                invertTree(root->left);
            }
            if (root->right != NULL) {
                invertTree(root->right);
            }
            TreeNode* tmpNode = root->left;
            root->left = root->right;
            root->right = tmpNode;
            return root;
        }
};
