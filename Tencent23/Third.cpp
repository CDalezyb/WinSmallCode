#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

void buildTree(const vector<int> &nums, const int n, TreeNode *&root)
{
    queue<TreeNode *> que;
    root = new TreeNode(nums[0]);
    que.push(root);
    int size = 1;
    int index = 1;
    while (!que.empty() && index < n)
    {
        auto node = que.front();
        que.pop();

        if (index < n && nums[index] != -1)
        {
            node->left = new TreeNode(nums[index]);
            que.push(node->left);
        }
        index++;

        if (index < n && nums[index] != -1)
        {
            node->right = new TreeNode(nums[index]);
            que.push(node->right);
        }
        index++;
    }
}

int Pcount = 0;
// int zeroCount = 0, oneCount = 0;
void Solve(TreeNode *root, int zeroCount, int oneCount)
{
    // if (root == nullptr)
    //     return;
    if (root->val == 0)
        zeroCount++;
    else
        oneCount++;

    if (root->left == nullptr && root->right == nullptr)
    {
        if (oneCount - zeroCount == 1)
            Pcount++;
        return;
    }

    if (root->left)
        Solve(root->left, zeroCount, oneCount);
    if (root->right)
        Solve(root->right, zeroCount, oneCount);

    return;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    if (nums.empty())
    {
        cout << 0 << endl;
        return 0;
    }

    TreeNode *root;
    buildTree(nums, n, root);

    Solve(root, 0, 0);
    cout << Pcount << endl;
    return 0;
}