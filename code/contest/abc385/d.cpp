#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// lower_bound,upper_boundについて
// 定義としては、lower_bound: value以上の最初の位置, upper_bound: valueより大きい最初の位置 となっているが、
// 基本設計は「valueと等しい値の位置の下限と上限」である。(但し上限は含まない)
// しかし等しい値が存在しなかった時に破綻しないよう、次の値を返すという設計になっている。(この時lower_boundとupper_boundは同じ位置を返す)

// setについて
// - 内部は木構造なのでランダムアクセスをサポートしない。故にiteratorも`+1`のような演算をサポートしない。ランダムアクセスしたいなら、`vector + sort + unique`を使う(構築コストはsetと同じ)
// - 但し、動的にinsertやdeleteを行う場合はsetがO(logN)で高速。vectorは操作位置以降の移動が発生するのでO(N)になる。
// - eraseは注意
//   - eraseした位置のiteratorは未定義になる。戻り値が次のiteratorなのでそれを使って進める

// ポイント
// - グリッド上で遷移を伴う時、遷移の制約条件をまず整理する
//   - 斜めに動くのか、隣接遷移のみなのか、水平/垂直遷移のみなのか
//   - 斜めなら隣接遷移に変換できないか
// - sparse管理はvectorよりmapが適している
// - 再訪管理の方法
//   - vector<bool>を使う, eraseする
//   - 取り除くことで探索対象が縮小する構造になっているかを見極める
//   - eraseするならsetなど木構造が必要

int N, M, ans = 0;
map<ll, set<ll>> Hx, Hy;

void move_y(ll x, ll y, ll ny) {
    if (y > ny) swap(y, ny);
    auto lb = Hx[x].lower_bound(y);
    auto ub = Hx[x].upper_bound(ny);
    while (lb != ub) {
        ans++;
        Hy[*lb].erase(x);
        lb = Hx[x].erase(lb);
    }
}

void move_x(ll x, ll y, ll nx) {
    if (x > nx) swap(x, nx);
    auto lb = Hy[y].lower_bound(x);
    auto ub = Hy[y].upper_bound(nx);
    while (lb != ub) {
        ans++;
        Hx[*lb].erase(y);
        lb = Hy[y].erase(lb);
    }
}

int main() {
    int sx, sy; cin >> N >> M >> sx >> sy;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        Hx[x].insert(y);
        Hy[y].insert(x);
    }

    ll x = sx, y = sy;
    for (int i = 0; i < M; i++) {
        char d; int c; cin >> d >> c;
        if (d == 'U') {
            move_y(x, y, y + c);
            y += c;
        } else if (d == 'D') {
            move_y(x, y, y - c);
            y -= c;
        } else if (d == 'L') {
            move_x(x, y, x - c);
            x -= c;
        } else if (d == 'R') {
            move_x(x, y, x + c);
            x += c;
        }
    }

    cout << x << ' ' << y << ' ' << ans << endl;
}
