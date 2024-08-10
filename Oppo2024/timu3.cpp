#include <iostream>
#include <string>
using namespace std;

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