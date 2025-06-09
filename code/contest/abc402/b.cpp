#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int q; cin >> q;

    queue<int> que;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            que.push(x);
        } else {
            cout << que.front() << '\n';
            que.pop();
        }
    }
}
