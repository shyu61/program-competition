// 枝刈り(解が悪くなったら打ち切る): p313
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ナイーブな実装

// 整数計画問題のポイント
// 1. 終了判定や枝刈り判定がしやすい形で初期化する
//   - 保持する必要がある状態を洗い出す
//     - どのマッチが残っているか
//     - 各正方形が存在しているか
//     - 各正方形を構成するマッチとの関係性
// 2. 枝刈りの実装
//   - 探索順序の工夫(木の形状の最適化)
//     1. 最も制約の強い変数を優先する(可能な選択肢が少ない変数)
//     2. 最も制約を課す変数を優先する(他の変数により多くの制約を課す変数)
//   - 解が悪くなったら打ち切り(局所的な評価関数の利用)
//     1. 状況が改善しない
//     2. αβ法
//     3. 必須条件の利用

const int INF = 2 * 5 * (5 + 1);
int M, S, minv = INF;  // M: 初期状態での残りマッチ数, S: 初期状態での残り正方形数
vector<vector<bool>> m;  // m[p][i]: マッチpが正方形iに含まれるか
vector<int> mmax;  // mmax[i]: 正方形iを壊せるマッチ番号の最大値

// state[i]: 正方形iが残ってるか
int dfs(int p, int num, vector<bool> state) {
    if (p == M) return minv = num;
    if (num >= minv) return INF;

    // テクニック: ある操作を行うための条件が複数あって、それらが独立に判定可能な場合は、抽象化変数を使ってまとめて判定すると便利
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

// 初期化の難易度が高いが、「必要な情報は何か？」をまず考えて計算する順番を設計してから実装する
// m[p][i]の計算には、明らかに正方形への採番と、その正方形を構成するマッチの番号つまりtop,bottom,left,rightを計算する必要があることがわかる
// top,bottom,left,rightを計算するには、正方形のサイズと位置をパラメーターで渡せば良いこともわかる
// top,bottom,left,rightの計算は繰り返し単位(周期性)を適切に考えればそれほど難しくない

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
