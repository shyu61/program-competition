#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using T = tuple<ll, int, int>;

// 思考フロー
// グリッド問題, 逐次問題。逐次問題の色が特に強い。全探索が間に合わないので、貪欲法かdpかグラフを検討する。
// -> 逐次問題はまず遷移条件を考えるところから始める。選択と吸収からなり、選択は最小のマスを常に選べば良いことには気づけるはず。
// -> 常に最小とくればpriority_queue

// priority_queueについて
// - デフォルトではmax-heapなので降順(優先度が"高い")
// - sortなどもそうだが、比較は基本lessで行われるので、`<`をオーバーライドする

// ポイント
// - 整数と割り算の結果を比較したい場合は、切り上げると整数値のまま比較ができる
//   - 分母を払うと桁が大きくなりすぎる場合に特に有効
//   - ⌈b/a⌉ = (b+a-1)/a を使う
// - priority_queueやsortなどは、うまくpairやtupleの順番や符号を調整してデフォルのコンパレータが使えるようにすると楽

// priority_queueとsetの計算量
// - priority_queue
//   - insert,delete: O(logN), ただしsetより定数倍高速
//   - init: O(N)
// - set
//   - insert,delete: O(logN)
//   - init: O(Nlogn)

array<int, 4> dx = {1,0,-1,0}, dy = {0,1,0,-1};
int H, W, X, P, Q;
vector<vector<ll>> S;

void push(int x, int y, priority_queue<T, vector<T>, greater<T>>& pq) {
    for (int r = 0; r < 4; r++) {
        int nx = x + dx[r], ny = y + dy[r];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && S[nx][ny] != -1) {
            pq.emplace(S[nx][ny], nx, ny);
        }
    }
}

int main() {
    cin >> H >> W >> X;
    cin >> P >> Q; P--; Q--;
    S = vector<vector<ll>>(H, vector<ll>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> S[i][j];
    }

    priority_queue<T, vector<T>, greater<T>> pq;
    ll now = S[P][Q];
    S[P][Q] = -1;  // 吸収済み
    push(P, Q, pq);

    while (!pq.empty()) {
        auto [s, x, y] = pq.top(); pq.pop();
        if (S[x][y] == -1) continue;
        if (s >= (now + X - 1) / X) break;
        now += s;
        S[x][y] = -1;
        push(x, y, pq);
    }

    cout << now << endl;
}
