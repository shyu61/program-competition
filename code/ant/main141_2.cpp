// 枝刈り(解が悪くなったら打ち切る): p313
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ヒューリスティックなコスト見積もりを加味した実装

const int INF = 2 * 5 * (5 + 1);
int M, S, minv = INF;  // M: 初期状態での残りマッチ数, S: 初期状態での残り正方形数
vector<vector<bool>> m;  // m[p][i]: マッチpが正方形iに含まれるか
vector<int> mmax;  // mmax[i]: 正方形iを壊せるマッチ番号の最大値

// p以降のマッチを考えた時の解の下限 => 最大独立集合と同じ(各独立な正方形を壊すのにはマッチ1本が必ず必要)
int hstar(int p, vector<bool> state) {
    vector<pair<int, int>> ps;
    for (int i = 0; i < S; i++) {
        if (state[i]) {
            int num = 0;
            for (int j = p; j < M; j++) {
                if (m[j][i]) num++;
            }
            ps.emplace_back(num, i);
        }
    }
    sort(ps.begin(), ps.end());
    int res = 0;
    // used[i]: Xに含まれる正方形でマッチiを含むものが存在する
    vector<bool> used(M);
    for (auto [_, id] : ps) {
        bool ok = true;
        for (int j = p; j < M; j++) {
            if (m[j][id] && used[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            res++;
            for (int j = p; j < M; j++) {
                if (m[j][id]) used[j] = true;
            }
        }
    }
    return res;
}

// state[i]: 正方形iが残ってるか
int dfs(int p, int num, vector<bool> state) {
    if (p == M) return minv = num;
    if (num + hstar(p, state) >= minv) return INF;

    // use: マッチpを必ず除く
    // notuse: マッチpを必ず除かない
    bool use = false, notuse = true;
    for (int i = 0; i < S; i++) {
        // マッチpが正方形iに含まれる => pを除けば正方形が減る => 除いても除かなくてもok
        if (state[i] && m[p][i]) notuse = false;
        // マッチpが正方形iを壊すための最後の番号 => 必ず取り除かないといけない
        if (state[i] && mmax[i] == p) use = true;
    }

    int res = INF;
    // マッチpを除かない場合
    if (!use) res = min(res, dfs(p + 1, num, state));

    // マッチpを除く場合
    for (int i = 0; i < S; i++) {
        if (m[p][i]) state[i] = false;
    }
    if (!notuse) res = min(res, dfs(p + 1, num + 1, state));
    return res;
}

void init(int N, int num, vector<bool> removes) {
    int total = 2 * N * (N + 1);
    M = total - num;

    int max_square = 0;
    for (int i = N; i > 0; i--) max_square += i * i;

    // 初期状態でマッチpまでで取り除かれているマッチの本数を計算
    int cum = 0;
    vector<int> blanks(total);
    for (int i = 0; i < total; i++) {
        if (removes[i]) cum++;
        blanks[i] = cum;
    }

    m = vector<vector<bool>>(M, vector<bool>(max_square));
    mmax = vector<int>(max_square);

    // 正方形のサイズ
    for (int k = 1; k <= N; k++) {
        // 正方形の位置
        for (int r = 0; r <= N - k; r++) {
            for (int c = 0; c <= N - k; c++) {
                vector<int> matches;

                for (int i = 0; i < k; i++) {
                    int left = (r + 1) * N + r * (N + 1) + c + i * (N * 2 + 1);
                    matches.push_back(left);

                    int right = left + k;
                    matches.push_back(right);

                    int top = r * (N * 2 + 1) + c + i;
                    matches.push_back(top);

                    // mmaxになるので配列の最後にする
                    int bottom = top + (N * 2 + 1) * k;
                    matches.push_back(bottom);
                }

                bool ok = true;
                for (auto p : matches) {
                    if (removes[p]) ok = false;
                }
                if (ok) {
                    for (auto p : matches) m[p - blanks[p]][S] = true;
                    mmax[S] = matches[matches.size() - 1];
                    S++;
                }
            }
        }
    }
}

int main() {
    int N, num; cin >> N >> num;
    vector<bool> removes(N * 2 * (N + 1));
    for (int i = 0; i < num; i++) {
        int k; cin >> k;
        removes[k] = true;
    }
    init(N, num, removes);

    vector<bool> state(S, true);
    cout << dfs(0, 0, state) << endl;
}
