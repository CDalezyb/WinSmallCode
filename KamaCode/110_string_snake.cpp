#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    string beginStr, endStr;
    int n;
    cin >> n;

    cin >> beginStr >> endStr;
    unordered_set<string> strSet;
    string str;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        strSet.insert(str);
    }

    unordered_map<string, int> visitMap; // 表征word是否出现 & 出现的时候 ，path长度

    queue<string> que;
    que.push(beginStr);
    visitMap.insert(pair<string, int>(beginStr, 1));

    while (!que.empty())
    {
        auto word = que.front();
        que.pop();
        int path = visitMap[word];

        for (int i = 0; i < word.size(); i++)
        {
            string newWord = word;
            for (int j = 0; j < 26; j++)
            {
                newWord[i] = 'a' + j;
                if (newWord == endStr)
                {
                    cout << path + 1 << endl;
                    return 0;
                }

                if (strSet.find(newWord) != strSet.end() && visitMap.count(newWord) == 0)
                {
                    visitMap.insert(pair<string, int>(newWord, path + 1));
                    que.push(newWord);
                }
            }
        }
    }

    cout << 0 << endl;
    return 0;
}