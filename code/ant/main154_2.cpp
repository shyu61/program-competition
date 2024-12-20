// Endless Knight: p353
#include <bits/stdc++.h>
#include <./lib/mod.cpp>
using namespace std;
using P = pair<int, int>;

// 全探索するとO(H+W/3 ^2)でLargeが解けない
// -> 開始位置が固定かつ遷移がh,w共に増える方向のみで、かつ数え上げなのでほとんどの枝刈りが使えない
// -> 全探索以外の方法を考える必要がある
// -> 遷移が隣接ではない、かつ代数的特徴を持つ(Δx^2 + Δy^2 = 5)ので座標変換をして隣接遷移に変換できないか検討する
// -> 隣接変換すると、右or下の隣接移動のみになる -> パスのパターンが単純なcombinationで計算できる形に帰着される
// -> あとは数え上げるだけ。場合の数の数え上げは、直接数えるか余事象で数えるかをまず検討する。
// -> 石の上限が小さいので明らかに余事象で数えた方が良い。つまり「少なくとも1つ以上の石を通るパスの総数」を数えれば良い
// -> 「少なくとも」は和集合なので、一般に積集合で考えた方が良いので包除原理を使う。
// -> 余事象の包除原理は空集合を考えて全ての符号を反転させれば一発で計算できることを利用すると良い。

// ポイント
// - グリッド問題で隣接移動じゃないものは座標変換して隣接移動に直せないか検討する
//   - 遷移が代数的特徴を持つ場合は変換できるケースが多い
//     - 逆にランダムウォークや確率的な遷移をする場合は変換が意味をなさないことが多い
//   - 単調性がある場合は座標変換によりそれを最大限に活かせる場合がある
// - 隣接遷移のパス数え上げはcombinationが使える形に帰着できないか考える
// - 場合の数の数え上げは、まず直接数えるか余事象で数えるか考える
// - 余事象の包除原理は空集合を考えて符号反転
// - グリッド上での遷移のパターンは単純なcombinationに帰着できる場合がある
// - 配列からの要素削除はeraseではなく、末尾のptrの位置で調整する

const int MOD = 10007;

bool normalize(int& x, int& y) {
    int xx = -x + y * 2, yy = x * 2 - y;
    if (xx < 0 || xx % 3 != 0 || yy < 0 || yy % 3 != 0) return false;
    x = xx / 3; y = yy / 3;
    return true;
}

int main() {
    int H, W, R; cin >> H >> W >> R;
    vector<P> ps(R + 1);  // 石の位置
    for (int i = 0; i < R; i++) {
        cin >> ps[i].first >> ps[i].second;
        ps[i].first--; ps[i].second--;
    }

    int pn = 0;  // 到達可能点に置かれた石の数
    for (int i = 0; i < R; i++) {
        // 到達不可能な点に置かれた石は除外しておく
        if (normalize(ps[i].first, ps[i].second)) {
            ps[pn++] = ps[i];
        }
    }

    // ゴールが到達不可能なら0通り
    ps[pn] = P(H - 1, W - 1);
    if (!normalize(ps[pn].first, ps[pn].second)) {
        cout << 0 << endl;
        return 0;
    }
    sort(ps.begin(), ps.begin() + pn);

    int res = 0;
    Mod mod = Mod(MOD);
    // 全ての石の積集合を考える
    for (int i = 0; i < (1 << pn); i++) {
        int add = 1, prevx = 0, prevy = 0, num = -1;
        for (int j = 0; j <= pn; j++) {  // pnを含むのは最後ゴールも考えるから
            if (i >> j & 1 || j == pn) {
                num++;
                // 石jまでで (mx+my)Cmx 通りのパスがある
                int mx = ps[j].first - prevx, my = ps[j].second - prevy;
                add = add * mod.get_comb(mx + my, mx) % MOD;
                prevx = ps[j].first;
                prevy = ps[j].second;
            }
        }
        // 包除原理で和集合を求める
        if (num % 2 == 0) res = (res + add) % MOD;
        else res = (res - add + MOD) % MOD;
    }

    cout << res << endl;
}
