#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct FreCount
{
    int count;
    int number;
    // 元素 index 最小堆
    priority_queue<int, vector<int>, std::greater<int>> IdxQ;
};

bool mycom(const FreCount &l, const FreCount &r)
{
    // 出现次数降序 如果次数相同，则最先出现的在左边
    if (l.count == r.count)
    {
        return l.IdxQ.top() < r.IdxQ.top();
    }
    else
        return l.count > r.count;
}

int main()
{
    int minCount = 0, minCost = 0;
    int n, k, inNumber;
    cin >> n >> k;
    set<int> chuxianguo;
    vector<FreCount> vecStone;

    vector<int> vecNumber(n);
    for (int i = 0; i < n; i++)
        cin >> vecNumber[i];

    for (int i = 0; i < n; i++)
    {
        inNumber = vecNumber[i];
        if (chuxianguo.find(inNumber) != chuxianguo.end())
        {
            for (int j = 0; j < vecStone.size(); j++)
            {
                if (vecStone[j].number == inNumber)
                {
                    vecStone[j].count++;
                    vecStone[j].IdxQ.push(i);
                    break;
                }
            }
        }
        else
        {
            chuxianguo.insert(inNumber);
            FreCount temp;
            temp.count = 1;
            temp.IdxQ.push(i);
            temp.number = inNumber;
            vecStone.push_back(temp);
        }
    }

    sort(vecStone.begin(), vecStone.end(), mycom);
    minCount = vecStone[0].count;

    while (k > 0)
    {
        // count 数字出现次数从大到小
        // 数字出现的Idx从小到大
        bool f = false;
        // k delete chances but more than k sam frequency number
        if (vecStone.size() > k && vecStone[k].count == vecStone[0].count)
        {
            break;
        }

        // do the delete
        if (vecStone[0].count > 0)
        {
            const int toDeleteCount = vecStone[0].count;
            for (int i = 0; i < k; i++)
            {
                if (vecStone[i].count == toDeleteCount)
                {
                    vecStone[i].count--;
                    k--;
                    minCost += vecStone[i].IdxQ.top() + 1;
                    vecStone[i].IdxQ.pop();
                }
                else
                    break;
            }
        }
        else
        {
            // 所有元素都删除了
            break;
        }

        sort(vecStone.begin(), vecStone.end(), mycom);
        minCount = vecStone[0].count;
    }

    cout << minCount << " " << minCost << endl;

    return 0;
}