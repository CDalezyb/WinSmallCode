#include <iostream>
#include <string>
using namespace std;

/*
    给一个字符串str(最长为1e5)和两个int类整数x和y；
    请把str拆成str1和str2，使得str1组成的数字能被x整除，str2组成的数字能被y整除，如果找到不，输出-1。
*/

bool canBeDevided(const string s, int startIdx, int endIdx, const int devider)
{
    int Yu = 0;
    int cur = startIdx;
    for (cur; cur <= endIdx; cur++)
    {
        Yu = Yu * 10 + int(s[cur] - '0');
        Yu %= devider;
    }

    if (Yu == 0)
        return true;
    else
        return false;
}

int main()
{

    // cout << canBeDevided("135", 0, 2, 5);
    // cout << canBeDevided("135", 0, 1, 5);

    string str;
    cin >> str;
    int x, y;
    cin >> x >> y;

    int xYu = 0, yYu = 0;
    int cur = 0; // [0,cur] [cur+1,lenght+1]

    bool find = false;

    for (cur; cur + 1 <= str.length() - 1; cur++)
    {
        xYu = xYu * 10 + (int)(str[cur] - '0');
        if (xYu < x)
            continue;
        else
        {
            if (xYu % x == 0)
            {
                if (canBeDevided(str, cur + 1, str.length() - 1, y))
                {
                    cout << str.substr(0, cur + 1) << " " << str.substr(cur + 1) << endl;
                    find = true;
                    break;
                }
            }
            else
            {
                xYu %= x;
            }
        }
    }

    if (!find)
        cout << -1 << endl;

    return 0;
}
// 64 位输出请用 printf("%lld")