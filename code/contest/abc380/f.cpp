#include <bits/stdc++.h>
using namespace std;

// ジャンル
// ゲーム問題, bitdp, 全探索

// 方針
// ゲーム問題なので、各局面での状態を考えて、その状態からスタートした時の勝敗をdpで記述する
// 遷移先に1つでもfalse(相手が負ける)状態があればtrue(先手の勝利)として遷移を記述する
// 後は各状態の持ち方を考えれば良い
// 各カードの状態は3パターンあるので、3進数か3要素tupleで持つ

// ポイント
// 集合dpは必ずしもbit列とは限らない。3進数や普通にvectorで持つケースもある
//   - このケースは再帰で書く方が良い
// ゲーム問題は各局面の状態をどう表現するかが最重要
//   - 存在性: 2進数
//   - 存在場所,より詳細な状態など3値以上のパターンを取りうる場合: 3進数, 各パターンをtupleで別々にvectorなどで保持

int main() {
    int n, m, l; cin >> n >> m >> l;
    vector<int> a(n), b(m), c(l);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < l; i++) cin >> c[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    using T = tuple<vector<int>, vector<int>, vector<int>>;
    map<T, bool> mem;

    // 状態sからスタートした時に先手が勝つかどうか
    auto rec = [&](auto rec, T s) -> bool {
        if (mem.count(s)) return mem[s];
        auto [sa, sb, sc] = s;
        bool res = false;
        // 状態sからの遷移先で、少なくとも1つ相手が負ける選択肢があるか
        // -> 状態sで操作できるカードを全探索する
        for (int i = 0; i < sa.size(); i++) {
            auto na = sa, nc = sc;
            nc.push_back(sa[i]);
            na.erase(na.begin() + i);
            sort(nc.begin(), nc.end());
            // カードを出した後、場からカードを取らない場合
            if (!rec(rec, T(sb, na, nc))) {
                res = true;
                break;
            }
            // カードを出した後、場からカードを取る場合
            for (int j = 0; j < nc.size(); j++) {
                if (nc[j] < sa[i]) {
                    auto na2 = na, nc2 = nc;
                    nc2.erase(nc2.begin() + j);
                    na2.push_back(nc[j]);
                    sort(na2.begin(), na2.end());
                    if (!rec(rec, T(sb, na2, nc2))) {
                        res = true;
                        break;
                    }
                }
            }
        }
        return mem[s] = res;
    };

    bool ans = rec(rec, T(a, b, c));
    cout << (ans ? "Takahashi" : "Aoki") << endl;
}

// 3進数による解法
int main() {
    int n, m, l; cin >> n >> m >> l;
    int N = n + m + l;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    // 3進数で状態を保持
    int state = 0;
    auto get = [&](int s, int i) -> int { return s >> 2 * i & 3; };
    auto set = [&](int& s, int i, int v) -> void { s = (s & ~(3 << 2 * i)) | (v << 2 * i); };

    for (int i = 0; i < n; i++) set(state, i, 0);
    for (int i = n; i < n + m; i++) set(state, i, 1);
    for (int i = n + m; i < N; i++) set(state, i, 2);
	
	unordered_map<int, bool> mem;
	auto rec = [&](auto rec, int s, int turn) -> bool {
        if (mem.count(s << 1 | turn)) return mem[s << 1 | turn];

        bool res = false;
		for(int i = 0; i < N; i++) {
			if (get(s, i) != turn) continue;
            int ns = s;
			set(ns, i, 2);
            if (!(rec(rec, ns, !turn))) {
                res = true;
                break;
            }

			for (int j = 0; j < N; j++) {
                if (get(s, j) != 2 || a[j] >= a[i]) continue;
                int ns2 = ns;
				set(ns2, j, turn);
                if (!(rec(rec, ns2, !turn))) {
                    res = true;
                    break;
                }
			}
		}
		return mem[s << 1 | turn] = res;
	};

    bool ans = rec(rec, state, 0);
    cout << (ans ? "Takahashi" : "Aoki") << endl;
}
