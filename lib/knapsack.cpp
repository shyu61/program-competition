#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_G&lang=ja
// 個数制限付きナップサック
// ダブリングを使う方法: O(nWlogm)
// ダブリングは組合せ最適化(塊で扱う)や逐次問題(一気に進める)で利用シーンがある
// ただし組み合わせ最適化においては各要素が独立に選択可能であることが条件
int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n), m(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i] >> m[i];

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int k = 1; sum <= m[i]; k <<= 1) {
            int mul = min(m[i] - sum, k);
            vector<int> old(W + 1);
            swap(dp, old);
            for (int j = 0; j <= W; j++) {
                if (j - w[i] * mul >= 0) dp[j] = max(old[j], old[j - w[i] * mul] + v[i] * mul);
                else dp[j] = old[j];
            }
            sum += k;
        }
    }
    cout << dp[W] << endl;
}

// https://scrapbox.io/nojima/%E5%80%8B%E6%95%B0%E5%88%B6%E9%99%90%E4%BB%98%E3%81%8D%E3%83%8A%E3%83%83%E3%83%97%E3%82%B5%E3%83%83%E3%82%AF
// スライド最大化を使った解法
// 考え方
// naiveな遷移式は dp[i+1][j]:=max{dp[i][j-k*wi]+k*vi | 0<=k<=mi}
// 同じiでは常に固定区間に対する最大値を求めているので、スライド最大化が使える形に変形することを前提に考える
// -> 周期性は剰余でのグループ化がうまくいことが多く、剰余が同じであれば同じスライドの枠組みで連続的にmaxを求めることができる
int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n), m(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i] >> m[i];

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        // 剰余でグループ化
        vector<int> old(W + 1);
        swap(dp, old);
        for (int r = 0; r < w[i]; r++) {
            deque<pair<int, int>> deq;
            // 個数でループ
            for (int j = 0; j * w[i] + r <= W; j++) {
                int val = old[j * w[i] + r] - j * v[i];
                while (!deq.empty() && deq.back().first <= val) deq.pop_back();
                deq.emplace_back(val, j);

                dp[j * w[i] + r] = deq.front().first + j * v[i];
                if (deq.front().second == j - m[i]) deq.pop_front();
            }
        }
    }
    cout << dp[W] << endl;
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_H&lang=ja
// 巨大ナップサック: v,w共に大きい場合は、nが小さいことを条件にnのみに依存して計算することができる O(n2^(n/2))
// 半分全列挙を使う
int main() {
    int n; ll W; cin >> n >> W;
    vector<ll> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    // 前半分を全列挙
    int n2 = n / 2;
    vector<pair<ll, ll>> ps(1 << n2);
    for (int i = 0; i < 1 << n2; i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n2; j++) {
            if (i >> j & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        ps[i] = {sw, sv};
    }
    sort(ps.begin(), ps.end());
    int m = 1;
    for (int i = 1; i < 1 << n2; i++) {
        if (ps[m - 1].second < ps[i].second) ps[m++] = ps[i];
    }

    // 後ろ半分を全列挙
    ll ans = 0, INF = 1e17;
    for (int i = 0; i < 1 << (n - n2); i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n - n2; j++) {
            if (i >> j & 1) {
                sw += w[n2 + j];
                sv += v[n2 + j];
            }
        }
        if (W - sw >= 0) {
            auto it = lower_bound(ps.begin(), ps.begin() + m, make_pair(W - sw, INF));
            if (it != ps.begin()) {
                it--;
                ans = max(ans, sv + it->second);
            } else ans = max(ans, sv);
        }
    }
    cout << ans << endl;
}


// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_F&lang=ja
// 01ナップサックその2: O(nW)ではTLEだが、nとWの偏りが大きいケース => O(nV)
// 添字と値を入れ替える
int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    const int VMAX = 100 * n;
    const int INF = 1e7 * n + 1;
    vector<int> dp(VMAX + 1, INF); dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> old(VMAX + 1, INF); old[0] = 0;
        swap(dp, old);
        for (int j = 0; j <= VMAX; j++) {
            if (j - v[i] >= 0) dp[j] = min(old[j - v[i]] + w[i], old[j]);
            else dp[j] = old[j];
        }
    }
    for (int i = VMAX; i >= 0; i--) {
        if (dp[i] <= W) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja
// 個数制限なしナップサック問題
// 復元抽出の場合は自己遷移を書くことで、1個ずつ逐次的に自分自身を任意の個数選択する操作を表現できる
// このとき選ぶ個数が0個を考慮するために前の状態からの遷移とのmaxをとる
int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        vector<int> old(W + 1);
        swap(dp, old);
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[j] = max(dp[j - w[i]] + v[i], old[j]);
            else dp[j] = old[j];
        }
    }
    cout << dp[W] << endl;
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
// 01ナップサック問題
int main() {
    int n, W; cin >> n >> W;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        vector<int> old(W + 1);
        swap(dp, old);
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0) dp[j] = max(old[j - w[i]] + v[i], old[j]);
            else dp[j] = old[j];
        }
    }
    cout << dp[W] << endl;
}
