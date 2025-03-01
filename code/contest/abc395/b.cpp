#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<vector<char>> mas(n, vector<char>(n));
    rep(i, n) {
        int j = n - i;
        if (i > j) continue;
        char c = (i % 2 == 0) ? '#' : '.';
        for (int k = i; k < j; k++) {
            for (int l = i; l < j; l++) {
                mas[k][l] = c;
            }
        }
    }

    rep(i, n) {
        rep(j, n) cout << mas[i][j];
        cout << '\n';
    }
}
