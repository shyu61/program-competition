#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        int h, w; cin >> h >> w;
        vector<string> mas(h);
        rep(i, h) cin >> mas[i];
        if (h > w) {
            swap(h, w);
            vector<string> tmp(h, string(w, '.'));
            rep(i, h) rep(j, w) tmp[i][j] = mas[j][i];
            swap(mas, tmp);
        }

        // 行方向に累積和を取る
        vector<vector<int>> s(h, vector<int>(w));
        rep(i, h) {
            rep(j, w) s[i][j] = (mas[i][j] == '#' ? 1 : -1);
            for (int j = 1; j < w; j++) s[i][j] += s[i][j - 1];
        }

        // 列方向は全探索
        ll ans = 0;
        vector<int> cnt(h * w * 2 + 1);
        rep(si, h) {
            vector<int> a(w + 1, h * w);
            for (int ti = si; ti < h; ti++) {
                rep(i, w) a[i + 1] += s[ti][i];
                rep(i, w + 1) {
                    ans += cnt[a[i]];
                    cnt[a[i]]++;
                }
                rep(i, w + 1) cnt[a[i]]--;
            }
        }
        cout << ans << '\n';
    }
}
