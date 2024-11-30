// スタックの利用: p298
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// stackの本質
// 逐次的に処理をして、ある条件に達した場合にある条件が満たさなくなるまで"戻る"という操作が得意

// stackが使えるシーン
// dfs(バックトラック), 逐次問題, グリッド問題
// 特に長方形などの面積が絡む問題ではよく使う

const int INF = 1e9;

int main() {
    int n; cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    stack<pair<int, int>> st;
    ll maxs = 0;
    for (int i = 0; i <= n; i++) {
        int hi = i < n ? h[i] : 0;
        int j = i;
        // h[i]より小さくなるまで戻る
        while (!st.empty() && st.top().first >= hi) {
            int nh = st.top().first;
            j = st.top().second; st.pop();
            // 都度面積を計算する
            maxs = max(maxs, ll(nh) * (i - j));
        }
        // 戻った地点でh[i]を加える
        st.emplace(hi, j);
    }

    cout << maxs << endl;
}
