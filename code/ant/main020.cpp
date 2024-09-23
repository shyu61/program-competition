// デックの利用: スライド最小値: p300
// dequeによる解法
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;
int n, k;
vector<int> a;

deque<int> deq;

void push(int v) {
    // 常に先頭に最小値が来るように処理する
    // 末尾からpopしながら進むことで、範囲外要素は必ずpushがgetのどちらかで除去される
    while (!deq.empty() && deq.back() >= v) deq.pop_back();
    deq.push_back(v);
}

int get() {
    int v = deq.front();
    deq.pop_front();
    return v;
}

int main() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b;
    for (int i = 0; i < n; i++) {
        push(a[i]);
        if (i >= k - 1) b.push_back(get());
    }

    for (auto x : b) cout << x << " ";
    cout << endl;
}
