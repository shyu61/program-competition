#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;
using P = pair<int, bool>;

// ジャンル
// グリッド問題, 組合せ最適化, ドミノ敷き詰めdp

// ポイント
// ドミノ敷き詰めdpで、直近の状態がwの時は列番号で良いが、それ以上の場合は順番に持って右シフトすることで遷移に対応する
// bitdpは常に特定の範囲をbit全探索している意識を持つ。sparseなら事前計算で計算量が落とせる
// - sparseと座標圧縮はセットで考える
// mapは重い。際どいループ内では極力避ける

vector<int> dx = {1,1,1,0,0,-1,-1,-1}, dy = {1,0,-1,1,-1,1,0,-1};

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    vector<vector<bool>> used(25, vector<bool>(25));
    auto check = [&](int i, int j) -> bool {
        rep(r, 8) {
            int ni = i + dy[r], nj = j + dx[r];
            if (ni < 0 || nj < 0 || nj >= w) continue;
            if (used[ni][nj]) return false;
        }
        return true;
    };

    vector<unordered_map<int, P>> mp(w);  // 位置状態ごとに状態と状態番号を紐づける(圧縮のため)
    vector<vector<int>> states(w);
	auto dfs = [&](auto dfs, int pos, int d, int state) -> void {
		int i = pos / w, j = pos % w;
		if (d == w + 1) {
            mp[j][state] = make_pair(states[j].size(), check(i, j));
			states[j].push_back(state);
			return;
		}
	    dfs(dfs, pos + 1, d + 1, state);  // 置かない場合
        if (check(i, j)) {
            used[i][j] = true;
            dfs(dfs, pos + 1, d + 1, state | 1 << d);  // 置く場合
            used[i][j] = false;
        }
	};

	rep(i, w) dfs(dfs, i, 0, 0);

    vector<vector<int>> nx0(w), nx1(w);
    rep(i, w) {
        for (auto s : states[i]) {
            int nx0i = mp[(i + 1) % w][s >> 1].first;
            int nx1i = mp[(i + 1) % w][s >> 1 | 1 << w].first;
            bool ok = mp[i % w][s].second;

            nx0[i].push_back(nx0i);
            nx1[i].push_back(ok ? nx1i : -1);
        }
    }

    vector<mint> dp(states[0].size());
    dp[0] = 1;
	rep(i, h) {
		rep(j, w) {
            vector<mint> old(states[(j + 1) % w].size());
            swap(dp, old);
            rep(si, states[j].size()) {
				dp[nx0[j][si]] += old[si];
				if (nx1[j][si] != -1 && mas[i][j] == '.') {
                    dp[nx1[j][si]] += old[si];
                }
			}
		}
	}

	mint ans = 0;
    rep(i, states[0].size()) ans += dp[i];
	cout << ans.val() << endl;
}
