// Grundy数(コインのゲーム2): p281
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// grundy数とは
// - nimの石の個数を抽象化した指標
// - 操作に制限がある, サブゲーム数が動的などのゲームをnimに帰着するためのもの
// - 次の一手でいける状態のgrundy数のmex(含まれない最小非負整数)
// - grundy数の定義自体はゲーム全体で共通(サブゲームによって違わない)
// - grundy=x: 次の一手で状態0,1,...,x-1の任意の状態に行ける
// - grundy=0: 負け確, grundy≠0: 勝ち確
//   - 定義より、grundy=0とは次の一手で状態0に行けない, grundy≠0とは次の一手で状態0に行ける
//   - これらサブゲームの勝敗の組合せで全体勝敗が決定するため、XORで表現する

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(k), x(n);
    rep(i, k) cin >> a[i];
    rep(i, n) cin >> x[i];

    int mx = 0;
    rep(i, n) mx = max(mx, x[i]);

    // 一つの山に注目してgrundy数を計算
    // grundy[i] := その山に石がi個あるときのgrundy数
    vector<int> grundy(n + 1);
    for (int i = 1; i <= mx; i++) {
        set<int> st;  // grundy[i]から次の一手でいける状態のgrundy数
        rep(j, k) {  // 選ぶaを全探索
            if (a[j] <= i) st.insert(grundy[i - a[j]]);
        }

        // stに含まれない最小の非負整数を探索
        int g = 0;
        while (st.contains(g)) g++;
        grundy[i] = g;
    }

    // 全ての山のgrundy数のXORをとる
    int res = 0;
    rep(i, n) res ^= grundy[x[i]];

    if (res) cout << "Bob" << endl;
    else cout << "Alice" << endl;
}
