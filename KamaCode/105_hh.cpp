#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

int main()
{
    int n, k;
    int n1, n2;
    cin >> n >> k;
    vector<vector<int>> Edges(n + 1);
    while (k--)
    {
        cin >> n1 >> n2;
        Edges[n1].push_back(n2);
    }

    vector<bool> bReach(n + 1, false);
    bReach[0] = bReach[1] = true;

    queue<int> que;
    que.push(1);
    while (!que.empty())
    {
        int n1 = que.front();
        que.pop();

        for (auto n2 : Edges[n1])
        {
            if (bReach[n2] == false)
            {
                que.push(n2);
                bReach[n2] = true;
            }
        }
    }

    bool allReach = true;
    for (int i = 0; i < bReach.size(); i++)
    {
        if (bReach[i] == false)
            allReach = false;
    }

    if (allReach)
        cout << 1;
    else
        cout << -1;

    return 0;
}