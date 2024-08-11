#include <iostream>
#include <vector>
using namespace std;

/*

一个长为n的正整数数组，现随机从数组中删除一个数，求删除后数组奇数位和与偶数位和的绝对值的最小值
（这个题解没有验证过,事后做的题目)

*/

int main()
{
    int n;
    cin >> n;
    // n = 7;
    vector<int> nums(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    // vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7};

    // nums valid idx from 1 to n both close
    vector<int> preSumOdd(n + 2, 0), preSumEven(n + 2, 0);
    int evenStart = 0, oddStart = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 1) // odd number
        {
            if (i == 1)
                preSumOdd[i] = nums[i];
            else
                preSumOdd[i] = preSumOdd[i - 2] + nums[i];

            preSumEven[i] = preSumEven[i - 1];
        }
        else // even bumber
        {
            if (i == 2)
                preSumEven[i] = nums[i];
            else
                preSumEven[i] = preSumEven[i - 2] + nums[i];

            preSumOdd[i] = preSumOdd[i - 1];
        }
    }

    // cout << "odd pre sum" << endl;
    // for (auto odd : preSumOdd)
    //     cout << odd << " ";
    // cout << endl;
    // cout << "odd pre sum" << endl;
    // for (auto even : preSumEven)
    //     cout << even << " ";
    // cout << endl;

    int minAbsDiff = INT_MAX;
    int deleteIdx = -1;
    for (int delIdx = 1; delIdx <= n; delIdx++)
    {
        int frontOddSum = preSumOdd[delIdx - 1];
        int frontEvenSum = preSumEven[delIdx - 1];
        int backOddSum = preSumOdd[n] - preSumOdd[delIdx];
        int backEvenSum = preSumEven[n] - preSumEven[delIdx];

        // cout << "deleted element at idx: " << delIdx << " frontOddSum: " << frontOddSum << " frontEvenSum: " << frontEvenSum << " backOddSum: " << backOddSum << " backEvenSum:" << backEvenSum << endl;

        int sum1 = frontEvenSum + backOddSum;
        int sum2 = frontOddSum + backEvenSum;
        if (abs(sum1 - sum2) < minAbsDiff)
        {
            minAbsDiff = abs(sum1 - sum2);
            deleteIdx = delIdx;
        }
    }

    cout << " minAbsDiff: " << minAbsDiff << " deleteIdx: " << deleteIdx << endl;
    return 0;
}