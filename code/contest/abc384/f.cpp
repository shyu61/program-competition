#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ポイント
// - 全てのペアに対する操作を伴う問題のパターンは以下の2つ
//   - そもそもペアの生成が間に合わない
//     - 対称なものをまとめて計算する
//     - 剰余が絡むなら余りで分類すると良い
//     - ペアの剰余は移項により独立に計算できる(事前計算により高速化ができる)
//   - f(x)の計算が間に合わない
// - a^bの剰余は「少なくともaでb回割れる」のであって「ちょうどaでb回割れる」わけではない
//   - つまりちょうどを求めたいなら累積和と同様引き算をする必要がある
//   - 逆に言えば累乗の剰余を考えるときは「ちょうど」を直接実装せず、剰余を使って間接的に求めるのが良い

// mapとunordered_map
// - 内部実装は全然違うし速度も全然違う
// - map: 二分探索木(赤黒木)
//   - search,insert,delete: O(logN)
// - unorderd_map: ハッシュテーブル
//   - search,insert,delete: O(1)
//     - バケット単位でハッシュテーブルを保持するので、削除後に後続の要素をシフトする必要がなく、deleteもO(1)になる
//   - iteratorに順序がない。it++のように要素を走査することはできるが、出力順序保証はない

const int K = 25;  // 2^25 > max{Ai} = 2*10^5

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<ll> d(K + 1);  // dk := Ai+Aj が2^kの倍数であるものの総和
    for (int k = 0; k < K; k++) {
        int k2 = 1 << k;
        unordered_map<int, pair<int, ll>> s;
        for (auto ai : A) {
            // 剰余ごとに分類する
            int r = (-ai % k2 + k2) % k2;
            s[r].first++;
            s[r].second += ai;

            // 現在のajにおいて、考慮して良いaiはi<=jの範囲のみ
            d[k] += ll(s[ai % k2].first) * ai + s[ai % k2].second;
        }
    }

    ll ans = 0;
    for (int i = 0; i < K; i++) {
        ans += (d[i] - d[i + 1]) / (1 << i);
    }
    cout << ans << endl;
}
