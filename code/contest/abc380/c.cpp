#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    string s; cin >> s;

    int cnt = 0, num = 0;
    vector<char> ans;

    char prv = '#';
    for (int i = 0; i < n; i++) {
        if (prv != s[i] && s[i] == '1') cnt++;
        if (cnt == k - 1 && s[i] == '0') num++;
        else ans.push_back(s[i]);

        if (cnt == k && s[i] == '0' && num > 0) {
            for (int j = 0; j < num; j++) ans.push_back('0');
            num = 0;
        }
        prv = s[i];
    }
    if (num > 0) {
        for (int i = 0; i < num; i++) ans.push_back('0');
    }

    for (auto c : ans) cout << c;
    cout << endl;
}
