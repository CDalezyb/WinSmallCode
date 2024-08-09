#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <cmath>
using namespace std;
/*
牛牛有一棵二叉树，该二叉树节点的权值为 0 或者 1。

牛牛给你这棵二叉树, 想让你告诉他该二叉树从根节点到叶子节点的所有路径中, 节点"权值 1 的个数"比权值 0 的个数"多 1 的路径有多少条。
*/

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

void dfs(TreeNode *root, int count0, int count1, int &ans)
{
    if (root == nullptr)
        return;

    root->val == 1 ? count1++ : count0++;

    if (root->left == nullptr && root->right == nullptr)
    {
        if (count1 - count0 == 1)
        {
            ans++;
        }
        return;
    }

    dfs(root->left, count0, count1, ans);
    dfs(root->right, count0, count1, ans);
}

int main()
{
    int N;
    cin >> N;
    vector<int> nums(N, 0);
    for (int i = 0; i < N; i++)
        cin >> nums[i];

    // N = 7;
    // vector<int> nums{1, 0, 0, 1, 0, -1, 1, -1, -1, 1, 0, -1, -1};
    // vector<int> nums{1, 0, 0, 1, 0, -1, 1};

    if (nums.empty())
        return 0;

    queue<TreeNode *> que;
    TreeNode *root = new TreeNode(nums[0]);
    que.push(root);
    int idx = 1;
    while (!que.empty() && idx < N)
    {
        TreeNode *node = que.front();
        que.pop();

        if (idx < N && nums[idx] != -1)
        {
            node->left = new TreeNode(nums[idx]);
            que.push(node->left);
        }
        idx++;

        if (idx < N && nums[idx] != -1)
        {
            node->right = new TreeNode(nums[idx]);
            que.push(node->right);
        }
        idx++;
    }

    int ans = 0;

    dfs(root, 0, 0, ans);

    cout << ans << endl;

    return 0;
}
