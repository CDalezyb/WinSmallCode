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

bool isSpecialArray(const unordered_map<int, int> Count)
{
    if (Count.size() != 2)
        return false;
    int one = 0, plusone = 0;
    bool error = false;
    for (auto it : Count)
    {
        if (it.second == 1)
            one++;
        else if (it.second > 1)
            plusone++;
        else
            return false;
    }

    if (one == 1 && plusone == 1)
        return true;

    return false;
}

int main()
{
    int n;
    // cin >> n;
    n = 4;
    vector<int> nums(n, 0);

    // for (int i = 0; i < n; i++)
    //     cin >> nums[i];

    nums = {2, 2, 3, 2};

    // int a, b, c;
    int ans = 0;
    unordered_map<int, int> Count;
    deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        dq.push_back(nums[i]);
        if (dq.size() < 3)
        {
            Count[nums[i]]++;
            continue;
        }

        // 添加一个已经存在的
        if (Count[nums[i]] > 0)
        {
            Count[nums[i]]++;
            if (isSpecialArray(Count))
                ans++;
            else
            {
                while (!(isSpecialArray(Count)))
                {
                    int e = dq.front();
                    Count[e]--;
                    dq.pop_front();
                    if (Count[e] == 0)
                        Count.erase(e);
                }
            }
        }
        else
        {
            Count[nums[i]]++;
            // add new number
            if (Count.size() > 2)
            {
                while (Count.size() > 2)
                {
                    int e = dq.front();
                    dq.pop_front();
                    Count[e]--;
                    if (Count[e] == 0)
                        Count.erase(e);
                }
            }

            if (isSpecialArray(Count))
            {
                ans++;
            }
        }
    }

    while (!dq.empty())
    {
        int e = dq.front();
        dq.pop_front();
        Count[e]--;
        if (Count[e] == 0)
            Count.erase(e);

        if (isSpecialArray(Count))
        {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
// 64 位输出请用 printf("%lld")