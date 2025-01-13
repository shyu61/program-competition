#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 組合せ最適化, ペアリング問題, 数え上げ, 区間クエリ

// 方針
// まずEと同様に解くことを考えると、各クエリO(NlogN)で求解でき、クエリ回実行するとO(QNlogN)となりTLE
// 各クエリをO(logN)程度で処理する必要がある
// 区間クエリの高速化は区間アルゴリズムを使うのが定石。事前計算が絡むケースも多い。
// しかし、区間の伸縮が高速であることが前提の尺取り法やmo's, 区間のmergeが高速であることが前提のsegtreeなども直接解を持たせると効率的に処理ができないことがわかる
// 解を直接持たせてダメなら、間接情報を持たせることを考える。
// O(NlogN)のうち、Nは線形スキャンなので高速化の余地がありそう。「全て満たすか」を調べる線形スキャンなので「最悪のケースが満たすか」に言い換えて考えると、事前計算とsegtreeによりO(logN)でできることがわかる

template<auto op, int iv>
struct Segtree {
    vector<int> dat;
    int sz = 1;

    Segtree() {}
    // n: 要素数, a: 初期化時に利用する値
    Segtree(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<int>(sz * 2 - 1, iv);

        for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    int query(int a, int b) { return query(a, b, 0, 0, sz); }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = op(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    private:
        // [a, b)の最小値を探索
        // k: ノード番号, [l, r)はそれに紐づく区間
        int query(int a, int b, int k, int l, int r) {
            // [a, b)と[l, r)が交差しない場合は解なし
            if (b <= l || r <= a) return iv;
            // [a, b)が[l, r)を完全に含んでいる時、このノードの値が解
            if (a <= l && r <= b) return dat[k];
            else {
                int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
                int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
                return op(vl, vr);
            }
        }
};

int op(int a, int b) { return max(a, b); }

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // ∀iについて Ai*2>=Aj となる最小のjまでの距離を事前計算
    vector<int> B(N);
    int cur = 0;
    for (int i = 0; i < N; i++) {
        while (cur < N && A[i] * 2 > A[cur]) cur++;
        B[i] = cur - i;
    }

    Segtree<op, 0> rmq(N, B);

    auto check = [&](int l, int r, int k) -> bool {
        return rmq.query(l, l + k) <= r - l - k;
    };

    int Q; cin >> Q;
    for (int q = 0; q < Q; q++) {
        int l, r; cin >> l >> r;
        l--;

        int lb = 0, ub = (r - l) / 2 + 1;
        while (ub - lb > 1) {
            int m = (lb + ub) / 2;
            check(l, r, m) ? lb = m : ub = m;
        }
        cout << lb << endl;
    }
}
