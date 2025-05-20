#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 最小の最大化なのでまずは二分探索で考える
// 二分探索を考える時はsortして単調性を導入するのが基本
// minはall的考え方ができるので、Δx,Δyともにmid以上になる点を探索すれば良い。
// check関数はO(nlogn)までかけられるので、xは線形スキャンして、y部分は尺取りでうまくやれば良い
// この時、yについて欲しい情報はminy,maxyなので、増やす方向に尺取りした方が良い。
// 故にxの線形スキャンの左側について尺取りする

// 🔷抑えるべき抽象論は？
// 尺取り法は、posに対して左右どちらを使うかを一度考えると良い
// - ある値より大きい方を見るか小さい方を見るか
// - キャンセルする方向はmin/maxの計算にsetが必要。追加する方向はデータ構造不要
// min: all, max: at least

int main() {
    int n; cin >> n;
    vector<P> a(n);
    rep(i, n) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());

    // |xi-xj| >= mid && |yi-yj| >= mid となる(i,j)が存在するか
    auto check = [&](int mid) -> bool {
        int pos = 0;
        int miny = INF, maxy = -INF;
        rep(i, n) {
            auto [x, y] = a[i];
            while (pos < i && (x - a[pos].first) >= mid) {
                miny = min(miny, a[pos].second);
                maxy = max(maxy, a[pos].second);
                pos++;
            }
            if (y - miny >= mid || maxy - y >= mid) return true;
        }
        return false;
    };

    int ok = 0, ng = 1e9 + 1;
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }

    cout << ok << endl;
}
