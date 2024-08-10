#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(string s1, string s2) {
    return s1.size() < s2.size();
}

int main() {
    int n;
    cin >> n;
    string RealPwd;
    string FakePwd;
    cin >> RealPwd;
    set<string> sString;
    for (int i = 0; i < n; i++) {
        cin >> FakePwd;
        if (sString.find(FakePwd) == sString.end()) {
            sString.insert(FakePwd);
        }
    }

    vector<string> vecString;
    vecString.assign(sString.begin(), sString.end());
    sort(vecString.begin(), vecString.end(), cmp);

    const int RealLength = RealPwd.size();
    int equal = 0, less = 0;
    for (int i = 0; i < vecString.size(); i++) {
        FakePwd = vecString[i];
        if (FakePwd.size() == RealLength) {
            equal++;
        } else if (FakePwd.size() < RealLength) {
            less++;
        }
    }

    cout << less + 1 << " " << equal + less << endl;
}
// 64 位输出请用 printf("%lld")