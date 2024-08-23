#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
using namespace std;

long long calculate(vector<int> TarIdx, vector<int> CurIdx)
{
    long long ans = 0;
    assert(TarIdx.size() == CurIdx.size());

    for (int i = 0; i < TarIdx.size(); i++)
    {
        ans += abs(TarIdx[i] - CurIdx[i]);
    }

    return ans;
}

void solve(const string &str)
{

    const int len = str.size();
    vector<int> count(2, 0);
    long long idx_sum = 0;
    vector<int> targetIdx((len + 1) / 2, 0);
    for (int i = 0; i < targetIdx.size(); i++)
        targetIdx[i] = 2 * i;
    vector<int> zero_Idx, one_Idx;
    zero_Idx.reserve((len + 1) / 2);
    one_Idx.reserve((len + 1) / 2);
    long long idx_0 = 0, idx_1 = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '0')
        {
            count[0]++;
            zero_Idx.push_back(i);
        }
        else
        {
            count[1]++;
            one_Idx.push_back(i);
        }
    }

    long long ans = 0;

    if (count[0] == count[1])
    {
        auto N1 = calculate(targetIdx, zero_Idx);
        auto N2 = calculate(targetIdx, one_Idx);

        ans = min(N1, N2);
    }
    else
    {
        if (count[0] > count[1])
            ans = calculate(targetIdx, zero_Idx);
        else
            ans = calculate(targetIdx, one_Idx);
    }
    cout << ans << endl;

    // cout << "------------------------------" << endl;
}

int main()
{
    string str;

    // while (cin >> str)
    // {
    cin >> str;
    solve(str);
    // }
    return 0;
}