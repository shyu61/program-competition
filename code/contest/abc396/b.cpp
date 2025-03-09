#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int q; cin >> q;
    vector<int> a(100);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int x; cin >> x;
            a.push_back(x);
        } else {
            cout << a.back() << '\n';
            a.pop_back();
        }
    }
}
