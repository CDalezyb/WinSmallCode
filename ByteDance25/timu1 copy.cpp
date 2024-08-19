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
    cin >> n;
    // n = 6;
    vector<int> nums(n, 0);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    // nums = {1, 1, 4, 5, 1, 4};

    // int a, b, c;
    int ans = 0;

    deque<int> dq;
    vector<vector<bool>> rec(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 2; j < n; j++)
        {
            if (j > i + 2 && rec[i][j - 1] == false)
                break;
            unordered_map<int, int> Count;

            for (int k = i; k <= j; k++)
            {
                Count[nums[k]]++;
            }

            if (isSpecialArray(Count))
            {
                rec[i][j] = true;
                ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
// 64 位输出请用 printf("%lld")