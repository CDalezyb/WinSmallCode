#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int findTargetSumWays(vector<int> &nums, int target)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > sum)
        return 0;
    if ((sum + target) % 2 == 1)
        return 0;

    const int BagSize = (target + sum) / 2;
    vector<int> dp(BagSize + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = BagSize; j >= nums[i]; j--)
        {
            int a = dp[j];
            int b = dp[j - nums[i]] + nums[i];
            dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
        }
    }

    return dp[BagSize];
}

int main()
{
    vector<int> array{1, 1, 1, 1, 1};
    int target = 3;
    findTargetSumWays(array, target);

    return 0;
}