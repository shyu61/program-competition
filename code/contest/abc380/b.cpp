#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    vector<int> a;
    int prv = 0;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '-') continue;
        a.push_back(i - prv - 1);
        prv = i;
    }

    for (auto ai : a) cout << ai << ' ';
}
