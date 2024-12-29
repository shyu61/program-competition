#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// f(x)は因数が絡むので数論の問題
// -> ある関数f(x)の合計などを計算する問題。大抵は、そもそも全てのxを入力する時間すらないケースが多い(f(x)をO(1)で計算できたとしても間に合わない)
// -> 同じ値を取るf(x)などをまとめて計算する必要がある

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

    vector<ll> d(K + 1);
    for (int k = 0; k < K; k++) {
        int kk = 1 << k;
        unordered_map<int, pair<int, ll>> s;
        for (auto aj : A) {
            int i = (-aj % kk + kk) % kk;

            s[i].first++;
            s[i].second += aj;
            d[k] += ll(s[aj % kk].first) * aj + s[aj % kk].second;
        }
    }

    ll ans = 0;
    for (int i = 0; i < K; i++) {
        ans += (d[i] - d[i + 1]) / (1 << i);
    }
    cout << ans << endl;
}
