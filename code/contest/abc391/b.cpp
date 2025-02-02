#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<string> s(n), t(m);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < m; i++) cin >> t[i];

    for (int i = 0; i < n - m + 1; i++) {
        for (int j = 0; j < n - m + 1; j++) {
            bool ok = true;
            for (int k = 0; k < m; k++) {
                for (int l = 0; l < m; l++) {
                    if (s[i][j] != t[k][l]) ok = false;
                }
            }
            if (ok) {
                cout << i + 1 << ' ' << j + 1 << endl;
                return 0;
            }
        }
    }
}
