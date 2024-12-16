// Year of More Code Jam: p347
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 確率や期待値問題はまず立式して整理するのが鉄則

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

    vector<vector<int>> E(T, vector<int>(MAX_D + 1));  // E[i][a] := ラウンドiのa日目の期待値

    // 各トーナメント毎の期待値を計算
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < m[i]; j++) {
            E[i][d[i][j]]++;
        }
        for (int a = 1; a <= MAX_D; a++) {
            E[i][a] += E[i][a - 1];
        }
    }

    // 全体の期待値の計算
    ll K = 0, A = 0, B = ll(N) * N;
    for (int a = 1; a <= N && a <= MAX_D; a++) {
        ll sum = 0, sum2 = 0;
        for (int i = 0; i < T; i++) {
            sum += E[i][a];
            sum2 += E[i][a] * E[i][a];
        }
        if (a < MAX_D) {
            A += sum * sum - sum2 + sum * N;
            K += A / B;
            A %= B;
        } else {
            // MAX_Dより大きい部分は全て同じ期待値
            ll n = N - MAX_D + 1;
            K += sum * n / N;
            A += (sum * sum - sum2) * n + sum * n % N * N;
            K += A / B;
            A %= B;
            if (A < 0) {
                A += B;
                K--;
            }
        }
    }
    ll x = gcd(A, B);
    cout << K << "+" << A / x << "/" << B / x << endl;
}
