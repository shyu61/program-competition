// 行列: p256
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vec = vector<double>;
using mat = vector<vec>;

// 条件付き期待値の繰り返し期待値の法則より、ある期待値はその状態へ遷移する前の状態の期待値*確率の総和になる(Ex = Σ(i=1,n)E[x|yi]*Pi)
// 本問題に限らす期待値DPでは上記の法則を使って遷移を記述することになる
// https://math314.hateblo.jp/entry/2013/12/12/232045

// また期待値は値なので、確定値と和を取ることができる
// ex)コイントスとで2回目以降で初めて表が出る期待値は、1回目以降で表が出る期待値をEとすると、1+Eとなる
// 1は初回確定分で、Eは状態として1回目の試行前の状態と全く同じになる(自己ループ)ため
// 今回の場合は、`E(x,y) = 0.25*(E(x-1,y)+1) + 0.25*(E(x,y-1)+1) + 0.25*(E(x+1,y)+1) + 0.25*(E(x,y+1)+1)`であり、
// 一つ前の状態における期待値から、追加一回分の操作が確定するので+1する必要がある

// ポイント
// 連立方程式の使用を検討すべきシーン
// - DPのように遷移の関係が記述できる
//   - 但しその関係式は線形である
//   - 局所的な制約であり、全体制約がない
// - 値が`確率`や`期待値`などの連続値である
// - 自己ループがあってDPでは解けない、遷移条件が複雑でDPで記述するのが大変
// - 最適化ではなく値を求めたい
// - 時間制約に余裕がある

// DPの代替手段としてネットワークフローもある。ネットワークフローの使用を検討すべきシーンは以下
// - 値が離散値
// - 最適化問題である
// - 局所的な制約条件に加え、全体制約がある
// - 遷移条件(関係式)は線形である必要はない

// 本問題は、ランダムウォークであり自己ループがあるためDPでは解けない。求める値が連続値であり局所的な関係式で記述できかつ一次なので一次連立方程式で解く

const double EPS = 1e-8;
vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};
vector<vector<bool>> grid, can_goal;
int N, M;

vec gauss_jordan(const mat& A, const vec& b) {
    int n = A.size();
    // 拡大係数行列の作成
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) B[i][j] = A[i][j];
    }
    // 行列Aの後ろにbを並べ同時に処理する
    for (int i = 0; i < n; i++) B[i][n] = b[i];

    for (int i = 0; i < n; i++) {
        // 注目している変数の係数の絶対値が大きい式をi番目に持ってくる
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i], B[pivot]);

        // 解がないか、一意でない
        if (abs(B[i][i]) < EPS) return vec();

        // 注目している変数の係数を1にする
        for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                // j番目の式からi番目の変数を消去
                // B[i][i]は1なのでB[i]をB[j][i]倍して引く
                for (int k = i + 1; k <= n; k++) B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    vec x(n);
    // 後ろに並べたbが解になる
    for (int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}

void dfs(int x, int y) {
    can_goal[x][y] = true;
    for (int r = 0; r < 4; r++) {
        int nx = x + dx[r], ny = y + dy[r];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !can_goal[nx][ny] && grid[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    cin >> N >> M;
    grid = can_goal = vector<vector<bool>>(N, vector<bool>(M));
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            char c; cin >> c;
            if (c == '.') grid[x][y] = true;
        }
    }

    dfs(N - 1, M - 1);

    // 立式の際はまず方程式を書いてみて定数項が右辺に来るよう変形してみる
    // 行番号は何個目の方程式かを表し、各列が各変数の係数になる
    // 行列の構築
    mat A = mat(N * M, vec(N * M, 0));
    vec b(N * M, 0);
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            // ゴールにいる場合または(x,y)からゴールに到達できない場合
            if (x == N - 1 && y == M - 1 || !can_goal[x][y]) {
                A[x * M + y][x * M + y] = 1;
                continue;
            }

            // ゴール以外
            int move = 0;
            for (int r = 0; r < 4; r++) {
                int nx = x + dx[r], ny = y + dy[r];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny]) {
                    A[x * M + y][nx * M + ny] = -1;
                    move++;
                }
            }
            b[x * M + y] = A[x * M + y][x * M + y] = move;
        }
    }
    vec res = gauss_jordan(A, b);
    cout << fixed << setprecision(8) << res[0] << endl;
}
