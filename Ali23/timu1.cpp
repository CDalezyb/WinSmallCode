#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int i = 0;
    string str;
    cin >> str;
    for (int i = 0; i < n - 1; i++)
    {
        if (str[i] == '1' && str[i + 1] == '0')
        {
            swap(str[i], str[i + 1]);
            k--;
            i -= 2;
            if (k == 0)
            {
                cout << str;
                return 0;
            }
            if (i < -1)
            {
                i = -1;
            }
        }
    }
    cout << str << endl;
    return 0;
}