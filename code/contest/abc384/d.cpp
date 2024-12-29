#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ポイント
// - 周期性がある問題は、剰余を取ることで周期の範囲内に還元することができる
// - 周期性の問題は、周期を跨ぐ場合を考慮するために2倍長を考える
//   - 時刻などを扱う問題も同様
// - 累積和は開区間: S[i+1]はa[i]までの累積和を表し, S[0]は常に0

// 累積和と尺取り法
// 累積和: 調べたい区間が明確な場合, 区間幅が明確な場合
// 尺取り法: 条件を満たす区間を逐次的に探索したい場合
// -> 本問題は区間和がSになる区間の探索なので、条件と見れば尺取り法だし、区間幅がSと見れば累積和でもいい

int main() {
    ll N, S; cin >> N >> S;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    ll sum = 0;
    for (int i = 0; i < N; i++) sum += A[i];
    if (S > sum) S %= sum;

    // 尺取り法
    sum = 0;
    int right = 0;
    for (int left = 0; left < N * 2; left++) {
        while (sum < S && right < N * 2) {
            sum += A[right % N];
            right++;
        }

        if (sum == S) {
            cout << "Yes" << endl;
            return 0;
        }

        if (sum > S) {
            sum -= A[left % N];
        } else break;
    }
    cout << "No" << endl;
}

// 別解
int main() {
    ll N, S; cin >> N >> S;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // 累積和
    vector<ll> s(N * 2 + 1);
    for (int i = 0; i < N * 2; i++) s[i + 1] = s[i] + A[i % N];

    S %= s[N];

    set<ll> st;
    for (auto si : s) st.insert(si);
    for (auto si : s) {
        if (st.count(si - S)) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
