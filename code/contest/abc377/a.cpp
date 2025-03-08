#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    vector<int> cnt(3);
    rep(i, 3) {
        if (s[i] == 'A') cnt[0]++;
        if (s[i] == 'B') cnt[1]++;
        if (s[i] == 'C') cnt[2]++;
    }

    if (cnt[0] == 1 && cnt[1] == 1 && cnt[2] == 1) cout << "Yes" << endl;
    else cout << "No" << endl;
}
