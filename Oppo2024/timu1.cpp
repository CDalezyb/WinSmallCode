#include <iostream>
using namespace std;

bool isprime(long long n) {
    if (n <= 1)
        return false;

    if (n == 2 || n == 3)
        return true;

    if (n % 6 != 1 && n % 6 != 5)
        return false;


    for (int i = 5; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }

    return true;

}

int main() {
    long long x;
    cin >> x;
    if (x == 1 || x == 2) {
        cout << 2 << endl;
        return 0;
    }

    if (x == 3) {
        cout << 3 << endl;
        return 0;
    }
    if (x == 4 || x == 5) {
        cout << 5 << endl;
        return 0;
    }

    long long n = x / 6 - 2;
    long long number1, number2;
    while (n) {
        number1 = 6 * n - 1;
        if (number1 >= x && isprime(number1)) {
            cout << number1 << endl;
            break;
        }

        number2 = 6 * n + 1;
        if (number2 >= x && isprime(number2)) {
            cout << number2 << endl;
            break;
        }

    }
}
// 64 位输出请用 printf("%lld")