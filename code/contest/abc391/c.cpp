#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 方針
// update: 鳩を探して移動する
//   - 鳩がどこにいるかの位置配列: O(1)
//   - 移動: O(1)
// query: 複数いる巣の個数
//   - 巣ごとの鳩の数: O(1)
//   - 上記を使ってクエリ毎に、複数いる巣の個数を計算: O(1)

// ポイント
// 何を高速化する必要があるのかを分解して、1つずつ考える

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n), cnt(n, 1);
    int num = 0;
    rep(i, n) a[i] = i;

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int p, h; cin >> p >> h; p--; h--;
            cnt[a[p]]--;
            if (cnt[a[p]] == 1) num--;
            a[p] = h;
            cnt[a[p]]++;
            if (cnt[a[p]] == 2) num++;
        } else {
            cout << num << '\n';
        }
    }
}
