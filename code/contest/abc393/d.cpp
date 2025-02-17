#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 数列, バブルソート, 交換数, 配置問題

// 方針
// 距離(絶対値)の総和の最小化は中央値を基準に考えれば良い
// つまり、各1から中央の位置までの距離が分かればよい
// 凝集する時offsetの考慮が面倒なので、前処理で引いておけば1の幅を無視でき、単に中央値との距離を計算するだけで良くなる
// 1について位置配列を計算し、offsetを引く前処理をした上で中央値との距離の総和を取れば良い

// ポイント
// Σ|p[i]-t|を最小にするtは中央値であることは有名事実。数列の各要素に対しての絶対値の総和を最小にする要素は中央値になる
// 位置オフセットの調整
// -> ある種の要素の大きさを無視したい時、オフセットを引くことで大きさをなくし、凝集する際に1点凝集と捉えることができる
//   - 連続性が要求される配置問題
//   - 隣接交換を行う問題

int main() {
    int n; string s; cin >> n >> s;
    vector<int> p;
    rep(i, n) if (s[i] == '1') p.push_back(i);
    int k = p.size();
    rep(i, k) p[i] -= i;
    int med = p[k / 2];

    ll ans = 0;
    rep(i, k) ans += abs(med - p[i]);
    cout << ans << endl;
}

int main() {
    int n; string s; cin >> n >> s;
    vector<int> zeros(n + 1);
    rep(i, n) {
        zeros[i + 1] += zeros[i] + !(s[i] - '0');
    }

    int mid = (n - zeros[n]) / 2 + 1;
    rep(i, n) {
        if (s[i] == '1') mid--;
        if (mid == 0) {
            mid = i;
            break;
        }
    }

    ll ans = 0;
    rep(i, n) {
        if (s[i] == '0') continue;
        ans += abs(zeros[mid] - zeros[i]);
    }
    cout << ans << endl;
}

// 尺取り的解法
int main() {
    int n; string s; cin >> n >> s;
    vector<int> ones(n + 1);
    ll cost = 0, zero = 0;
    rep(i, n) {
        ones[i + 1] += ones[i] + (s[i] - '0');
        if (s[i] == '1') cost += zero;
        else zero++;
    }

    ll ans = numeric_limits<ll>::max();
    rep(i, n) {
        if (s[i] == '0') cost += ones[i] - (ones[n] - ones[i + 1]);
        ans = min(ans, cost);
    }
    cout << ans << endl;
}
