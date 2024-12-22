// ゲームと必勝法(コインのゲーム1): p272
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ゲームの必勝法
// - DPを使う: 明確な状態が存在し、操作は遷移として定義できるため
// - 後ろから考える: ゲームには明確な終了状態が存在する。その状態から逆方向に考えていく
// - ある状態で手番のプレイヤーが勝てるかどうかで考える。相手が負けるように遷移できるなら勝てる

int main() {
    int x, k; cin >> x >> k;
    vector<int> a(k);
    for (int i = 0; i < k; i++) cin >> a[i];

    vector<bool> win(x + 1);  // win[i]: 残りi枚の状態で手番のプレイヤーが勝てるか
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < k; j++) {
            // 残りi-a[j]枚 -> i枚へ遷移するとき、i-a[j]の状態でfalse(相手が負ける)ものが一つでもあれば、
            // そのカードa[j]を選ぶことで今の手番のプレイヤーは勝てる
            if (i - a[j] >= 0 && !win[i - a[j]]) {
                win[i] = true;
                break;
            }
        }
    }
    cout << (win[x] ? "Alice" : "Bob") << endl;
}
