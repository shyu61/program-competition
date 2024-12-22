// デックの利用: スライド最小値: p300
// dequeによる解法
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;
int n, k;
vector<int> a;

deque<pair<int, int>> deq;

void push(int v, int i) {
    // 常に先頭に最小値が来るように処理する
    // 末尾からpopしながら進むことで、範囲外要素は必ずpushがgetのどちらかで除去される
    while (!deq.empty() && deq.back().first >= v) deq.pop_back();
    deq.emplace_back(v, i);
}

int get(int left) {
    auto [v, i] = deq.front();
    // 使った先頭がキャンセル対象の場合はpopする
    if (i == left) deq.pop_front();
    return v;
}

int main() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b;
    for (int i = 0; i < n; i++) {
        push(a[i], i);
        if (i >= k - 1) b.push_back(get(i - k + 1));
    }

    for (auto x : b) cout << x << " ";
    cout << endl;
}
