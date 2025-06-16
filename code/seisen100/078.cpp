#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// 二次元累積和: 長方形を使った領域の足し引きを考える。左上は含まないよう処理したいのでそのまま、右下は含みたいので+1する
// - s[x+1][y+1] = s[x+1][y] + s[x][y+1] - s[x][y] + a[x][y];
// - s[x2+1][y2+1] - s[x1][y2+1] - s[x2+1][y1] + s[x1][y1];

int main() {
    int h, w, q; cin >> h >> w >> q;
    vector<vector<vector<int>>> a(3, vector<vector<int>>(h, vector<int>(w)));
    rep(i, h) rep(j, w) {
        char c; cin >> c;
        if (c == 'J') a[0][i][j]++;
        if (c == 'O') a[1][i][j]++;
        if (c == 'I') a[2][i][j]++;
    }

    vector<vector<vector<int>>> s(3, vector<vector<int>>(h + 1, vector<int>(w + 1)));
    rep(r, 3) rep(i, h) rep(j, w) {
        s[r][i + 1][j + 1] = s[r][i + 1][j] + s[r][i][j + 1] - s[r][i][j] + a[r][i][j];
    }

    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--;
        rep(r, 3) {
            int ans = s[r][x2][y2] - s[r][x1][y2] - s[r][x2][y1] + s[r][x1][y1];
            cout << ans << (r < 2 ? ' ' : '\n');
        }
    }
}   
