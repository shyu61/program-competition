#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int t; cin >> t;
    while (t--) {
        int h, w; cin >> h >> w;
        vector<string> mas(h);
        rep(i, h) cin >> mas[i];

        if (h > w) {
            vector<string> nmas(w);
            rep(i, h) rep(j, w) nmas[j][i] = mas[i][j];
            swap(h, w);
        }

        // 列方向に累積和をとっておく
        vector<vector<int>> s(w, vector<int>(h + 1));
        rep(i, w) {
            rep(j, h) {
                int c = mas[i][j] == '#' ? 1 : -1;
                s[i][j + 1] = s[i][j] + c;
            }
        }

        // hは全探索
        vector<int> s2(w + 1);
        rep(i, h) rep(j, h) {
            // hi = [i,j]について計算する
            s2[0] = 0;
            rep(k, w) {
                s2[k + 1] = s2[k] + (s[k][j + 1] - s[k][i]);
            }

        }
    }
}
