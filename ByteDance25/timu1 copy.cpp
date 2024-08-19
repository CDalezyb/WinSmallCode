#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <deque>
using namespace std;

/*
给你一个数组，求满足以下条件的子数组：
长度至少为3，恰好出现两种数字，其中一个数字出现1次
*/

int FindABB(const vector<int> &nums)
{
    int count = 0;
    for (int i = 0; i + 2 <= nums.size() - 1; i++)
    {
        int A = nums[i];
        int B = nums[i + 1];
        if (B == A)
            continue;
        for (int j = i + 2; j <= nums.size() - 1; j++)
        {
            if (nums[j] == B)
                count++;
            else
                break;
        }
    }
    return count;
}

int FindBBA(const vector<int> &nums)
{
    int count = 0;

    for (int i = nums.size() - 1; i - 2 >= 0; i--)
    {
        int A = nums[i];
        int B = nums[i - 1];
        if (B == A)
            continue;
        for (int j = i - 2; j >= 0; j--)
        {
            if (nums[j] == B)
                count++;
            else
                break;
        }
    }

    return count;
}

int FindBAB(const vector<int> &nums)
{
    int count = 0;

    for (int i = 1; i + 1 <= nums.size() - 1; i++)
    {
        int A = nums[i];
        int B1 = nums[i - 1];
        int B2 = nums[i + 1];
        if (B1 != B2)
            continue;
        if (A == B1)
            continue;

        int left = 1, right = 1;
        int B = B1;

        for (int j = i - 2; j >= 0; j--)
        {
            if (nums[j] == B)
                left++;
            else
                break;
        }

        for (int j = i + 2; j <= nums.size() - 1; j++)
        {
            if (nums[j] == B)
                right++;
            else
                break;
        }

        count += left * right;
    }

    return count;
}

int main()
{
    int n;
    vector<int> nums;
    bool debug = true;
    // debug = false;
    if (debug)
    {
        n = 6;
        nums = {1, 1, 1, 4, 5, 4, 1, 1, 1, 4, 1, 1, 1};
    }
    else
    {
        cin >> n;
        nums.resize(n, 0);
        for (int i = 0; i < n; i++)
            cin >> nums[i];
    }

    int c1 = FindABB(nums);
    int c2 = FindBBA(nums);
    int c3 = FindBAB(nums);
    cout << c1 + c2 + c3 << endl;

    return 0;
}
// 64 位输出请用 printf("%lld")