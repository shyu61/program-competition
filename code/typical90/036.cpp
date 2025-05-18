#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷抑えるべき抽象論は？
// マンハッタン距離の取り扱い
// - 45度回転&縮小によりx,yを区別なく扱える(1変数にできる)
//   - (x,y) -> (x-y,x+y)
//   - 45回転する理由: 等距離領域が軸平行になり、チェビシェフ距離として計算できる。それによりx,yを区別なく扱える
//   - 縮小する理由: 係数を無視してもマンハッタン距離は保存されるため(ユークリッド距離は変換する)

int main() {
    int n, q; cin >> n >> q;
    vector<P> a(n);
    rep(i, n) cin >> a[i].first >> a[i].second;

    // 45度回転
    rep(i, n) {
        a[i] = {a[i].first - a[i].second, a[i].first + a[i].second};
    }

    int maxx = 0, minx = 2e9, maxy = 0, miny = 2e9;
    for (auto [x, y] : a) {
        maxx = max(maxx, x);
        minx = min(minx, x);
        maxy = max(maxy, y);
        miny = min(miny, y);
    }

    while (q--) {
        int qi; cin >> qi; qi--;
        ll x = a[qi].first, y = a[qi].second;
        ll ans = max({abs(maxx - x), abs(minx - x), abs(maxy - y), abs(miny - y)});
        cout << ans << '\n';
    }
}
