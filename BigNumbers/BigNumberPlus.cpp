#include <iostream>
#include <string>
using namespace std;

string BigNumberPlus(string num1, string num2);

int main()
{
    string num1 = "123456000000";
    string num2 = "98765";
    cin >> num1 >> num2;
    cout << BigNumberPlus(num1, num2) << endl;
    return 0;
}

string BigNumberPlus(string num1, string num2)
{
    // ensure num1 is longer
    if (num1.size() < num2.size())
        swap(num1, num2);

    int len1 = num1.size(), len2 = num2.size(), flag = 0, a, b, sum;
    while (len1 > 0)
    {
        a = num1[len1 - 1] - '0';

        if (len2 > 0)
            b = num2[len2 - 1] - '0';
        else
            b = 0;

        sum = a + b + flag;
        if (sum >= 10)
            flag = 1;
        else
            flag = 0;
        num1[len1 - 1] = '0' + sum % 10;

        len1--;
        len2--;
    }

    if (flag)
        num1 = "1" + num1;
    return num1;
}