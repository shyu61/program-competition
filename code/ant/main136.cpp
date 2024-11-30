// デックの利用(スライド最小値): p300
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 尺取り法は和や数え上げが得意でmin/maxには適用できないが、dequeを使うとmin/maxにも拡張できる。O(n)
// 尺取り法は重複部分を単純な計算結果で保持するが、dequeは順序を保持しつつ最小値候補をO(1)で取り出せるよう昇順で保持する構造を採用している
// dequeの利用シーン
// 区間のmin/maxを連続的に何度も求めたいケース
// <- 尺取り法と同じで飛地に弱い。飛地の場合はセグ木を使う

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n - k + 1);

    deque<pair<int, int>> que;
    for (int i = 0; i < n; i++) {
        while (!que.empty() && que.back().first >= a[i]) que.pop_back();
        que.emplace_back(a[i], i);
        if (i - k + 1 >= 0) {
            b[i - k + 1] = que.front().first;
            if (que.front().second == i - k + 1) que.pop_front();
        }
    }

    for (auto v : b) cout << v << endl;
}
