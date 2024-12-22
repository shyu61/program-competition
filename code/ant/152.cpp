// Year of More Code Jam: p347
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 問題設定が複雑なので目的を整理してみる -> 幸福度の期待値を求める問題 -> 確率や期待値を求める問題は立式するのが鉄則(式変形により求解できる形に帰着させることがよくある)
// -> E[S^2] = E[Σ(a=1 to N) (a日目のラウンド総数)^2]

// ポイント
// - 確率や期待値問題はまず立式して整理するのが鉄則
// - 計算できる期待値の形を考え、それを目指して式変形を行う
//   - 多くは線形性や独立性を考慮した分解が効果的
// - 等確率の場合は、本当にその確率変数値を取るのが1通りなのか(場合の数が1なのか？)を考える

// 期待値とは？
// 重み付き平均のこと
// E[X] = 確率変数X * 発生確率

const int MAX_D = 1e5;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int N, T; cin >> N >> T;  // N: 開催日数, T: トーナメント数
    vector<int> m(T);  // m[i] := トーナメントiのラウンド総数
    for (int i = 0; i < T; i++) cin >> m[i];
    vector<vector<int>> d(N);  // d[i][j] := トーナメントiのラウンドjの開催日(そのトーナメントの開始日からの日数)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < m[i]; j++) {
            int d_; cin >> d_;
            d[i].push_back(d_);
        }
    }

    // E[i][a] := 大会a日目に、トーナメントiにラウンドが開催される期待値
    // 大会a日目にラウンド開催があるのは、dij <= aの場合(トーナメントiの開始日siは 1<=si<=MAX_D-m[i] を取ることができ何パターンもある)であり、これは累積和になる
    vector<vector<int>> E(T, vector<int>(MAX_D + 1));

    // 各トーナメント毎の期待値を計算
    for (int i = 0; i < T; i++) {
        // ラウンドの開催がある日は1
        for (int j = 0; j < m[i]; j++) {
            E[i][d[i][j]]++;
        }
        // 累積和を計算しておく
        for (int a = 1; a <= MAX_D; a++) {
            E[i][a] += E[i][a - 1];
        }
    }

    // 全体の期待値の計算
    // E[i][a]は分子部分のみなので、1/Nをかける必要がある。Eの2乗項に合わせてB=N^2としておき、1乗項は*Nして補正しておく
    ll K = 0, A = 0, B = ll(N) * N;
    for (int a = 1; a <= N && a <= MAX_D; a++) {
        ll sum = 0, sum2 = 0;
        for (int i = 0; i < T; i++) {
            sum += E[i][a];
            sum2 += E[i][a] * E[i][a];
        }
        if (a < MAX_D) {
            A += sum * sum - sum2 + sum * N;  // B=N^2なので1乗項は*Nで補正する
            K += A / B;
            A %= B;
        } else {  // 最終回のループのみ
            // MAX_Dより大きい部分は全て同じ期待値
            ll n = N - MAX_D + 1;
            K += sum * n / N;  // わざわざKを先に別計算するのはAを剰余なしで計算するとオーバーフローのリスクがあるから
            A += (sum * sum - sum2) * n + sum * n % N * N;
            K += A / B;
            A %= B;
            if (A < 0) {
                A += B;
                K--;
            }
        }
    }
    ll x = gcd(A, B);  // A/Bを既約分数に変換
    cout << K << "+" << A / x << "/" << B / x << endl;
}
