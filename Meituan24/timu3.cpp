/*
美团25毕业秋招第三题，做题时间2024 8 10

有一根无限长度、颜色循环的彩带，彩带的颜色为N，对彩带进行 k次剪裁，求每次剪裁下来的彩带中颜色的个数

6 3（彩带长为6，进行3次剪裁）
1 2 3 4 1 4 （彩带颜色）
L 2 第一次剪裁：从左边开始，剪裁长度为2
L 3 第二次剪裁：从左边开始，剪裁长度为3
R 12 第三次剪裁：从右边开始，剪裁长度为12

印象中 N k 都是1e9
别的条件不记得了
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
using namespace std;
int main()
{
    int BanLength, cutTimes;
    cin >> BanLength >> cutTimes;
    vector<int> BanColor(BanLength);
    for (int i = 0; i < BanLength; i++)
        cin >> BanColor[i];

    vector<vector<int>> rec(BanLength, vector<int>(2 * BanLength, 1));
    for (int i = 0; i < BanLength - 1; i++)
    {
        for (int j = i + 1; j < 2 * BanLength; j++)
        {
            if (j - i >= BanLength)
            {
                rec[i][j] = rec[0][BanLength - 1];
                continue;
            }

            int colorNum = 0;
            set<int> ColorApps;
            for (int k = i; k <= j; k++)
            {
                if (ColorApps.find(BanColor[k % BanLength]) == ColorApps.end())
                {
                    colorNum++;
                    ColorApps.insert(BanColor[k % BanLength]);
                }
            }
            rec[i][j] = colorNum;
        }
    }
    // cout << "REC 0 1" << rec[0][1] << endl;
    char direc;
    int lengthCut;
    vector<pair<char, int>> everyCut(cutTimes);
    for (int i = 0; i < cutTimes; i++)
    {
        cin >> direc >> lengthCut;
        everyCut[i] = pair<char, int>(direc, lengthCut);
    }

    int left = 0, right = BanLength - 1;
    int start, end;
    for (int i = 0; i < cutTimes; i++)
    {
        if (everyCut[i].second >= BanLength)
        {
            cout << rec[0][BanLength - 1] << endl;
            continue;
        }

        if (everyCut[i].first == 'L')
        {
            start = left;
            end = left + everyCut[i].second - 1;
            // cout << "out:rec[" << start << "," << end << "]" << endl;
            cout << rec[start][end] << endl;

            left = (end + 1) % BanLength;
        }
        else
        {
            end = right;
            start = right - everyCut[i].second + 1;
            while (start < 0)
            {
                start += BanLength;
                end += BanLength;
            }
            // cout << "out:rec[" << start << "," << end << "]" << endl;
            cout << rec[start][end] << endl;

            right = start - 1;
            while (right < 0)
                right += BanLength;
        }
    }

    return 0;
}